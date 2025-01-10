#include <algorithm>
#include <stdexcept>

#include "lightcircuit/types.hpp"

namespace lc {

CMatrix identity(std::size_t n) {
    CMatrix m(n, n);
    for (std::size_t i = 0; i < n; ++i) m(i, i) = 1.0;
    return m;
}

CMatrix multiply(const CMatrix& x, const CMatrix& y) {
    if (x.cols != y.rows) throw std::invalid_argument("multiply: shapes do not match");
    CMatrix z(x.rows, y.cols);
    for (std::size_t i = 0; i < x.rows; ++i)
        for (std::size_t k = 0; k < x.cols; ++k) {
            const cplx v = x(i, k);
            if (v == cplx(0.0, 0.0)) continue;
            for (std::size_t j = 0; j < y.cols; ++j) z(i, j) += v * y(k, j);
        }
    return z;
}

CMatrix adjoint(const CMatrix& m) {
    CMatrix t(m.cols, m.rows);
    for (std::size_t i = 0; i < m.rows; ++i)
        for (std::size_t j = 0; j < m.cols; ++j) t(j, i) = std::conj(m(i, j));
    return t;
}

double unitarity_defect(const CMatrix& s) {
    const CMatrix p = multiply(adjoint(s), s);
    double worst = 0.0;
    for (std::size_t i = 0; i < p.rows; ++i)
        for (std::size_t j = 0; j < p.cols; ++j) worst = std::max(worst, std::abs(p(i, j) - (i == j ? 1.0 : 0.0)));
    return worst;
}

double reciprocity_defect(const CMatrix& s) {
    double worst = 0.0;
    for (std::size_t i = 0; i < s.rows; ++i)
        for (std::size_t j = 0; j < i; ++j) worst = std::max(worst, std::abs(s(i, j) - s(j, i)));
    return worst;
}

double max_column_power(const CMatrix& s) {
    double worst = 0.0;
    for (std::size_t j = 0; j < s.cols; ++j) {
        double p = 0.0;
        for (std::size_t i = 0; i < s.rows; ++i) p += std::norm(s(i, j));
        worst = std::max(worst, p);
    }
    return worst;
}

}  // namespace lc
