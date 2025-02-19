#include "lightcircuit/circuit.hpp"

#include <stdexcept>

#include "lightcircuit/lu.hpp"

namespace lc {

Circuit::Circuit(const Netlist& n) {
    for (const ComponentSpec& spec : n.components) {
        try {
            components_.push_back(make_component(spec.kind, spec.params, n.medium));
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("component '" + spec.name + "': " + e.what());
        }
        component_names_.push_back(spec.name);
        offset_.push_back(total_);
        total_ += components_.back()->ports();
    }
    partner_.assign(total_, -1);
    std::vector<char> used(total_, 0);
    auto claim = [&](const PortRef& ref) {
        const std::size_t g = global_index(ref);
        if (used[g]) throw std::runtime_error("port " + ref.component + "." + std::to_string(ref.port) + " is used more than once");
        used[g] = 1;
        return g;
    };
    for (const Link& link : n.links) {
        const std::size_t a = claim(link.a), b = claim(link.b);
        partner_[a] = static_cast<long>(b);
        partner_[b] = static_cast<long>(a);
    }
    for (const ExternalPort& p : n.ports) {
        external_.push_back(claim(p.at));
        names_.push_back(p.name);
    }
}

std::size_t Circuit::global_index(const PortRef& ref) const {
    for (std::size_t c = 0; c < component_names_.size(); ++c)
        if (component_names_[c] == ref.component) {
            if (ref.port < 1 || ref.port > components_[c]->ports())
                throw std::runtime_error("component '" + ref.component + "' (" + components_[c]->kind() + ") has no port " + std::to_string(ref.port));
            return offset_[c] + ref.port - 1;
        }
    throw std::runtime_error("unknown component '" + ref.component + "'");
}

std::size_t Circuit::open_ports() const {
    std::size_t open = total_;
    for (long p : partner_) open -= p >= 0;
    return open - external_.size();
}

CMatrix Circuit::solve(double lambda) const {
    // global block-diagonal scattering matrix
    CMatrix s(total_, total_);
    for (std::size_t c = 0; c < components_.size(); ++c) {
        const CMatrix block = components_[c]->scattering(lambda);
        for (std::size_t i = 0; i < block.rows; ++i)
            for (std::size_t j = 0; j < block.cols; ++j) s(offset_[c] + i, offset_[c] + j) = block(i, j);
    }
    // the wave entering a linked port is the wave leaving its partner: a = P b + a_external
    CMatrix system = identity(total_);
    for (std::size_t k = 0; k < total_; ++k) {
        if (partner_[k] < 0) continue;
        const std::size_t j = static_cast<std::size_t>(partner_[k]);
        for (std::size_t i = 0; i < total_; ++i) system(i, k) -= s(i, j);
    }
    const LU lu(std::move(system));
    CMatrix out(external_.size(), external_.size());
    std::vector<cplx> rhs(total_);
    for (std::size_t e = 0; e < external_.size(); ++e) {
        for (std::size_t i = 0; i < total_; ++i) rhs[i] = s(i, external_[e]);
        const std::vector<cplx> b = lu.solve(rhs);
        for (std::size_t h = 0; h < external_.size(); ++h) out(h, e) = b[external_[h]];
    }
    return out;
}

}  // namespace lc
