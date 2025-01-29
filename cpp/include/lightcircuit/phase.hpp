#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// A wavelength-independent phase shift between ports 1 and 2 (a heater, to first order).
class PhaseShifter : public Component {
  public:
    explicit PhaseShifter(double phi) : phi_(phi) {}
    std::size_t ports() const override { return 2; }
    const char* kind() const override { return "phase"; }
    CMatrix scattering(double lambda) const override;

  private:
    double phi_;
};

// A wavelength-independent power loss in decibels between ports 1 and 2.
class Attenuator : public Component {
  public:
    explicit Attenuator(double db);
    std::size_t ports() const override { return 2; }
    const char* kind() const override { return "attenuator"; }
    CMatrix scattering(double lambda) const override;

  private:
    double amplitude_;
};

}  // namespace lc
