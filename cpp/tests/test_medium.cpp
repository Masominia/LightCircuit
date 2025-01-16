#include "check.hpp"
#include "lightcircuit/medium.hpp"

using namespace lc;

void test_medium(Suite& suite) {
    const Medium m{1.55, 2.4, 4.2, 2.0};
    CHECK_NEAR(m.index(1.55), 2.4, 1e-15);
    // group index n - lambda dn/dlambda at the reference wavelength
    const double h = 1e-6, slope = (m.index(1.55 + h) - m.index(1.55 - h)) / (2.0 * h);
    CHECK_NEAR(m.index(1.55) - 1.55 * slope, 4.2, 1e-8);
    CHECK_NEAR(m.beta(1.55), 2.0 * PI * 2.4 / 1.55, 1e-13);
    // 2 dB/cm over one centimetre
    CHECK_NEAR(power_to_db(std::norm(m.propagate(1.55, 1e4))), -2.0, 1e-10);
    CHECK_NEAR(std::arg(m.propagate(1.55, 1.55 / 2.4)), 0.0, 1e-9);  // one wavelength in the guide
    const Medium lossless{1.55, 2.4, 4.2, 0.0};
    CHECK_NEAR(std::abs(lossless.propagate(1.6, 123.0)), 1.0, 1e-15);
    CHECK_NEAR(db_to_power(-3.0), 0.5011872336272722, 1e-15);
    CHECK_NEAR(power_to_db(0.01), -20.0, 1e-12);
    CHECK(power_to_db(0.0) == -300.0);
}
