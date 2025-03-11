"""Python side of the C++ simulator: runs the binary on a netlist and parses its output."""

from __future__ import annotations

import subprocess
from pathlib import Path

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
BINARY = ROOT / "cpp" / "build" / "lightcircuit"


def available() -> bool:
    return BINARY.exists()


def run(netlist: Path | str, command: str = "run") -> dict:
    """Solve a netlist. Returns title, ports, defects, per-port metrics, checks and, for `run`, the spectrum.

    Raises RuntimeError with the simulator's message if the netlist is invalid.
    """
    proc = subprocess.run([str(BINARY), command, str(netlist)], capture_output=True, text=True)
    if proc.returncode == 2:
        raise RuntimeError(proc.stderr.strip())
    res: dict = {"metrics": {}, "checks": []}
    rows = []
    for line in proc.stdout.splitlines():
        key, _, rest = line.partition(" ")
        if key == "row":
            rows.append(rest)
        elif key == "metric":
            port, name, value = rest.split()
            res["metrics"].setdefault(port, {})[name] = float(value)
        elif key == "check":
            status, _, tail = rest.partition(" ")
            name, _, detail = tail.partition(" :: ")
            res["checks"].append({"check": name, "status": status, "detail": detail})
        elif key == "title":
            res["title"] = rest
        elif key == "ports":
            res["ports"] = rest.split()
        elif key == "excite":
            res["excite"] = rest
        else:
            res[key] = float(rest)
    if rows:
        table = np.array([r.split() for r in rows], dtype=float)
        n = len(res["ports"])
        res["lambda"] = table[:, 0]
        res["db"] = {p: table[:, 1 + i] for i, p in enumerate(res["ports"])}
        res["phase"] = {p: table[:, 1 + n + i] for i, p in enumerate(res["ports"])}
    return res
