#include "lightcircuit/splitter.hpp"

#include <cmath>
#include <stdexcept>

namespace lc {

Splitter::Splitter(double ratio, double excess_db) {
    if (ratio < 0.0 || ratio > 1.0) throw std::invalid_argument("splitter: ratio must be between 0 and 1");
    if (excess_db < 0.0) throw std::invalid_argument("splitter: excess loss must not be negative");
    const double keep = std::sqrt(db_to_power(-excess_db));
    a2_ = keep * std::sqrt(ratio);
    a3_ = keep * std::sqrt(1.0 - ratio);
}

CMatrix Splitter::scattering(double) const {
    CMatrix s(3, 3);
    s(1, 0) = s(0, 1) = a2_;
    s(2, 0) = s(0, 2) = a3_;
    return s;
}

}  // namespace lc
