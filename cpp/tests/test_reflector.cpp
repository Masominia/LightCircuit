#include "check.hpp"
#include "lightcircuit/reflector.hpp"

using namespace lc;

void test_reflector(Suite& suite) {
    for (double r : {0.0, 0.3, 0.9, 1.0}) {
        const CMatrix s = Reflector(r).scattering(1.55);
        CHECK(unitarity_defect(s) < 1e-15 && reciprocity_defect(s) == 0.0);
        CHECK_NEAR(std::norm(s(0, 0)), r, 1e-15);
        CHECK_NEAR(std::norm(s(1, 0)), 1.0 - r, 1e-15);
    }
    CHECK_NEAR(std::norm(Mirror(0.64, 0.0).scattering(1.55)(0, 0)), 0.64, 1e-15);
    CHECK_NEAR(std::arg(Mirror(1.0, 0.7).scattering(1.55)(0, 0)), 0.7, 1e-15);
    CHECK(Mirror(0.0, 0.0).scattering(1.55)(0, 0) == cplx(0, 0));
    CHECK(Mirror(1.0, 0.0).ports() == 1);
    CHECK_THROWS(Reflector(-0.1));
    CHECK_THROWS(Mirror(1.1, 0.0));
}
