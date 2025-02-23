#include "lightcircuit/analysis.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace lc {

std::vector<Feature> find_features(const Vector& lambda, const Vector& db, bool dips, double prominence) {
    const std::size_t n = db.size();
    std::vector<Feature> out;
    if (n < 3) return out;
    const double sign = dips ? -1.0 : 1.0;
    auto y = [&](std::size_t i) { return sign * db[i]; };
    for (std::size_t i = 1; i + 1 < n; ++i) {
        if (!(y(i) > y(i - 1) && y(i) >= y(i + 1))) continue;
        // prominence: height above the higher of the two lowest points reached before meeting a higher sample
        double left = y(i), right = y(i);
        for (std::size_t k = i; k-- > 0;) {
            if (y(k) > y(i)) break;
            left = std::min(left, y(k));
        }
        for (std::size_t k = i + 1; k < n; ++k) {
            if (y(k) > y(i)) break;
            right = std::min(right, y(k));
        }
        if (y(i) - std::max(left, right) < prominence) continue;
        Feature f;
        f.index = i;
        const double a = y(i - 1), b = y(i), c = y(i + 1), denom = a - 2.0 * b + c;
        const double shift = denom != 0.0 ? 0.5 * (a - c) / denom : 0.0;
        f.lambda = lambda[i] + shift * (lambda[i + 1] - lambda[i]);
        f.db = sign * (b - 0.25 * (a - c) * shift);
        out.push_back(f);
    }
    return out;
}

double mean_spacing_nm(const std::vector<Feature>& f) {
    if (f.size() < 2) return std::numeric_limits<double>::quiet_NaN();
    return 1e3 * (f.back().lambda - f.front().lambda) / static_cast<double>(f.size() - 1);
}

const Feature& nearest_feature(const std::vector<Feature>& features, double lambda) {
    if (features.empty()) throw std::invalid_argument("no resonance found");
    return *std::min_element(features.begin(), features.end(), [&](const Feature& a, const Feature& b) { return std::fabs(a.lambda - lambda) < std::fabs(b.lambda - lambda); });
}

double full_width_nm(const Vector& lambda, const Vector& power, const std::vector<Feature>& features, const Feature& feature, bool dip) {
    // search window: up to the neighbouring features, or the ends of the sweep
    std::size_t lo = 0, hi = power.size() - 1;
    for (const Feature& f : features) {
        if (f.index < feature.index) lo = std::max(lo, f.index);
        if (f.index > feature.index) hi = std::min(hi, f.index);
    }
    const double centre = power[feature.index];
    double opposite = centre;
    for (std::size_t i = lo; i <= hi; ++i) opposite = dip ? std::max(opposite, power[i]) : std::min(opposite, power[i]);
    const double level = 0.5 * (centre + opposite);
    auto crossing = [&](int direction) {
        std::size_t i = feature.index;
        while (true) {
            if ((direction < 0 && i == lo) || (direction > 0 && i == hi)) return std::numeric_limits<double>::quiet_NaN();
            const std::size_t next = direction < 0 ? i - 1 : i + 1;
            const bool crossed = dip ? power[next] >= level : power[next] <= level;
            if (crossed) {
                const double w = (level - power[i]) / (power[next] - power[i]);
                return lambda[i] + w * (lambda[next] - lambda[i]);
            }
            i = next;
        }
    };
    return 1e3 * (crossing(+1) - crossing(-1));
}

double interpolate(const Vector& lambda, const Vector& values, double at) {
    if (at <= lambda.front()) return values.front();
    if (at >= lambda.back()) return values.back();
    const auto it = std::upper_bound(lambda.begin(), lambda.end(), at);
    const std::size_t i = static_cast<std::size_t>(it - lambda.begin()) - 1;
    const double w = (at - lambda[i]) / (lambda[i + 1] - lambda[i]);
    return values[i] + w * (values[i + 1] - values[i]);
}

Vector group_delay_ps(const Vector& lambda, const Vector& phase) {
    const std::size_t n = lambda.size();
    Vector tau(n, 0.0);
    for (std::size_t i = 0; i < n; ++i) {
        const std::size_t a = i == 0 ? 0 : i - 1, b = i + 1 == n ? i : i + 1;
        const double slope = (phase[b] - phase[a]) / (lambda[b] - lambda[a]);
        // with the convention exp(+i beta L) the phase falls as the wavelength grows, hence the minus sign
        tau[i] = -lambda[i] * lambda[i] / (2.0 * PI * LIGHT_SPEED_UM_PER_PS) * slope;
    }
    return tau;
}

}  // namespace lc
