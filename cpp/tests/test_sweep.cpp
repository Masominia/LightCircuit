#include "check.hpp"
#include "lightcircuit/sweep.hpp"

using namespace lc;

void test_sweep(Suite& suite) {
    const Netlist n = parse_netlist("medium lambda0=1.55 neff=2.4 ng=4.2 loss_db_cm=0\nsweep 1.54 1.56 201\n"
                                    "comp s1 coupler kappa=0.5\ncomp a waveguide length=100\ncomp b waveguide length=150\ncomp s2 coupler kappa=0.5\n"
                                    "link s1.3 a.1\nlink s1.4 b.1\nlink a.2 s2.1\nlink b.2 s2.2\nport in s1.1\nport in2 s1.2\nport bar s2.3\nport cross s2.4\n");
    const Spectrum sp = sweep(Circuit(n), n);
    CHECK(sp.lambda.size() == 201 && sp.lambda.front() == 1.54 && sp.lambda.back() == 1.56);
    CHECK(sp.ports.size() == 4 && sp.excited == 0 && sp.port_index("cross") == 3);
    CHECK_THROWS(sp.port_index("drop"));
    CHECK(sp.unitarity_defect < 1e-12 && sp.power_defect < 1e-12 && sp.reciprocity_defect < 1e-12);
    CHECK_NEAR(sp.max_power, 1.0, 1e-12);
    // the two outputs of a lossless interferometer are complementary
    const Vector bar = sp.power(2), cross = sp.power(3);
    double worst = 0.0;
    for (std::size_t i = 0; i < bar.size(); ++i) worst = std::max(worst, std::fabs(bar[i] + cross[i] - 1.0));
    CHECK(worst < 1e-12);
    // bar power is sin^2 of half the phase difference
    const Medium m{1.55, 2.4, 4.2, 0.0};
    CHECK_NEAR(bar[77], std::pow(std::sin(0.5 * m.beta(sp.lambda[77]) * 50.0), 2), 1e-11);
    CHECK_NEAR(sp.power_db(2)[77], power_to_db(bar[77]), 1e-12);
    // the unwrapped phase has no jump larger than pi
    const Vector ph = sp.phase(3);
    double jump = 0.0;
    for (std::size_t i = 1; i < ph.size(); ++i) jump = std::max(jump, std::fabs(ph[i] - ph[i - 1]));
    CHECK(jump < PI);
}
