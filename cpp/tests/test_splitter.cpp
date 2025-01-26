#include "check.hpp"
#include "lightcircuit/splitter.hpp"

using namespace lc;

void test_splitter(Suite& suite) {
    const CMatrix s = Splitter(0.5, 0.0).scattering(1.55);
    CHECK_NEAR(std::norm(s(1, 0)), 0.5, 1e-15);
    CHECK_NEAR(std::norm(s(2, 0)), 0.5, 1e-15);
    CHECK(reciprocity_defect(s) == 0.0 && max_column_power(s) <= 1.0 + 1e-15);
    // as a combiner: in-phase arms add up, out-of-phase arms are lost
    const double a = std::sqrt(0.5);
    CHECK_NEAR(std::norm(s(0, 1) * a + s(0, 2) * a), 1.0, 1e-15);
    CHECK_NEAR(std::norm(s(0, 1) * a - s(0, 2) * a), 0.0, 1e-15);
    CHECK(unitarity_defect(s) > 0.4);  // a three-port cannot be lossless, matched and reciprocal at once
    const CMatrix uneven = Splitter(0.8, 0.5).scattering(1.55);
    CHECK_NEAR(std::norm(uneven(1, 0)) / std::norm(uneven(2, 0)), 4.0, 1e-12);
    CHECK_NEAR(power_to_db(std::norm(uneven(1, 0)) + std::norm(uneven(2, 0))), -0.5, 1e-12);
    CHECK_THROWS(Splitter(1.5, 0.0));
}
