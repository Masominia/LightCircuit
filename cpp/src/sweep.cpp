#include "lightcircuit/sweep.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace lc {

Vector Spectrum::power(std::size_t port) const {
    Vector p(lambda.size());
    for (std::size_t i = 0; i < p.size(); ++i) p[i] = std::norm(amplitude[port][i]);
    return p;
}

Vector Spectrum::power_db(std::size_t port) const {
    Vector p = power(port);
    for (double& v : p) v = power_to_db(v);
    return p;
}

Vector Spectrum::phase(std::size_t port) const {
    Vector ph(lambda.size());
    double offset = 0.0, previous = 0.0;
    for (std::size_t i = 0; i < ph.size(); ++i) {
        const double raw = std::arg(amplitude[port][i]);
        if (i > 0) {
            const double step = raw - previous;
            if (step > PI) offset -= 2.0 * PI;
            if (step < -PI) offset += 2.0 * PI;
        }
        previous = raw;
        ph[i] = raw + offset;
    }
    return ph;
}

std::size_t Spectrum::port_index(const std::string& name) const {
    const auto it = std::find(ports.begin(), ports.end(), name);
    if (it == ports.end()) throw std::invalid_argument("unknown port '" + name + "'");
    return static_cast<std::size_t>(it - ports.begin());
}

Spectrum sweep(const Circuit& circuit, const Netlist& n) {
    Spectrum sp;
    sp.ports = circuit.external_names();
    sp.excited = sp.port_index(n.excite);
    sp.lambda.resize(n.sweep_points);
    sp.amplitude.assign(sp.ports.size(), std::vector<cplx>(n.sweep_points));
    for (std::size_t i = 0; i < n.sweep_points; ++i) {
        const double lambda = n.sweep_from + (n.sweep_to - n.sweep_from) * static_cast<double>(i) / static_cast<double>(n.sweep_points - 1);
        sp.lambda[i] = lambda;
        const CMatrix s = circuit.solve(lambda);
        double total = 0.0;
        for (std::size_t p = 0; p < sp.ports.size(); ++p) {
            sp.amplitude[p][i] = s(p, sp.excited);
            total += std::norm(s(p, sp.excited));
        }
        sp.power_defect = std::max(sp.power_defect, std::fabs(total - 1.0));
        sp.unitarity_defect = std::max(sp.unitarity_defect, unitarity_defect(s));
        sp.reciprocity_defect = std::max(sp.reciprocity_defect, reciprocity_defect(s));
        sp.max_power = std::max(sp.max_power, max_column_power(s));
    }
    return sp;
}

}  // namespace lc
