#pragma once

#include "lightcircuit/component.hpp"

namespace lc {

// Uniform Bragg grating by coupled-mode theory. `kappa` is the coupling coefficient per micrometre,
// `bragg_lambda` the wavelength of peak reflection. Ports 1 and 2; lossless.
class Bragg : public Component {
  public:
    Bragg(const Medium& medium, double length, double kappa, double bragg_lambda);
    std::size_t ports() const override { return 2; }
    const char* kind() const override { return "bragg"; }
    CMatrix scattering(double lambda) const override;

    // Peak power reflectivity tanh^2(kappa L).
    double peak_reflectivity() const;

  private:
    Medium medium_;
    double length_, kappa_, beta_bragg_;
};

}  // namespace lc
