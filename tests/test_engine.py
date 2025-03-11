import numpy as np
import pytest

from lightcircuit import analytic, engine

pytestmark = pytest.mark.skipif(not engine.available(), reason="C++ simulator not built")

RING = """title test ring
medium lambda0=1.55 neff=2.4 ng=4.2 loss_db_cm=2
sweep 1.54 1.56 2001
comp c1 coupler kappa=0.1
comp c2 coupler kappa=0.2
comp w1 waveguide length=40
comp w2 waveguide length=40
link c1.4 w1.1
link w1.2 c2.4
link c2.2 w2.1
link w2.2 c1.2
port in c1.1
port through c1.3
port drop c2.1
expect passive
expect lossless
"""


def test_ring_matches_the_formula(tmp_path):
    path = tmp_path / "ring.net"
    path.write_text(RING)
    r = engine.run(path)
    assert r["ports"] == ["in", "through", "drop"] and r["excite"] == "in" and len(r["lambda"]) == 2001
    expected = analytic.add_drop(r["lambda"], 80.0, 0.1, 0.2, 2.0)
    for port in ("through", "drop"):
        assert np.max(np.abs(10 ** (r["db"][port] / 10) - expected[port])) < 1e-9
    assert [c["status"] for c in r["checks"]] == ["PASS", "FAIL"]  # passive, but not lossless
    assert r["metrics"]["drop"]["peaks"] >= 2 and "peaks_fsr_nm" in r["metrics"]["drop"]
    assert r["reciprocity_defect"] < 1e-12 and r["open_ports"] == 1


def test_check_command_and_errors(tmp_path):
    path = tmp_path / "ring.net"
    path.write_text(RING)
    r = engine.run(path, "check")
    assert "lambda" not in r and len(r["checks"]) == 2
    bad = tmp_path / "bad.net"
    bad.write_text("comp a coupler kappa=2\nport in a.1\n")
    with pytest.raises(RuntimeError, match="kappa must be between 0 and 1"):
        engine.run(bad)
    bad.write_text("comp a coupler kappa=0.5\nlink a.1 b.1\nport in a.2\n")
    with pytest.raises(RuntimeError, match="unknown component 'b'"):
        engine.run(bad)


def test_phase_and_delay(tmp_path):
    path = tmp_path / "wg.net"
    path.write_text(
        "sweep 1.549 1.551 201\ncomp w waveguide length=500\nport in w.1\nport out w.2\n"
        "expect delay out 1.55 7.00485 1e-4\n"
    )
    r = engine.run(path)
    assert r["checks"][0]["status"] == "PASS"
    slope = np.gradient(r["phase"]["out"], r["lambda"])
    assert np.all(slope < 0)  # phase falls with wavelength
