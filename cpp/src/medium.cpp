#include "lightcircuit/medium.hpp"

#include <cmath>

namespace lc {

double Medium::index(double lambda) const { return neff + (lambda - lambda0) * (neff - ng) / lambda0; }

double Medium::beta(double lambda) const { return 2.0 * PI * index(lambda) / lambda; }

double Medium::amplitude_loss() const { return 0.5 * loss_db_cm * std::log(10.0) / 10.0 * 1e-4; }

cplx Medium::propagate(double lambda, double length) const {
    return std::exp(cplx(-amplitude_loss() * length, beta(lambda) * length));
}

double db_to_power(double db) { return std::pow(10.0, db / 10.0); }

double power_to_db(double power) { return 10.0 * std::log10(power > 1e-30 ? power : 1e-30); }

}  // namespace lc
