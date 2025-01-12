#include "check.hpp"
#include "lightcircuit/types.hpp"

using namespace lc;

void test_cmatrix(Suite& suite) {
    CMatrix a(2, 2);
    a(0, 0) = cplx(1, 1), a(0, 1) = cplx(0, 2), a(1, 0) = cplx(3, 0), a(1, 1) = cplx(0, -1);
    const CMatrix p = multiply(a, identity(2));
    CHECK(p(0, 1) == cplx(0, 2) && p(1, 1) == cplx(0, -1));
    const CMatrix h = adjoint(a);
    CHECK(h(0, 1) == cplx(3, 0) && h(1, 0) == cplx(0, -2) && h(0, 0) == cplx(1, -1));
    const CMatrix sq = multiply(a, a);
    CHECK(sq(0, 0) == cplx(1, 1) * cplx(1, 1) + cplx(0, 2) * cplx(3, 0));
    CHECK_THROWS(multiply(a, CMatrix(3, 1)));

    // a rotation is unitary but not symmetric
    CMatrix rot(2, 2);
    rot(0, 0) = rot(1, 1) = std::cos(0.3);
    rot(0, 1) = -std::sin(0.3), rot(1, 0) = std::sin(0.3);
    CHECK(unitarity_defect(rot) < 1e-15);
    CHECK_NEAR(reciprocity_defect(rot), 2.0 * std::sin(0.3), 1e-15);
    CHECK_NEAR(max_column_power(rot), 1.0, 1e-15);
    CMatrix half = identity(2);
    half(1, 1) = 0.5;
    CHECK_NEAR(unitarity_defect(half), 0.75, 1e-15);
    CHECK(reciprocity_defect(half) == 0.0);
}
