"""Draw the spectrum of one netlist to a PNG file.

python scripts/plot_case.py cases/crow_4_rings.net spectrum.png
"""

import sys

from lightcircuit import engine, plotting

if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise SystemExit(__doc__)
    result = engine.run(sys.argv[1])
    plotting.case_figure(result, result["title"], sys.argv[2])
    print(f"wrote {sys.argv[2]}")
