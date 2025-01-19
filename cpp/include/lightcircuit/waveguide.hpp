#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// A length of waveguide: ports 1 and 2, transmission exp(i beta L - alpha L) plus an optional fixed phase, no reflection.
class Waveguide : public Component {
  public:
    Waveguide(const Medium& medium, double length, double extra_phase);
    std::size_t ports() const override { return 2; }
    const char* kind() const override { return "waveguide"; }
    CMatrix scattering(double lambda) const override;

  private:
    Medium medium_;
    double length_, phase_;
};

}  // namespace lc
