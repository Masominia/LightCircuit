#include "check.hpp"
#include "lightcircuit/netlist.hpp"

using namespace lc;

static const char* kRing =
    "title All-pass ring  # with a comment\n"
    "medium lambda0=1.31 neff=2.5 ng=4.4 loss_db_cm=1.5\n"
    "sweep 1.30 1.32 501\n"
    "feature 6\n"
    "\n"
    "comp c coupler kappa=0.1\n"
    "comp w waveguide length=100 loss_db_cm=3\n"
    "link c.4 w.1\n"
    "link w.2 c.2\n"
    "port in c.1\n"
    "port through c.3\n"
    "expect fsr through dips 3.9 0.01\n"
    "expect passive\n";

static std::string error_of(const std::string& text) {
    try {
        parse_netlist(text);
    } catch (const std::runtime_error& e) {
        return e.what();
    }
    return "";
}

void test_netlist(Suite& suite) {
    const Netlist n = parse_netlist(kRing);
    CHECK(n.title == "All-pass ring");
    CHECK(n.medium.lambda0 == 1.31 && n.medium.neff == 2.5 && n.medium.ng == 4.4 && n.medium.loss_db_cm == 1.5);
    CHECK(n.sweep_from == 1.30 && n.sweep_to == 1.32 && n.sweep_points == 501 && n.feature_db == 6.0);
    CHECK(n.components.size() == 2 && n.components[1].kind == "waveguide" && n.components[1].params.at("loss_db_cm") == 3.0);
    CHECK(n.links.size() == 2 && n.links[0].a.component == "c" && n.links[0].a.port == 4 && n.links[0].b.port == 1);
    CHECK(n.ports.size() == 2 && n.ports[1].name == "through" && n.excite == "in");
    CHECK(n.expectations.size() == 2 && n.expectations[0].kind == "fsr" && n.expectations[0].args.size() == 4 && n.expectations[0].line == 12);

    const PortRef r = parse_port_ref("ring.stage2.3");
    CHECK(r.component == "ring.stage2" && r.port == 3);
    CHECK_THROWS(parse_port_ref("ring"));
    CHECK_THROWS(parse_port_ref("ring.0"));
    CHECK_THROWS(parse_port_ref("ring.x"));

    // every error names its line
    CHECK(error_of("comp a coupler kappa=0.1\ncomp a coupler kappa=0.2\nport in a.1\n").find("line 2") != std::string::npos);
    CHECK(error_of("comp a coupler kappa\nport in a.1\n").find("line 1") != std::string::npos);
    CHECK(error_of("comp a coupler kappa=0.1\nwire a.1 a.2\n").find("unknown statement") != std::string::npos);
    CHECK(error_of("comp a coupler kappa=0.1\nport in a.1\nsweep 1.6 1.5 10\n").find("line 3") != std::string::npos);
    CHECK(error_of("port in a.1\n").find("no components") != std::string::npos);
    CHECK(error_of("comp a coupler kappa=0.1\n").find("no external ports") != std::string::npos);
    CHECK(error_of("comp a coupler kappa=0.1\nport in a.1\nexcite out\n").find("unknown port") != std::string::npos);
    CHECK_THROWS(read_netlist("no_such_file.net"));
}
