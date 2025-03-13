import json

import pytest

from lightcircuit import engine
from lightcircuit.pipeline import run


@pytest.mark.skipif(not engine.available(), reason="C++ simulator not built")
def test_fast_pipeline(tmp_path):
    m = run(out=tmp_path, fast=True)
    assert not [c for c in m["checks"] if c["status"] == "FAIL"]
    assert m["circuits"] >= 12 and m["closed_form"]
    assert (tmp_path / "report.md").exists() and (tmp_path / "figures" / "overview.png").exists()
    records = list((tmp_path / "cases").glob("*.json"))
    assert len(records) == m["circuits"] == len(list((tmp_path / "figures" / "cases").glob("*.png")))
    assert json.loads(records[0].read_text())["checks"]
