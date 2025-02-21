#include "check.hpp"
#include "lightcircuit/circuit.hpp"

using namespace lc;

static Circuit build(const std::string& text) { return Circuit(parse_netlist(text)); }

void test_circuit(Suite& suite) {
    const Medium m{1.55, 2.4, 4.2, 2.0};
    const std::string medium = "medium lambda0=1.55 neff=2.4 ng=4.2 loss_db_cm=2\n";

    // two waveguides in series are one waveguide
    const Circuit series = build(medium + "comp a waveguide length=30\ncomp b waveguide length=70\nlink a.2 b.1\nport in a.1\nport out b.2\n");
    CHECK(series.total_ports() == 4 && series.open_ports() == 0 && series.external_count() == 2);
    CHECK(std::abs(series.solve(1.551)(1, 0) - m.propagate(1.551, 100.0)) < 1e-13);
    CHECK(std::abs(series.solve(1.551)(0, 0)) < 1e-15);

    // all-pass ring against (t - a e^{i phi}) / (1 - t a e^{i phi})
    const Circuit ring = build(medium + "comp c coupler kappa=0.2\ncomp w waveguide length=80\nlink c.4 w.1\nlink w.2 c.2\nport in c.1\nport through c.3\n");
    for (double lambda : {1.540, 1.5503, 1.5571, 1.562}) {
        const cplx loop = m.propagate(lambda, 80.0);
        const double t = std::sqrt(0.8);
        CHECK(std::abs(ring.solve(lambda)(1, 0) - (t - loop) / (1.0 - t * loop)) < 1e-12);
    }

    // add-drop ring: drop port against -k1 k2 sqrt(loop) / (1 - t1 t2 loop)
    const Circuit add_drop = build(medium +
                                   "comp c1 coupler kappa=0.1\ncomp c2 coupler kappa=0.15\ncomp w1 waveguide length=40\ncomp w2 waveguide length=40\n"
                                   "link c1.4 w1.1\nlink w1.2 c2.4\nlink c2.2 w2.1\nlink w2.2 c1.2\nport in c1.1\nport through c1.3\nport drop c2.1\nport add c2.3\n");
    {
        const double lambda = 1.5533, t1 = std::sqrt(0.9), t2 = std::sqrt(0.85), k1 = std::sqrt(0.1), k2 = std::sqrt(0.15);
        const cplx half = m.propagate(lambda, 40.0), loop = half * half;
        const CMatrix s = add_drop.solve(lambda);
        CHECK(std::abs(s(2, 0) - (-k1 * k2 * half) / (1.0 - t1 * t2 * loop)) < 1e-12);
        CHECK(std::abs(s(1, 0) - (t1 - t2 * loop) / (1.0 - t1 * t2 * loop)) < 1e-12);
        CHECK(std::abs(s(3, 0)) < 1e-14);  // nothing reaches the add port
        CHECK(reciprocity_defect(s) < 1e-13 && max_column_power(s) < 1.0);
    }

    // Fabry-Perot between two partial reflectors: Airy transmission
    const Circuit fp = build("medium lambda0=1.55 neff=2.4 ng=4.2 loss_db_cm=0\ncomp m1 reflector reflectivity=0.5\ncomp w waveguide length=60\ncomp m2 reflector reflectivity=0.5\n"
                             "link m1.2 w.1\nlink w.2 m2.1\nport in m1.1\nport out m2.2\n");
    {
        const Medium lossless{1.55, 2.4, 4.2, 0.0};
        for (double lambda : {1.5412, 1.55, 1.5591}) {
            const double phi = lossless.beta(lambda) * 60.0;
            const double airy = 0.25 / (1.0 + 0.25 - 2.0 * 0.5 * std::cos(2.0 * phi));
            const CMatrix s = fp.solve(lambda);
            CHECK_NEAR(std::norm(s(1, 0)), airy, 1e-12);
            CHECK(unitarity_defect(s) < 1e-12);
        }
    }

    // an unlinked port absorbs
    const Circuit open = build("comp s splitter\nport in s.1\nport a s.2\n");
    CHECK(open.open_ports() == 1);
    CHECK_NEAR(std::norm(open.solve(1.55)(1, 0)), 0.5, 1e-15);

    CHECK_THROWS(build("comp a waveguide length=1\nlink a.1 b.1\nport in a.2\n"));
    CHECK_THROWS(build("comp a waveguide length=1\nport in a.3\n"));
    CHECK_THROWS(build("comp a waveguide length=1\nport in a.1\nport out a.1\n"));
    CHECK_THROWS(build("comp a prism angle=3\nport in a.1\n"));
    CHECK_THROWS(build("comp a waveguide\nport in a.1\n"));
}
