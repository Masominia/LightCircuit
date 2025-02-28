// The response of a circuit over a range of wavelengths.
#pragma once

#include <string>
#include <vector>

#include "lightcircuit/circuit.hpp"

namespace lc {

struct Spectrum {
    Vector lambda;                            // micrometres
    std::vector<std::string> ports;           // external port names
    std::size_t excited = 0;                  // index of the driven port
    std::vector<std::vector<cplx>> amplitude; // amplitude[port][point], for unit input at the driven port
    double power_defect = 0.0;                // largest |total output power - 1| over the sweep, driven port only
    double unitarity_defect = 0.0;            // largest departure of the full external matrix from unitary
    double reciprocity_defect = 0.0;
    double max_power = 0.0;                   // largest total output power for any single input

    Vector power_db(std::size_t port) const;
    Vector power(std::size_t port) const;
    Vector phase(std::size_t port) const;     // unwrapped, radians
    std::size_t port_index(const std::string& name) const;  // throws if unknown
};

Spectrum sweep(const Circuit& circuit, const Netlist& netlist);

}  // namespace lc
