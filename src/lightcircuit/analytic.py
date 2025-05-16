"""Closed-form responses, written independently of the C++ code, for whole-spectrum comparisons.

Same conventions as the simulator: neff(lambda) = neff0 + (lambda - lambda0) (neff0 - ng) / lambda0,
propagation factor exp(i beta L - alpha L), coupler bar amplitude t and cross amplitude i k.
"""

from __future__ import annotations

import numpy as np

LAMBDA0, NEFF, NG = 1.55, 2.4, 4.2


def propagate(lam, length, loss_db_cm=0.0):
    index = NEFF + (lam - LAMBDA0) * (NEFF - NG) / LAMBDA0
    alpha = 0.5 * loss_db_cm * np.log(10) / 10 * 1e-4
    return np.exp((1j * 2 * np.pi * index / lam - alpha) * length)


def allpass(lam, circumference, kappa, loss_db_cm=0.0):
    """Power transmission of a ring coupled to one bus."""
    t, loop = np.sqrt(1 - kappa), propagate(lam, circumference, loss_db_cm)
    return {"through": np.abs((t - loop) / (1 - t * loop)) ** 2}


def add_drop(lam, circumference, kappa1, kappa2, loss_db_cm=0.0):
    t1, t2 = np.sqrt(1 - kappa1), np.sqrt(1 - kappa2)
    half = propagate(lam, circumference / 2, loss_db_cm)
    den = 1 - t1 * t2 * half**2
    return {
        "through": np.abs((t1 - t2 * half**2) / den) ** 2,
        "drop": np.abs(np.sqrt(kappa1 * kappa2) * half / den) ** 2,
    }


def mach_zehnder(lam, length_a, length_b, kappa1=0.5, kappa2=0.5):
    t1, k1, t2, k2 = np.sqrt(1 - kappa1), np.sqrt(kappa1), np.sqrt(1 - kappa2), np.sqrt(kappa2)
    a, b = propagate(lam, length_a), propagate(lam, length_b)
    return {"bar": np.abs(t1 * t2 * a - k1 * k2 * b) ** 2, "cross": np.abs(t1 * k2 * a + k1 * t2 * b) ** 2}


def fabry_perot(lam, length, reflectivity):
    """Airy function of two identical lossless mirrors."""
    one_way = propagate(lam, length)
    t = (1 - reflectivity) ** 2 * np.abs(one_way) ** 2 / np.abs(1 - reflectivity * one_way**2) ** 2
    return {"out": t, "in": 1 - t}


def michelson(lam, length_a, length_b):
    a, b = propagate(lam, 2 * length_a), propagate(lam, 2 * length_b)
    return {"in": np.abs(0.5 * (a - b)) ** 2, "out": np.abs(0.5 * (a + b)) ** 2}


def bragg(lam, length, kappa, bragg_lambda=LAMBDA0):
    """Reflection and transmission of a uniform grating from coupled-mode theory."""
    beta = lambda x: 2 * np.pi * (NEFF + (x - LAMBDA0) * (NEFF - NG) / LAMBDA0) / x  # noqa: E731
    delta = beta(lam) - beta(bragg_lambda)
    s = np.sqrt((kappa**2 - delta**2).astype(complex))
    den = s * np.cosh(s * length) + 1j * delta * np.sinh(s * length)
    return {"in": np.abs(kappa * np.sinh(s * length) / den) ** 2, "out": np.abs(s / den) ** 2}


# Case name -> (function, arguments). The arguments repeat what the netlists say.
RING10 = 2 * np.pi * 10
REFERENCE = {
    "ring_allpass_r10": (allpass, (RING10, 0.05, 3.0)),
    "ring_allpass_lossless": (allpass, (RING10, 0.1, 0.0)),
    "ring_adddrop_symmetric": (add_drop, (RING10, 0.1, 0.1, 2.0)),
    "ring_adddrop_asymmetric": (add_drop, (RING10, 0.2, 0.05, 2.0)),
    "ring_adddrop_strong": (add_drop, (RING10, 0.4, 0.4, 2.0)),
    "mzi_dl_100": (mach_zehnder, (100.0, 200.0)),
    "mzi_unbalanced_couplers": (mach_zehnder, (100.0, 200.0, 0.4, 0.4)),
    "fabry_perot_r30": (fabry_perot, (200.0, 0.3)),
    "fabry_perot_r90": (fabry_perot, (200.0, 0.9)),
    "michelson": (michelson, (100.0, 150.0)),
    "bragg_strong": (bragg, (300.0, 0.01)),
    "bragg_weak": (bragg, (100.0, 0.003)),
}


def compare(case: str, result: dict) -> dict | None:
    """Largest difference in linear power between the simulator and the closed form, over the whole sweep."""
    if case not in REFERENCE:
        return None
    function, args = REFERENCE[case]
    expected = function(result["lambda"], *args)
    worst = 0.0
    for port, power in expected.items():
        worst = max(worst, float(np.max(np.abs(10 ** (result["db"][port] / 10) - power))))
    return {
        "ports": ", ".join(sorted(expected)),
        "points": int(len(result["lambda"])),
        "largest power difference": worst,
    }
