#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// Directional coupler. Ports 1 and 2 on one side, 3 and 4 on the other; 1 faces 3 and 2 faces 4.
// Power coupling kappa goes to the cross port with a quarter-wave phase: 1->3 is t, 1->4 is i k.
class Coupler : public Component {
  public:
    Coupler(double kappa, double excess_db);
    std::size_t ports() const override { return 4; }
    const char* kind() const override { return "coupler"; }
    CMatrix scattering(double lambda) const override;

  private:
    double t_, k_;
};

}  // namespace lc
