#include "check.hpp"
#include "lightcircuit/coupler.hpp"

using namespace lc;

void test_coupler(Suite& suite) {
    for (double kappa : {0.0, 0.1, 0.5, 0.85, 1.0}) {
        const CMatrix s = Coupler(kappa, 0.0).scattering(1.55);
        CHECK(unitarity_defect(s) < 1e-15 && reciprocity_defect(s) == 0.0);
        CHECK_NEAR(std::norm(s(3, 0)), kappa, 1e-15);       // cross
        CHECK_NEAR(std::norm(s(2, 0)), 1.0 - kappa, 1e-15); // bar
        CHECK(s(0, 0) == cplx(0, 0) && s(1, 0) == cplx(0, 0));  // no reflection, no coupling back
    }
    // the cross port lags by a quarter wave
    const CMatrix half = Coupler(0.5, 0.0).scattering(1.55);
    CHECK_NEAR(std::arg(half(3, 0)) - std::arg(half(2, 0)), PI / 2, 1e-15);
    // two half couplers in a row send everything across
    CHECK(std::abs(half(2, 0) * half(2, 0) + half(3, 0) * half(2, 1)) < 1e-15);
    CHECK_NEAR(std::abs(half(2, 0) * half(3, 0) + half(3, 0) * half(3, 1)), 1.0, 1e-15);
    const CMatrix lossy = Coupler(0.5, 1.0).scattering(1.55);
    CHECK_NEAR(power_to_db(std::norm(lossy(2, 0)) + std::norm(lossy(3, 0))), -1.0, 1e-12);
    CHECK_THROWS(Coupler(1.2, 0.0));
    CHECK_THROWS(Coupler(0.5, -0.1));
}
