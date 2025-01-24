#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// Y-branch: port 1 is the stem, ports 2 and 3 the arms. `ratio` is the share of power sent to port 2.
// Reciprocal and matched at the stem; light entering the arms out of phase is lost, as in a real Y-branch.
class Splitter : public Component {
  public:
    Splitter(double ratio, double excess_db);
    std::size_t ports() const override { return 3; }
    const char* kind() const override { return "splitter"; }
    CMatrix scattering(double lambda) const override;

  private:
    double a2_, a3_;
};

}  // namespace lc
