#include "check.hpp"
#include "lightcircuit/lu.hpp"

using namespace lc;

void test_lu(Suite& suite) {
    // needs a row exchange
    CMatrix a(3, 3);
    const cplx v[3][3] = {{cplx(0, 0), cplx(2, 1), cplx(1, 0)}, {cplx(1, -1), cplx(1, 0), cplx(0, 0)}, {cplx(2, 0), cplx(0, 0), cplx(0, 3)}};
    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j) a(i, j) = v[i][j];
    const std::vector<cplx> x_true = {cplx(1, 2), cplx(-1, 0.5), cplx(0, -3)};
    std::vector<cplx> b(3);
    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j) b[i] += a(i, j) * x_true[j];
    const LU lu(a);
    const std::vector<cplx> x = lu.solve(b);
    for (std::size_t i = 0; i < 3; ++i) CHECK(std::abs(x[i] - x_true[i]) < 1e-13);
    CHECK(lu.pivot_ratio() > 0.0 && lu.pivot_ratio() <= 1.0);
    // a second right-hand side with the same factorisation
    const std::vector<cplx> e = lu.solve({cplx(1, 0), cplx(0, 0), cplx(0, 0)});
    cplx back = 0.0;
    for (std::size_t j = 0; j < 3; ++j) back += a(1, j) * e[j];
    CHECK(std::abs(back) < 1e-13);

    CMatrix singular(2, 2);
    singular(0, 0) = singular(0, 1) = singular(1, 0) = singular(1, 1) = 1.0;
    CHECK_THROWS(LU(singular));
    CHECK_THROWS(LU(CMatrix(2, 3)));
    CHECK_THROWS(lu.solve({cplx(1, 0)}));
}
