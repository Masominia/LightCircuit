"""Runs the whole circuit library, checks it and writes the report."""

from __future__ import annotations

import json
from pathlib import Path

import pandas as pd
import yaml

from . import analytic, cases, engine, plotting
from .engine import ROOT
from .report import md_table


def run(cfg_path=None, out=None, fast: bool = False) -> dict:
    cfg = yaml.safe_load(open(cfg_path or ROOT / "configs" / "default.yaml"))
    out = Path(out) if out else ROOT / "reports"
    (out / "figures" / "cases").mkdir(parents=True, exist_ok=True)
    if not engine.available():
        raise SystemExit("C++ simulator not built: run `make build` first")
    paths = cases.discover(ROOT / cfg["cases_dir"])
    if fast:
        keep = set(cfg["gallery"]) | set(list(analytic.REFERENCE)[:3])
        paths = [p for i, p in enumerate(paths) if i % cfg["fast_every"] == 0 or p.stem in keep]

    checks, rows, cross, gallery = [], [], {}, {}
    for path in paths:
        record, result = cases.run_case(path)
        cases.write_record(record, out / "cases")
        plotting.case_figure(result, record["title"], out / "figures" / "cases" / f"{path.stem}.png")
        family = cases.family_of(path.stem, cfg["families"])
        for c in record["checks"]:
            checks.append(
                {"area": family, "check": f"{path.stem}: {c['check']}", "status": c["status"], "detail": c["detail"]}
            )
        passed = sum(c["status"] == "PASS" for c in record["checks"])
        rows.append(
            {
                "case": path.stem,
                "family": family,
                "circuit": record["title"],
                "components": record["components"],
                "ports": len(record["ports"]),
                "points": record["points"],
                "checks": len(record["checks"]),
                "passed": passed,
            }
        )
        comparison = analytic.compare(path.stem, result)
        if comparison:
            cross[path.stem] = comparison
            ok = comparison["largest power difference"] < 1e-9
            checks.append(
                {
                    "area": "closed form",
                    "check": f"{path.stem}: whole spectrum against the formula",
                    "status": "PASS" if ok else "FAIL",
                    "detail": f"largest difference {comparison['largest power difference']:.1e} in linear power over {comparison['points']} points",
                }
            )
        if path.stem in cfg["gallery"]:
            gallery[path.stem] = (result, record["title"], cfg["gallery"][path.stem])

    table = pd.DataFrame(rows)
    fam = table.groupby("family", sort=False).agg(
        cases=("case", "size"), components=("components", "sum"), checks=("checks", "sum"), passed=("passed", "sum")
    )
    if gallery:
        plotting.overview(gallery, out / "figures" / "overview.png")
    xt = pd.DataFrame(cross).T
    xt.index.name = "case"

    val = pd.DataFrame(checks)
    counts = val["status"].value_counts().to_dict()
    lines = [
        "# LightCircuit report",
        "",
        f"{len(table)} circuits, {int(table['components'].sum())} components, {len(val)} checks: {counts.get('PASS', 0)} PASS, {counts.get('FAIL', 0)} FAIL.",
        "",
        "Every circuit is a netlist in `cases/`. Its expectations come from closed-form results stated in the comments at the top of the file.",
        "Per-circuit results are in `reports/cases/`, spectra in `reports/figures/cases/`.",
        "",
        "## Families",
        "",
        md_table(fam, 0),
        "",
        "## Whole spectra against closed forms",
        "",
        "For these circuits the complete spectrum is compared, point by point, with a formula written separately in Python (`src/lightcircuit/analytic.py`).",
        "",
        md_table(xt, 3),
        "",
        "## All circuits",
        "",
        md_table(table.drop(columns=["family"]), 0, index=False),
        "",
    ]
    (out / "report.md").write_text("\n".join(lines))
    (out / "validation.md").write_text("# Validation checks\n\n" + md_table(val, index=False) + "\n")
    metrics = {
        "circuits": len(table),
        "components": int(table["components"].sum()),
        "families": fam.to_dict("index"),
        "closed_form": cross,
        "checks": checks,
    }
    (out / "metrics.json").write_text(json.dumps(metrics, indent=1, default=float))
    return metrics
