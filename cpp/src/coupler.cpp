#include "lightcircuit/coupler.hpp"

#include <cmath>
#include <stdexcept>

namespace lc {

Coupler::Coupler(double kappa, double excess_db) {
    if (kappa < 0.0 || kappa > 1.0) throw std::invalid_argument("coupler: kappa must be between 0 and 1");
    if (excess_db < 0.0) throw std::invalid_argument("coupler: excess loss must not be negative");
    const double keep = std::sqrt(db_to_power(-excess_db));
    t_ = keep * std::sqrt(1.0 - kappa);
    k_ = keep * std::sqrt(kappa);
}

CMatrix Coupler::scattering(double) const {
    CMatrix s(4, 4);
    const cplx cross(0.0, k_);
    s(2, 0) = s(0, 2) = t_;
    s(3, 1) = s(1, 3) = t_;
    s(3, 0) = s(0, 3) = cross;
    s(2, 1) = s(1, 2) = cross;
    return s;
}

}  // namespace lc
