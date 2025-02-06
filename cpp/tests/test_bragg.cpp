#include "check.hpp"
#include "lightcircuit/bragg.hpp"

using namespace lc;

void test_bragg(Suite& suite) {
    const Medium m{1.55, 2.4, 4.2, 0.0};
    const Bragg g(m, 200.0, 0.01, 1.55);
    // at the Bragg wavelength the reflectivity is tanh^2(kappa L)
    const CMatrix s0 = g.scattering(1.55);
    CHECK_NEAR(std::norm(s0(0, 0)), std::pow(std::tanh(2.0), 2), 1e-13);
    CHECK_NEAR(g.peak_reflectivity(), std::pow(std::tanh(2.0), 2), 1e-15);
    // lossless and reciprocal at every wavelength, inside and outside the stop band
    for (double lambda = 1.53; lambda <= 1.57; lambda += 0.0007) {
        const CMatrix s = g.scattering(lambda);
        CHECK(unitarity_defect(s) < 1e-12 && reciprocity_defect(s) < 1e-15);
        CHECK(std::norm(s(0, 0)) <= std::norm(s0(0, 0)) + 1e-12);
    }
    // far from the stop band the grating is transparent
    CHECK(std::norm(g.scattering(1.45)(0, 0)) < 1e-3);
    // first zero of reflection: delta^2 = kappa^2 + (pi / L)^2
    const double delta = std::sqrt(0.01 * 0.01 + std::pow(PI / 200.0, 2));
    // beta(lambda) - beta_B = delta, solved to first order with the group index
    const double lambda_zero = 1.55 - delta * 1.55 * 1.55 / (2.0 * PI * 4.2);
    double least = 1.0;
    for (double l = lambda_zero - 2e-4; l <= lambda_zero + 2e-4; l += 2e-6) least = std::min(least, std::norm(g.scattering(l)(0, 0)));
    CHECK(least < 1e-5);
    // a weak grating reflects (kappa L)^2
    CHECK_NEAR(std::norm(Bragg(m, 10.0, 0.001, 1.55).scattering(1.55)(0, 0)), 1e-4, 2e-8);
    CHECK_THROWS(Bragg(m, 0.0, 0.01, 1.55));
}
