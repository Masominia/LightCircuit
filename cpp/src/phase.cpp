#include "lightcircuit/phase.hpp"

#include <cmath>
#include <stdexcept>

namespace lc {

CMatrix PhaseShifter::scattering(double) const {
    CMatrix s(2, 2);
    s(0, 1) = s(1, 0) = std::exp(cplx(0.0, phi_));
    return s;
}

Attenuator::Attenuator(double db) : amplitude_(std::sqrt(db_to_power(-db))) {
    if (db < 0.0) throw std::invalid_argument("attenuator: loss must not be negative (no gain)");
}

CMatrix Attenuator::scattering(double) const {
    CMatrix s(2, 2);
    s(0, 1) = s(1, 0) = amplitude_;
    return s;
}

}  // namespace lc
