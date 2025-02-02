#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// A lossless partial reflector between ports 1 and 2: reflection r on both sides, transmission i t,
// with r^2 = reflectivity and r^2 + t^2 = 1.
class Reflector : public Component {
  public:
    explicit Reflector(double reflectivity);
    std::size_t ports() const override { return 2; }
    const char* kind() const override { return "reflector"; }
    CMatrix scattering(double lambda) const override;

  private:
    double r_, t_;
};

// One port that sends back a fraction of the power; reflectivity zero is a perfect absorber.
class Mirror : public Component {
  public:
    Mirror(double reflectivity, double phase);
    std::size_t ports() const override { return 1; }
    const char* kind() const override { return "mirror"; }
    CMatrix scattering(double lambda) const override;

  private:
    cplx r_;
};

}  // namespace lc
