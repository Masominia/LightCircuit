#include "lightcircuit/reflector.hpp"

#include <cmath>
#include <stdexcept>

namespace lc {

Reflector::Reflector(double reflectivity) {
    if (reflectivity < 0.0 || reflectivity > 1.0) throw std::invalid_argument("reflector: reflectivity must be between 0 and 1");
    r_ = std::sqrt(reflectivity);
    t_ = std::sqrt(1.0 - reflectivity);
}

CMatrix Reflector::scattering(double) const {
    CMatrix s(2, 2);
    s(0, 0) = s(1, 1) = r_;
    s(0, 1) = s(1, 0) = cplx(0.0, t_);
    return s;
}

Mirror::Mirror(double reflectivity, double phase) {
    if (reflectivity < 0.0 || reflectivity > 1.0) throw std::invalid_argument("mirror: reflectivity must be between 0 and 1");
    r_ = std::sqrt(reflectivity) * std::exp(cplx(0.0, phase));
}

CMatrix Mirror::scattering(double) const {
    CMatrix s(1, 1);
    s(0, 0) = r_;
    return s;
}

}  // namespace lc
