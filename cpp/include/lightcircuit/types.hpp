// Complex scalars and a small dense complex matrix.
#pragma once

#include <complex>
#include <cstddef>
#include <vector>

namespace lc {

using cplx = std::complex<double>;
using Vector = std::vector<double>;
constexpr double PI = 3.14159265358979323846;
constexpr double LIGHT_SPEED_UM_PER_PS = 299.792458;  // micrometres per picosecond

struct CMatrix {
    std::size_t rows = 0, cols = 0;
    std::vector<cplx> a;

    CMatrix() = default;
    CMatrix(std::size_t r, std::size_t c) : rows(r), cols(c), a(r * c, cplx(0.0, 0.0)) {}

    cplx& operator()(std::size_t i, std::size_t j) { return a[i * cols + j]; }
    const cplx& operator()(std::size_t i, std::size_t j) const { return a[i * cols + j]; }
};

CMatrix identity(std::size_t n);
CMatrix multiply(const CMatrix& x, const CMatrix& y);
CMatrix adjoint(const CMatrix& m);  // conjugate transpose

// Largest |element| of (S^H S - I): zero for a lossless component.
double unitarity_defect(const CMatrix& s);

// Largest |S(i,j) - S(j,i)|: zero for a reciprocal component.
double reciprocity_defect(const CMatrix& s);

// Largest singular value squared is at most this bound: the largest column sum of |S|^2 (a quick passivity indicator).
double max_column_power(const CMatrix& s);

}  // namespace lc
