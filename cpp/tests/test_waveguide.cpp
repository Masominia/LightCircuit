#include "check.hpp"
#include "lightcircuit/phase.hpp"
#include "lightcircuit/waveguide.hpp"

using namespace lc;

void test_waveguide(Suite& suite) {
    const Medium m{1.55, 2.4, 4.2, 0.0};
    const Waveguide w(m, 50.0, 0.0);
    const CMatrix s = w.scattering(1.56);
    CHECK(w.ports() == 2 && s(0, 0) == cplx(0, 0) && s(1, 1) == cplx(0, 0));
    CHECK(std::abs(s(0, 1) - m.propagate(1.56, 50.0)) < 1e-15 && s(0, 1) == s(1, 0));
    CHECK(unitarity_defect(s) < 1e-14);
    // two halves make the whole
    const CMatrix half = Waveguide(m, 25.0, 0.0).scattering(1.56);
    CHECK(std::abs(half(1, 0) * half(1, 0) - s(1, 0)) < 1e-13);
    // an extra phase of pi flips the sign
    CHECK(std::abs(Waveguide(m, 50.0, PI).scattering(1.56)(1, 0) + s(1, 0)) < 1e-13);
    CHECK_THROWS(Waveguide(m, -1.0, 0.0));

    CHECK(std::abs(PhaseShifter(PI / 2).scattering(1.5)(1, 0) - cplx(0, 1)) < 1e-15);
    const CMatrix att = Attenuator(3.0).scattering(1.5);
    CHECK_NEAR(power_to_db(std::norm(att(1, 0))), -3.0, 1e-12);
    CHECK(reciprocity_defect(att) == 0.0);
    CHECK_THROWS(Attenuator(-1.0));
}
