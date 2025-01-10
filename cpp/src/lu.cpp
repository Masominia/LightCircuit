#include "lightcircuit/lu.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace lc {

LU::LU(CMatrix a) : lu_(std::move(a)) {
    if (lu_.rows != lu_.cols) throw std::invalid_argument("LU: matrix is not square");
    const std::size_t n = lu_.rows;
    perm_.resize(n);
    double smallest = 1e300, largest = 0.0;
    for (std::size_t k = 0; k < n; ++k) {
        std::size_t pivot = k;
        for (std::size_t r = k + 1; r < n; ++r)
            if (std::abs(lu_(r, k)) > std::abs(lu_(pivot, k))) pivot = r;
        const double mag = std::abs(lu_(pivot, k));
        if (mag < 1e-14) throw std::runtime_error("LU: singular matrix (a lossless loop exactly on resonance?)");
        smallest = std::min(smallest, mag);
        largest = std::max(largest, mag);
        perm_[k] = pivot;
        if (pivot != k)
            for (std::size_t c = 0; c < n; ++c) std::swap(lu_(k, c), lu_(pivot, c));
        for (std::size_t r = k + 1; r < n; ++r) {
            const cplx f = lu_(r, k) / lu_(k, k);
            if (f == cplx(0.0, 0.0)) continue;
            lu_(r, k) = f;
            for (std::size_t c = k + 1; c < n; ++c) lu_(r, c) -= f * lu_(k, c);
        }
    }
    pivot_ratio_ = n > 0 ? smallest / largest : 1.0;
}

std::vector<cplx> LU::solve(std::vector<cplx> b) const {
    const std::size_t n = lu_.rows;
    if (b.size() != n) throw std::invalid_argument("LU::solve: right-hand side has the wrong size");
    // the factorisation exchanged whole rows, multipliers included, so all exchanges come first
    for (std::size_t k = 0; k < n; ++k)
        if (perm_[k] != k) std::swap(b[k], b[perm_[k]]);
    for (std::size_t k = 0; k < n; ++k)
        for (std::size_t r = k + 1; r < n; ++r) b[r] -= lu_(r, k) * b[k];
    for (std::size_t i = n; i-- > 0;) {
        for (std::size_t c = i + 1; c < n; ++c) b[i] -= lu_(i, c) * b[c];
        b[i] /= lu_(i, i);
    }
    return b;
}

}  // namespace lc
