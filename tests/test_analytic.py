import numpy as np

from lightcircuit import analytic

LAM = np.linspace(1.54, 1.56, 4001)


def test_lossless_devices_conserve_power():
    ad = analytic.add_drop(LAM, 60.0, 0.1, 0.1)
    assert np.allclose(ad["through"] + ad["drop"], 1.0, atol=1e-12)
    mz = analytic.mach_zehnder(LAM, 100.0, 180.0, 0.3, 0.6)
    assert np.allclose(mz["bar"] + mz["cross"], 1.0, atol=1e-12)
    br = analytic.bragg(LAM, 200.0, 0.01)
    assert np.allclose(br["in"] + br["out"], 1.0, atol=1e-10)
    assert np.allclose(analytic.allpass(LAM, 60.0, 0.2)["through"], 1.0, atol=1e-12)


def test_known_values():
    assert abs(analytic.bragg(np.array([1.55]), 300.0, 0.01)["in"][0] - np.tanh(3.0) ** 2) < 1e-12
    fp = analytic.fabry_perot(LAM, 200.0, 0.5)
    assert abs(fp["out"].max() - 1.0) < 1e-4 and abs(fp["out"].min() - (0.5 / 1.5) ** 2) < 1e-4
    # 2 dB/cm over one centimetre
    assert abs(10 * np.log10(abs(analytic.propagate(1.55, 1e4, 2.0)) ** 2) + 2.0) < 1e-12


def test_free_spectral_range():
    t = analytic.allpass(LAM, 2 * np.pi * 10, 0.05, 3.0)["through"]
    dips = np.where((t[1:-1] < t[:-2]) & (t[1:-1] < t[2:]) & (t[1:-1] < 0.9))[0] + 1
    spacing = np.diff(LAM[dips]).mean() * 1e3
    assert abs(spacing - 1e3 * 1.55**2 / (4.2 * 2 * np.pi * 10)) < 0.06
