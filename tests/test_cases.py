import json

import pytest

from lightcircuit import cases, engine
from lightcircuit.engine import ROOT

ALL = cases.discover(ROOT / "cases")


def test_library_is_present_and_described():
    assert len(ALL) >= 60
    for path in ALL:
        assert cases.notes(path), f"{path.name} has no description"
        assert "expect " in path.read_text(), f"{path.name} checks nothing"


def test_families():
    fam = {"rings": ["ring_"], "trees": ["tree_"]}
    assert cases.family_of("ring_allpass_r10", fam) == "rings"
    assert cases.family_of("tree_1x8", fam) == "trees"
    assert cases.family_of("michelson", fam) == "other"


@pytest.mark.skipif(not engine.available(), reason="C++ simulator not built")
@pytest.mark.parametrize("path", ALL, ids=lambda p: p.stem)
def test_every_case_meets_its_expectations(path):
    result = engine.run(path, "check")
    assert result["checks"], "no expectations evaluated"
    failed = [c for c in result["checks"] if c["status"] != "PASS"]
    assert not failed, failed


@pytest.mark.skipif(not engine.available(), reason="C++ simulator not built")
def test_record_round_trip(tmp_path):
    record, result = cases.run_case(ROOT / "cases" / "coupler_3db.net")
    path = cases.write_record(record, tmp_path)
    back = json.loads(path.read_text())
    assert back["case"] == "coupler_3db" and back["ports"] == ["in", "isolated", "bar", "cross"]
    assert abs(back["metrics"]["bar"]["center_db"] + 3.0103) < 1e-4 and "lambda" not in back
