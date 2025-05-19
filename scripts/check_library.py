"""Run every netlist of the library and print one line per circuit. Exit status 1 if any expectation fails.

python scripts/check_library.py [directory]
"""

import sys
from pathlib import Path

from lightcircuit import cases, engine
from lightcircuit.engine import ROOT

if __name__ == "__main__":
    directory = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / "cases"
    failures = 0
    for path in cases.discover(directory):
        checks = engine.run(path, "check")["checks"]
        bad = [c for c in checks if c["status"] != "PASS"]
        failures += len(bad)
        print(f"{'ok  ' if not bad else 'FAIL'} {path.stem:<32} {len(checks) - len(bad)}/{len(checks)}")
        for c in bad:
            print(f"       {c['check']}: {c['detail']}")
    sys.exit(1 if failures else 0)
