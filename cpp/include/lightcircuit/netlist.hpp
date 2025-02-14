// The text description of a circuit.
#pragma once

#include <string>
#include <vector>

#include "lightcircuit/medium.hpp"
#include "lightcircuit/strutil.hpp"

namespace lc {

struct ComponentSpec {
    std::string name, kind;
    Params params;
};

struct PortRef {
    std::string component;
    std::size_t port = 0;  // 1-based, as written
};

struct Link {
    PortRef a, b;
};

struct ExternalPort {
    std::string name;
    PortRef at;
};

struct Expectation {
    std::string kind;
    std::vector<std::string> args;
    int line = 0;
};

struct Netlist {
    std::string title;
    Medium medium;
    double sweep_from = 1.5, sweep_to = 1.6;
    std::size_t sweep_points = 1001;
    double feature_db = 3.0;  // smallest prominence of a dip or peak that counts as a resonance
    std::vector<ComponentSpec> components;
    std::vector<Link> links;
    std::vector<ExternalPort> ports;
    std::string excite;  // name of the external port that is driven
    std::vector<Expectation> expectations;
};

// Statements, one per line, '#' starts a comment:
//   title <text>
//   medium lambda0=.. neff=.. ng=.. loss_db_cm=..
//   sweep <from um> <to um> <points>
//   feature <dB>
//   comp <name> <kind> key=value ...
//   link <comp.port> <comp.port>
//   port <name> <comp.port>
//   excite <port name>
//   expect <kind> <args...>
// Throws std::runtime_error with the line number on any error.
Netlist parse_netlist(const std::string& text);
Netlist read_netlist(const std::string& path);

PortRef parse_port_ref(const std::string& text);

}  // namespace lc
