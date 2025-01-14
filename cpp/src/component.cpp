#include "lightcircuit/component.hpp"

#include <stdexcept>

#include "lightcircuit/bragg.hpp"
#include "lightcircuit/coupler.hpp"
#include "lightcircuit/phase.hpp"
#include "lightcircuit/reflector.hpp"
#include "lightcircuit/splitter.hpp"
#include "lightcircuit/waveguide.hpp"

namespace lc {

Medium local_medium(const Params& p, const Medium& medium) {
    Medium m = medium;
    m.neff = get(p, "neff", m.neff);
    m.ng = get(p, "ng", m.ng);
    m.loss_db_cm = get(p, "loss_db_cm", m.loss_db_cm);
    return m;
}

std::unique_ptr<Component> make_component(const std::string& kind, const Params& p, const Medium& medium) {
    if (kind == "waveguide") return std::make_unique<Waveguide>(local_medium(p, medium), require(p, "length", kind), get(p, "phase", 0.0));
    if (kind == "phase") return std::make_unique<PhaseShifter>(require(p, "phi", kind));
    if (kind == "attenuator") return std::make_unique<Attenuator>(require(p, "db", kind));
    if (kind == "coupler") return std::make_unique<Coupler>(require(p, "kappa", kind), get(p, "excess_db", 0.0));
    if (kind == "splitter") return std::make_unique<Splitter>(get(p, "ratio", 0.5), get(p, "excess_db", 0.0));
    if (kind == "reflector") return std::make_unique<Reflector>(require(p, "reflectivity", kind));
    if (kind == "mirror") return std::make_unique<Mirror>(get(p, "reflectivity", 1.0), get(p, "phase", 0.0));
    if (kind == "terminator") return std::make_unique<Mirror>(0.0, 0.0);
    if (kind == "bragg") return std::make_unique<Bragg>(local_medium(p, medium), require(p, "length", kind), require(p, "kappa", kind), require(p, "bragg_lambda", kind));
    throw std::invalid_argument("unknown component kind '" + kind + "'");
}

}  // namespace lc
