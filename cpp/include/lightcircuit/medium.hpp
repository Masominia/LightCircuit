// The guided mode: effective index with first-order dispersion, and propagation loss.
#pragma once

#include "lightcircuit/types.hpp"

namespace lc {

struct Medium {
    double lambda0 = 1.55;     // reference wavelength, micrometres
    double neff = 2.4;         // effective index at lambda0
    double ng = 4.2;           // group index at lambda0
    double loss_db_cm = 0.0;   // power loss

    // neff(lambda) = neff0 + (lambda - lambda0) (neff0 - ng) / lambda0, which has group index ng at lambda0.
    double index(double lambda) const;

    // Propagation constant in radians per micrometre.
    double beta(double lambda) const;

    // Amplitude attenuation per micrometre.
    double amplitude_loss() const;

    // Complex amplitude factor of a length of waveguide, in micrometres.
    cplx propagate(double lambda, double length) const;
};

double db_to_power(double db);
double power_to_db(double power);

}  // namespace lc
