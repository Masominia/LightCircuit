#include "lightcircuit/expect.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stdexcept>

#include "lightcircuit/analysis.hpp"

namespace lc {

namespace {

std::string fmt(const char* format, double a, double b = 0.0, double c = 0.0) {
    char buf[200];
    std::snprintf(buf, sizeof buf, format, a, b, c);
    return buf;
}

bool is_dips(const std::string& word) {
    if (word == "dips") return true;
    if (word == "peaks") return false;
    throw std::invalid_argument("expected dips or peaks, got '" + word + "'");
}

void need(const Expectation& e, std::size_t n) {
    if (e.args.size() != n) throw std::invalid_argument("'" + e.kind + "' takes " + std::to_string(n) + " arguments");
}

double wrap_degrees(double d) {
    while (d > 180.0) d -= 360.0;
    while (d <= -180.0) d += 360.0;
    return d;
}

CheckResult one(const Netlist& n, const Spectrum& sp, const Expectation& e) {
    CheckResult r;
    r.name = e.kind;
    for (const std::string& a : e.args) r.name += " " + a;
    const double centre = 0.5 * (sp.lambda.front() + sp.lambda.back());
    const std::string& k = e.kind;
    if (k == "lossless" || k == "reciprocal") {
        if (e.args.size() > 1) throw std::invalid_argument("'" + k + "' takes at most one argument");
        const double tol = e.args.empty() ? 1e-9 : to_number(e.args[0]);
        const double defect = k == "lossless" ? sp.unitarity_defect : sp.reciprocity_defect;
        r.pass = defect <= tol;
        r.detail = fmt("defect %.2e, tolerance %.1e", defect, tol);
    } else if (k == "passive") {
        need(e, 0);
        r.pass = sp.max_power <= 1.0 + 1e-9;
        r.detail = fmt("largest output power %.9f", sp.max_power);
    } else if (k == "fsr" || k == "fwhm") {
        need(e, 4);
        const std::size_t p = sp.port_index(e.args[0]);
        const bool dips = is_dips(e.args[1]);
        const double want = to_number(e.args[2]), tol = to_number(e.args[3]);
        const auto features = find_features(sp.lambda, sp.power_db(p), dips, n.feature_db);
        const double got = k == "fsr" ? mean_spacing_nm(features) : full_width_nm(sp.lambda, sp.power(p), features, nearest_feature(features, centre), dips);
        r.pass = std::fabs(got / want - 1.0) <= tol;
        r.detail = fmt("%.5f nm, expected %.5f, relative error %.2e", got, want, got / want - 1.0);
    } else if (k == "count") {
        need(e, 3);
        const auto features = find_features(sp.lambda, sp.power_db(sp.port_index(e.args[0])), is_dips(e.args[1]), n.feature_db);
        const double want = to_number(e.args[2]);
        r.pass = static_cast<double>(features.size()) == want;
        r.detail = fmt("%.0f found, expected %.0f", static_cast<double>(features.size()), want);
    } else if (k == "center") {
        need(e, 4);
        const auto features = find_features(sp.lambda, sp.power_db(sp.port_index(e.args[0])), is_dips(e.args[1]), n.feature_db);
        const double want = to_number(e.args[2]), tol = to_number(e.args[3]);
        const double got = nearest_feature(features, want).lambda;
        r.pass = std::fabs(got - want) * 1e3 <= tol;
        r.detail = fmt("%.6f um, expected %.6f, off by %.4f nm", got, want, (got - want) * 1e3);
    } else if (k == "level") {
        need(e, 4);
        const double at = to_number(e.args[1]), want = to_number(e.args[2]), tol = to_number(e.args[3]);
        const double got = power_to_db(interpolate(sp.lambda, sp.power(sp.port_index(e.args[0])), at));
        r.pass = std::fabs(got - want) <= tol;
        r.detail = fmt("%.4f dB, expected %.4f, off by %.2e", got, want, got - want);
    } else if (k == "below" || k == "above") {
        need(e, 2);
        const Vector db = sp.power_db(sp.port_index(e.args[0]));
        const double bound = to_number(e.args[1]);
        const double extreme = k == "below" ? *std::max_element(db.begin(), db.end()) : *std::min_element(db.begin(), db.end());
        r.pass = k == "below" ? extreme < bound : extreme > bound;
        r.detail = fmt(k == "below" ? "maximum %.4f dB, bound %.4f" : "minimum %.4f dB, bound %.4f", extreme, bound);
    } else if (k == "min" || k == "max") {
        need(e, 3);
        const Vector db = sp.power_db(sp.port_index(e.args[0]));
        const double want = to_number(e.args[1]), tol = to_number(e.args[2]);
        const double got = k == "min" ? *std::min_element(db.begin(), db.end()) : *std::max_element(db.begin(), db.end());
        r.pass = std::fabs(got - want) <= tol;
        r.detail = fmt("%.4f dB, expected %.4f, off by %.2e", got, want, got - want);
    } else if (k == "deeper") {
        need(e, 2);
        const Vector db = sp.power_db(sp.port_index(e.args[0]));
        const double bound = to_number(e.args[1]), got = *std::min_element(db.begin(), db.end());
        r.pass = got < bound;
        r.detail = fmt("minimum %.3f dB, required below %.3f", got, bound);
    } else if (k == "extinction") {
        need(e, 3);
        const Vector db = sp.power_db(sp.port_index(e.args[0]));
        const double want = to_number(e.args[1]), tol = to_number(e.args[2]);
        const double got = *std::max_element(db.begin(), db.end()) - *std::min_element(db.begin(), db.end());
        r.pass = std::fabs(got - want) <= tol;
        r.detail = fmt("%.3f dB, expected %.3f", got, want);
    } else if (k == "uniform") {
        need(e, 1);
        double lo = 1e300, hi = -1e300;
        for (std::size_t p = 0; p < sp.ports.size(); ++p) {
            if (p == sp.excited) continue;
            const double v = power_to_db(interpolate(sp.lambda, sp.power(p), centre));
            lo = std::min(lo, v);
            hi = std::max(hi, v);
        }
        r.pass = hi - lo <= to_number(e.args[0]);
        r.detail = fmt("outputs between %.4f and %.4f dB", lo, hi);
    } else if (k == "delay") {
        need(e, 4);
        const std::size_t p = sp.port_index(e.args[0]);
        const double at = to_number(e.args[1]), want = to_number(e.args[2]), tol = to_number(e.args[3]);
        const double got = interpolate(sp.lambda, group_delay_ps(sp.lambda, sp.phase(p)), at);
        r.pass = std::fabs(got / want - 1.0) <= tol;
        r.detail = fmt("%.5f ps, expected %.5f, relative error %.2e", got, want, got / want - 1.0);
    } else if (k == "phase_step") {
        need(e, 3);
        const double at = to_number(e.args[0]), want = to_number(e.args[1]), tol = to_number(e.args[2]);
        double worst = 0.0, previous = 0.0;
        bool first = true;
        int steps = 0;
        for (std::size_t p = 0; p < sp.ports.size(); ++p) {
            if (p == sp.excited) continue;
            // interpolate the complex amplitude, then take its phase, so that wrapping cannot matter
            Vector re(sp.lambda.size()), im(sp.lambda.size());
            for (std::size_t i = 0; i < re.size(); ++i) re[i] = sp.amplitude[p][i].real(), im[i] = sp.amplitude[p][i].imag();
            const double phase = std::atan2(interpolate(sp.lambda, im, at), interpolate(sp.lambda, re, at)) * 180.0 / PI;
            if (!first) {
                worst = std::max(worst, std::fabs(wrap_degrees(phase - previous - want)));
                ++steps;
            }
            previous = phase;
            first = false;
        }
        if (steps == 0) throw std::invalid_argument("phase_step needs at least two output ports");
        r.pass = worst <= tol;
        r.detail = fmt("largest deviation %.4f degrees from a step of %.3f over %.0f steps", worst, wrap_degrees(want), steps);
    } else {
        throw std::invalid_argument("unknown expectation '" + k + "'");
    }
    return r;
}

}  // namespace

std::vector<CheckResult> evaluate(const Netlist& n, const Spectrum& sp) {
    std::vector<CheckResult> out;
    for (const Expectation& e : n.expectations) {
        try {
            out.push_back(one(n, sp, e));
        } catch (const std::exception& ex) {
            CheckResult r;
            r.name = e.kind;
            for (const std::string& a : e.args) r.name += " " + a;
            r.detail = std::string("line ") + std::to_string(e.line) + ": " + ex.what();
            out.push_back(r);
        }
    }
    return out;
}

}  // namespace lc
