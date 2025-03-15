"""Static figures for the report (matplotlib, PNG for the README)."""

from __future__ import annotations

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt  # noqa: E402
import numpy as np  # noqa: E402

# Validated categorical order (fixed, never cycled) + recessive ink.
SERIES = ["#2a78d6", "#eb6834", "#1baf7a", "#eda100", "#e87ba4", "#008300", "#6250d6", "#e34948"]
SURFACE, INK, INK2, GRID = "#fcfcfb", "#0b0b0b", "#52514e", "#e4e3df"
NEUTRAL = "#8a8985"
CRITICAL = "#c4271a"

plt.rcParams.update(
    {
        "figure.facecolor": SURFACE,
        "axes.facecolor": SURFACE,
        "savefig.facecolor": SURFACE,
        "axes.edgecolor": GRID,
        "axes.labelcolor": INK2,
        "xtick.color": INK2,
        "ytick.color": INK2,
        "text.color": INK,
        "axes.grid": True,
        "grid.color": GRID,
        "grid.linewidth": 0.6,
        "axes.spines.top": False,
        "axes.spines.right": False,
        "font.size": 9,
        "axes.titlesize": 10,
        "axes.titleweight": "bold",
        "legend.frameon": False,
        "lines.linewidth": 1.6,
        "figure.dpi": 150,
        "axes.axisbelow": True,
    }
)


def _save(fig, path):
    fig.tight_layout()
    fig.savefig(path, bbox_inches="tight")
    plt.close(fig)


def _visible(result):
    """Ports worth drawing: those that carry any light at all."""
    return [p for p in result["ports"] if result["db"][p].max() > -150.0]


def _draw(ax, result, ports):
    lam = result["lambda"]
    for i, port in enumerate(ports):
        ax.plot(lam, np.maximum(result["db"][port], -80.0), color=SERIES[i % len(SERIES)], lw=1.2, label=port)
    ax.set_xlim(lam[0], lam[-1])
    ax.set(xlabel="wavelength, um", ylabel="transmission, dB")
    if len(ports) <= 8:
        ax.legend(fontsize=7)


def case_figure(result, title, path):
    fig, ax = plt.subplots(figsize=(6.2, 3.4))
    _draw(ax, result, _visible(result))
    ax.set_title(title)
    fig.tight_layout()
    fig.savefig(path, dpi=110)
    plt.close(fig)


def overview(gallery, path):
    names = list(gallery)
    fig, axes = plt.subplots(2, 3, figsize=(13, 6.6))
    for ax, name in zip(axes.ravel(), names, strict=False):
        result, title, ports = gallery[name]
        _draw(ax, result, ports)
        ax.set_title(title, fontsize=9)
    for ax in axes.ravel()[len(names) :]:
        ax.axis("off")
    _save(fig, path)
