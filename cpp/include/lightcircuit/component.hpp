// A component is a scattering matrix that may depend on wavelength.
#pragma once

#include <memory>
#include <string>

#include "lightcircuit/medium.hpp"
#include "lightcircuit/strutil.hpp"
#include "lightcircuit/types.hpp"

namespace lc {

class Component {
  public:
    virtual ~Component() = default;
    virtual std::size_t ports() const = 0;
    virtual const char* kind() const = 0;
    // b = S a, with a the incoming and b the outgoing amplitudes at the component's ports.
    virtual CMatrix scattering(double lambda) const = 0;
};

// Builds a component from its kind and parameters; `medium` supplies defaults for waveguide properties.
// Kinds: waveguide, phase, attenuator, coupler, splitter, reflector, mirror, terminator, bragg.
std::unique_ptr<Component> make_component(const std::string& kind, const Params& params, const Medium& medium);

// The medium with any of neff, ng, loss_db_cm overridden by the parameters.
Medium local_medium(const Params& params, const Medium& medium);

}  // namespace lc
