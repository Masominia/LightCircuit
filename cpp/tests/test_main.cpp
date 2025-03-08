#include <cstdio>

#include "check.hpp"

int main() {
    Suite suite;
    struct Entry {
        const char* name;
        void (*run)(Suite&);
    };
    const Entry entries[] = {{"cmatrix", test_cmatrix}, {"lu", test_lu}, {"medium", test_medium}, {"strutil", test_strutil}, {"waveguide", test_waveguide}, {"coupler", test_coupler}, {"splitter", test_splitter}, {"reflector", test_reflector}, {"bragg", test_bragg}, {"netlist", test_netlist}, {"circuit", test_circuit}, {"sweep", test_sweep}, {"analysis", test_analysis}, {"expect", test_expect}};
    for (const Entry& e : entries) {
        const int before = suite.failures, checks = suite.checks;
        e.run(suite);
        std::printf("%-12s %3d checks  %s\n", e.name, suite.checks - checks, suite.failures == before ? "ok" : "FAILED");
    }
    std::printf("%d checks, %d failures\n", suite.checks, suite.failures);
    return suite.failures == 0 ? 0 : 1;
}
