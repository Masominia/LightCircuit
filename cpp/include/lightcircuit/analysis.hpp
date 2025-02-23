// Reading resonances and delays off a spectrum.
#pragma once

#include <vector>

#include "lightcircuit/types.hpp"

namespace lc {

struct Feature {
    std::size_t index = 0;  // nearest sample
    double lambda = 0.0;    // refined position, micrometres
    double db = 0.0;        // refined level
};

// Local minima (dips) or maxima (peaks) of a spectrum in decibels whose prominence is at least `prominence` dB.
// Positions are refined with a parabola through the three samples around each extremum.
std::vector<Feature> find_features(const Vector& lambda, const Vector& db, bool dips, double prominence);

// Mean spacing between consecutive features, in nanometres; NaN with fewer than two.
double mean_spacing_nm(const std::vector<Feature>& features);

// The feature closest to a wavelength; throws std::invalid_argument if there is none.
const Feature& nearest_feature(const std::vector<Feature>& features, double lambda);

// Full width, in nanometres, at the level halfway (in linear power) between the extremum and the
// opposite extreme found between its neighbours. NaN if the half level is not crossed on both sides.
double full_width_nm(const Vector& lambda, const Vector& power, const std::vector<Feature>& features, const Feature& feature, bool dip);

// Value at a wavelength by linear interpolation.
double interpolate(const Vector& lambda, const Vector& values, double at);

// Group delay in picoseconds from an unwrapped phase (radians): tau = (lambda^2 / (2 pi c)) dphi/dlambda.
Vector group_delay_ps(const Vector& lambda, const Vector& phase);

}  // namespace lc
