#include "lightcircuit/netlist.hpp"

#include <fstream>
#include <set>
#include <sstream>
#include <stdexcept>

namespace lc {

PortRef parse_port_ref(const std::string& text) {
    const auto dot = text.rfind('.');
    if (dot == std::string::npos || dot == 0 || dot + 1 == text.size()) throw std::invalid_argument("expected component.port, got '" + text + "'");
    PortRef r;
    r.component = text.substr(0, dot);
    const double n = to_number(text.substr(dot + 1));
    if (n < 1.0 || n != static_cast<double>(static_cast<std::size_t>(n))) throw std::invalid_argument("port numbers start at 1: '" + text + "'");
    r.port = static_cast<std::size_t>(n);
    return r;
}

Netlist parse_netlist(const std::string& text) {
    Netlist n;
    std::set<std::string> names, port_names;
    std::istringstream in(text);
    std::string raw;
    int number = 0;
    while (std::getline(in, raw)) {
        ++number;
        const std::string line = strip_comment(raw);
        if (line.empty()) continue;
        const std::vector<std::string> w = split_words(line);
        try {
            const std::string& key = w[0];
            if (key == "title") {
                n.title = line.size() > 6 ? line.substr(6) : "";
            } else if (key == "medium") {
                const Params p = parse_params(w, 1);
                n.medium.lambda0 = get(p, "lambda0", n.medium.lambda0);
                n.medium.neff = get(p, "neff", n.medium.neff);
                n.medium.ng = get(p, "ng", n.medium.ng);
                n.medium.loss_db_cm = get(p, "loss_db_cm", n.medium.loss_db_cm);
            } else if (key == "sweep") {
                if (w.size() != 4) throw std::invalid_argument("sweep needs: from to points");
                n.sweep_from = to_number(w[1]);
                n.sweep_to = to_number(w[2]);
                const double pts = to_number(w[3]);
                if (!(n.sweep_to > n.sweep_from) || n.sweep_from <= 0.0 || pts < 2.0) throw std::invalid_argument("sweep needs 0 < from < to and at least two points");
                n.sweep_points = static_cast<std::size_t>(pts);
            } else if (key == "feature") {
                if (w.size() != 2) throw std::invalid_argument("feature needs one number");
                n.feature_db = to_number(w[1]);
            } else if (key == "comp") {
                if (w.size() < 3) throw std::invalid_argument("comp needs: name kind [key=value ...]");
                if (!names.insert(w[1]).second) throw std::invalid_argument("component '" + w[1] + "' defined twice");
                n.components.push_back({w[1], w[2], parse_params(w, 3)});
            } else if (key == "link") {
                if (w.size() != 3) throw std::invalid_argument("link needs two component.port references");
                n.links.push_back({parse_port_ref(w[1]), parse_port_ref(w[2])});
            } else if (key == "port") {
                if (w.size() != 3) throw std::invalid_argument("port needs: name component.port");
                if (!port_names.insert(w[1]).second) throw std::invalid_argument("port '" + w[1] + "' defined twice");
                n.ports.push_back({w[1], parse_port_ref(w[2])});
            } else if (key == "excite") {
                if (w.size() != 2) throw std::invalid_argument("excite needs one port name");
                n.excite = w[1];
            } else if (key == "expect") {
                if (w.size() < 2) throw std::invalid_argument("expect needs a kind");
                n.expectations.push_back({w[1], std::vector<std::string>(w.begin() + 2, w.end()), number});
            } else {
                throw std::invalid_argument("unknown statement '" + key + "'");
            }
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("line " + std::to_string(number) + ": " + e.what());
        }
    }
    if (n.components.empty()) throw std::runtime_error("the netlist defines no components");
    if (n.ports.empty()) throw std::runtime_error("the netlist defines no external ports");
    if (n.excite.empty()) n.excite = n.ports.front().name;
    if (!port_names.count(n.excite)) throw std::runtime_error("excite names an unknown port '" + n.excite + "'");
    return n;
}

Netlist read_netlist(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open " + path);
    std::stringstream ss;
    ss << in.rdbuf();
    return parse_netlist(ss.str());
}

}  // namespace lc
