#include "check.hpp"
#include "lightcircuit/expect.hpp"

using namespace lc;

static std::vector<CheckResult> checks(const std::string& expectations) {
    const std::string text = "medium lambda0=1.55 neff=2.4 ng=4.2 loss_db_cm=2\nsweep 1.53 1.57 8001\n"
                             "comp c1 coupler kappa=0.1\ncomp c2 coupler kappa=0.1\ncomp w1 waveguide length=31.4159265359\ncomp w2 waveguide length=31.4159265359\n"
                             "link c1.4 w1.1\nlink w1.2 c2.4\nlink c2.2 w2.1\nlink w2.2 c1.2\nport in c1.1\nport through c1.3\nport drop c2.1\n" +
                             expectations;
    const Netlist n = parse_netlist(text);
    return evaluate(n, sweep(Circuit(n), n));
}

void test_expect(Suite& suite) {
    // free spectral range lambda^2 / (ng L) = 9.104 nm
    const auto good = checks("expect passive\nexpect reciprocal\nexpect fsr drop peaks 9.104 0.005\nexpect fsr through dips 9.104 0.005\n"
                             "expect count drop peaks 4\nexpect below drop 0\nexpect above through -40\nexpect deeper through -5\nexpect max through 0 0.5\n");
    CHECK(good.size() == 9);
    for (const CheckResult& c : good) CHECK(c.pass);
    CHECK(good[2].name == "fsr drop peaks 9.104 0.005" && good[2].detail.find("nm") != std::string::npos);

    // the same circuit fails expectations that are wrong
    const auto bad = checks("expect lossless\nexpect fsr drop peaks 8.0 0.005\nexpect count drop peaks 7\nexpect below through -1\nexpect level drop 1.55 0 0.1\n");
    for (const CheckResult& c : bad) CHECK(!c.pass);

    // malformed expectations fail with a message instead of stopping the run
    const auto broken = checks("expect fsr drop valleys 9 0.1\nexpect fsr nowhere dips 9 0.1\nexpect level drop 1.55\nexpect brightness drop 3\nexpect passive\n");
    CHECK(broken.size() == 5);
    CHECK(!broken[0].pass && broken[0].detail.find("dips or peaks") != std::string::npos);
    CHECK(!broken[1].pass && broken[1].detail.find("unknown port") != std::string::npos);
    CHECK(!broken[2].pass && broken[2].detail.find("4 arguments") != std::string::npos);
    CHECK(!broken[3].pass && broken[3].detail.find("unknown expectation") != std::string::npos);
    CHECK(broken[4].pass);
}
