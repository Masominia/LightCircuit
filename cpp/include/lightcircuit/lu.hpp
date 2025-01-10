// LU factorisation of a complex matrix with partial pivoting.
#pragma once

#include "lightcircuit/types.hpp"

namespace lc {

class LU {
  public:
    // Throws std::runtime_error if the matrix is singular to working precision.
    explicit LU(CMatrix a);

    // Solves A x = b for one right-hand side.
    std::vector<cplx> solve(std::vector<cplx> b) const;

    // Ratio of the smallest to the largest pivot magnitude: a rough indicator of conditioning.
    double pivot_ratio() const { return pivot_ratio_; }

  private:
    CMatrix lu_;
    std::vector<std::size_t> perm_;
    double pivot_ratio_ = 1.0;
};

}  // namespace lc
