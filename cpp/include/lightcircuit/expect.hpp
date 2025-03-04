// Expectations written in a netlist, checked against the computed spectrum.
#pragma once

#include <string>
#include <vector>

#include "lightcircuit/netlist.hpp"
#include "lightcircuit/sweep.hpp"

namespace lc {

struct CheckResult {
    std::string name;
    bool pass = false;
    std::string detail;
};

// Kinds and their arguments:
//   lossless [tol]                               all power leaves through the external ports
//   passive                                      no input produces more than unit output power
//   reciprocal [tol]                             the external matrix is symmetric
//   fsr <port> <dips|peaks> <nm> <reltol>        mean spacing of resonances
//   fwhm <port> <dips|peaks> <nm> <reltol>       width of the resonance nearest the centre of the sweep
//   count <port> <dips|peaks> <n>                number of resonances in the sweep
//   center <port> <dips|peaks> <um> <tol nm>     position of the resonance nearest a wavelength
//   level <port> <um> <dB> <tol dB>              transmission at a wavelength
//   below <port> <dB> / above <port> <dB>        bound on the whole sweep
//   min <port> <dB> <tol dB> / max ...           lowest or highest transmission over the sweep
//   deeper <port> <dB>                           the lowest transmission is below a bound
//   extinction <port> <dB> <tol dB>              maximum minus minimum over the sweep
//   uniform <tol dB>                             all ports except the driven one agree at the centre wavelength
//   delay <port> <um> <ps> <reltol>              group delay at a wavelength
//   phase_step <um> <degrees> <tol degrees>      phase difference between consecutive ports, driven port excluded
// A malformed expectation is reported as a failed check, not as an exception.
std::vector<CheckResult> evaluate(const Netlist& netlist, const Spectrum& spectrum);

}  // namespace lc
