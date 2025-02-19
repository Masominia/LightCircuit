// A netlist turned into something that can be solved at a wavelength.
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "lightcircuit/component.hpp"
#include "lightcircuit/netlist.hpp"

namespace lc {

class Circuit {
  public:
    // Throws std::runtime_error on unknown components, bad port numbers or a port used twice.
    explicit Circuit(const Netlist& netlist);

    std::size_t external_count() const { return external_.size(); }
    const std::vector<std::string>& external_names() const { return names_; }
    std::size_t total_ports() const { return total_; }

    // Component ports that are neither linked nor external. Light leaving through them is lost.
    std::size_t open_ports() const;

    // Scattering matrix between the external ports: element (i, j) is the amplitude leaving port i for unit input at port j.
    // All internal reflections and feedback loops are included exactly, by solving (I - S P) b = S a.
    CMatrix solve(double lambda) const;

  private:
    std::size_t global_index(const PortRef& ref) const;

    std::vector<std::unique_ptr<Component>> components_;
    std::vector<std::string> component_names_;
    std::vector<std::size_t> offset_;
    std::vector<long> partner_;          // linked port for every global port, or -1
    std::vector<std::size_t> external_;  // global index of each external port
    std::vector<std::string> names_;
    std::size_t total_ = 0;
};

}  // namespace lc
