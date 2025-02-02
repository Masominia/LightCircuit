#include "lightcircuit/bragg.hpp"

#include <cmath>
#include <stdexcept>

namespace lc {

Bragg::Bragg(const Medium& medium, double length, double kappa, double bragg_lambda) : medium_(medium), length_(length), kappa_(kappa) {
    if (length <= 0.0 || kappa <= 0.0 || bragg_lambda <= 0.0) throw std::invalid_argument("bragg: length, kappa and bragg_lambda must be positive");
    beta_bragg_ = medium_.beta(bragg_lambda);
}

double Bragg::peak_reflectivity() const {
    const double t = std::tanh(kappa_ * length_);
    return t * t;
}

CMatrix Bragg::scattering(double lambda) const {
    // detuning from the Bragg condition; s is real inside the stop band and imaginary outside
    const cplx delta(medium_.beta(lambda) - beta_bragg_, 0.0);
    const cplx s = std::sqrt(cplx(kappa_ * kappa_, 0.0) - delta * delta);
    const cplx sl = s * length_;
    cplx r, t;
    if (std::abs(sl) < 1e-9) {  // band edge: the limit of the expressions below
        const cplx denom = cplx(1.0, 0.0) + cplx(0.0, 1.0) * delta * length_;
        r = cplx(0.0, -kappa_ * length_) / denom;
        t = cplx(1.0, 0.0) / denom;
    } else {
        const cplx denom = s * std::cosh(sl) + cplx(0.0, 1.0) * delta * std::sinh(sl);
        r = cplx(0.0, -kappa_) * std::sinh(sl) / denom;
        t = s / denom;
    }
    // the transmitted wave also carries the phase of the Bragg wavevector over the length
    t *= std::exp(cplx(0.0, beta_bragg_ * length_));
    CMatrix m(2, 2);
    m(0, 0) = r;
    m(0, 1) = m(1, 0) = t;
    // reflection seen from the far end: fixed by energy conservation once r and t are known
    m(1, 1) = -std::conj(r) * t / std::conj(t);
    return m;
}

}  // namespace lc
