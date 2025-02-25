#include "check.hpp"
#include "lightcircuit/analysis.hpp"

using namespace lc;

void test_analysis(Suite& suite) {
    // Lorentzian dips every 2 nm, 0.1 nm wide, on a flat background
    const std::size_t n = 20001;
    Vector lambda(n), power(n), db(n);
    for (std::size_t i = 0; i < n; ++i) {
        lambda[i] = 1.54 + 0.02 * static_cast<double>(i) / static_cast<double>(n - 1);
        double t = 1.0;
        for (int k = 0; k < 10; ++k) {
            const double x = (lambda[i] - (1.5411 + 0.002 * k)) / 0.00005;  // half width 0.05 nm
            t -= 0.9 / (1.0 + x * x);
        }
        power[i] = t;
        db[i] = 10.0 * std::log10(t);
    }
    const auto dips = find_features(lambda, db, true, 3.0);
    CHECK(dips.size() == 10);
    CHECK_NEAR(mean_spacing_nm(dips), 2.0, 1e-4);
    CHECK_NEAR(dips[3].lambda, 1.5471, 2e-7);
    CHECK_NEAR(dips[3].db, -10.0, 0.15);
    CHECK(find_features(lambda, db, false, 3.0).size() == 9);  // the humps between the dips
    CHECK(find_features(lambda, db, true, 15.0).empty());      // none is that deep
    const Feature& mid = nearest_feature(dips, 1.55);
    CHECK_NEAR(mid.lambda, 1.5491, 1e-6);
    CHECK_NEAR(full_width_nm(lambda, power, dips, mid, true), 0.1, 2e-3);
    CHECK_THROWS(nearest_feature({}, 1.55));
    CHECK(std::isnan(mean_spacing_nm({dips[0]})));

    // a single peak
    Vector peak(n), peak_db(n);
    for (std::size_t i = 0; i < n; ++i) {
        const double x = (lambda[i] - 1.55) / 0.0002;
        peak[i] = 0.01 + 0.8 / (1.0 + x * x);
        peak_db[i] = 10.0 * std::log10(peak[i]);
    }
    const auto peaks = find_features(lambda, peak_db, false, 3.0);
    CHECK(peaks.size() == 1);
    CHECK_NEAR(full_width_nm(lambda, peak, peaks, peaks[0], false), 0.4, 0.01);

    CHECK_NEAR(interpolate({1.0, 2.0, 4.0}, {10.0, 20.0, 0.0}, 3.0), 10.0, 1e-14);
    CHECK(interpolate({1.0, 2.0}, {10.0, 20.0}, 0.0) == 10.0 && interpolate({1.0, 2.0}, {10.0, 20.0}, 9.0) == 20.0);

    // delay of a plain waveguide: phase = 2 pi n(lambda) L / lambda gives tau = ng L / c
    const double length = 1000.0, neff = 2.4, ng = 4.2;
    Vector phase(n);
    for (std::size_t i = 0; i < n; ++i) phase[i] = 2.0 * PI * (neff + (lambda[i] - 1.55) * (neff - ng) / 1.55) / lambda[i] * length;
    const Vector tau = group_delay_ps(lambda, phase);
    CHECK_NEAR(tau[n / 2], ng * length / LIGHT_SPEED_UM_PER_PS, 1e-6);
}
