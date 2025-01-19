#include "lightcircuit/waveguide.hpp"

#include <stdexcept>

namespace lc {

Waveguide::Waveguide(const Medium& medium, double length, double extra_phase) : medium_(medium), length_(length), phase_(extra_phase) {
    if (length < 0.0) throw std::invalid_argument("waveguide: negative length");
}

CMatrix Waveguide::scattering(double lambda) const {
    CMatrix s(2, 2);
    s(0, 1) = s(1, 0) = medium_.propagate(lambda, length_) * std::exp(cplx(0.0, phase_));
    return s;
}

}  // namespace lc
