"""Solve one netlist and print what the simulator found.

python scripts/simulate.py cases/ring_adddrop_symmetric.net
"""

import sys

from lightcircuit import engine

if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit(__doc__)
    r = engine.run(sys.argv[1], "check")
    print(f"{r['title']}: {int(r['components'])} components, ports {', '.join(r['ports'])}")
    for port, metrics in r["metrics"].items():
        if metrics["max_db"] < -150:
            continue
        line = f"  {port:<10} {metrics['min_db']:>8.2f} to {metrics['max_db']:>6.2f} dB"
        for kind in ("dips", "peaks"):
            if f"{kind}_fsr_nm" in metrics:
                line += f"   {kind}: spacing {metrics[kind + '_fsr_nm']:.3f} nm"
            if f"{kind}_q" in metrics:
                line += f", Q {metrics[kind + '_q']:.0f}"
        print(line)
    for c in r["checks"]:
        print(f"  {c['status']}  {c['check']}  ({c['detail']})")
