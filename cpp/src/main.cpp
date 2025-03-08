// Command line front end.
//
//   lightcircuit run <netlist>     solve, print metrics, checks and the spectrum
//   lightcircuit check <netlist>   solve and print the checks only; exit status 1 if any fails
//   lightcircuit info <netlist>    print the structure without solving
//
// Output lines: `key value`, `metric <port> <name> <value>`, `check <PASS|FAIL> <name> :: <detail>`,
// and for `run` one `row` per wavelength: wavelength, then power in dB for each port, then phase in radians for each port.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <string>

#include "lightcircuit/analysis.hpp"
#include "lightcircuit/circuit.hpp"
#include "lightcircuit/expect.hpp"
#include "lightcircuit/sweep.hpp"

using namespace lc;

static int run(const std::string& command, const std::string& path) {
    const Netlist n = read_netlist(path);
    const Circuit circuit(n);
    std::printf("title %s\n", n.title.c_str());
    std::printf("components %zu\ncomponent_ports %zu\nopen_ports %zu\n", n.components.size(), circuit.total_ports(), circuit.open_ports());
    std::printf("ports");
    for (const std::string& p : circuit.external_names()) std::printf(" %s", p.c_str());
    std::printf("\nexcite %s\npoints %zu\n", n.excite.c_str(), n.sweep_points);
    if (command == "info") return 0;

    const Spectrum sp = sweep(circuit, n);
    std::printf("power_defect %.6e\nunitarity_defect %.6e\nreciprocity_defect %.6e\nmax_power %.12f\n", sp.power_defect, sp.unitarity_defect, sp.reciprocity_defect, sp.max_power);
    const double centre = 0.5 * (sp.lambda.front() + sp.lambda.back());
    for (std::size_t p = 0; p < sp.ports.size(); ++p) {
        const Vector db = sp.power_db(p);
        const char* name = sp.ports[p].c_str();
        std::printf("metric %s max_db %.6f\nmetric %s min_db %.6f\n", name, *std::max_element(db.begin(), db.end()), name, *std::min_element(db.begin(), db.end()));
        std::printf("metric %s center_db %.6f\n", name, power_to_db(interpolate(sp.lambda, sp.power(p), centre)));
        for (bool dips : {true, false}) {
            const auto features = find_features(sp.lambda, db, dips, n.feature_db);
            const char* what = dips ? "dips" : "peaks";
            std::printf("metric %s %s %zu\n", name, what, features.size());
            if (features.size() >= 2) std::printf("metric %s %s_fsr_nm %.6f\n", name, what, mean_spacing_nm(features));
            if (!features.empty()) {
                const Feature& f = nearest_feature(features, centre);
                const double width = full_width_nm(sp.lambda, sp.power(p), features, f, dips);
                std::printf("metric %s %s_lambda_um %.8f\n", name, what, f.lambda);
                if (std::isfinite(width) && width > 0.0) std::printf("metric %s %s_fwhm_nm %.6f\nmetric %s %s_q %.1f\n", name, what, width, name, what, 1e3 * f.lambda / width);
            }
        }
    }
    int failed = 0;
    for (const CheckResult& c : evaluate(n, sp)) {
        std::printf("check %s %s :: %s\n", c.pass ? "PASS" : "FAIL", c.name.c_str(), c.detail.c_str());
        failed += !c.pass;
    }
    if (command == "check") return failed == 0 ? 0 : 1;
    std::vector<Vector> db, phase;
    for (std::size_t p = 0; p < sp.ports.size(); ++p) db.push_back(sp.power_db(p)), phase.push_back(sp.phase(p));
    for (std::size_t i = 0; i < sp.lambda.size(); ++i) {
        std::printf("row %.12f", sp.lambda[i]);
        for (const Vector& v : db) std::printf(" %.10f", v[i]);
        for (const Vector& v : phase) std::printf(" %.8f", v[i]);
        std::printf("\n");
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3 || (std::string(argv[1]) != "run" && std::string(argv[1]) != "check" && std::string(argv[1]) != "info")) {
        std::fprintf(stderr, "usage: lightcircuit <run|check|info> <netlist>\n");
        return 2;
    }
    try {
        return run(argv[1], argv[2]);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "lightcircuit: %s\n", e.what());
        return 2;
    }
}
