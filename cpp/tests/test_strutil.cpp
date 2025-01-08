#include "check.hpp"
#include "lightcircuit/strutil.hpp"

using namespace lc;

void test_strutil(Suite& suite) {
    CHECK(split_words("  comp  w1 waveguide\tlength=3 ") == (std::vector<std::string>{"comp", "w1", "waveguide", "length=3"}));
    CHECK(strip_comment("  link a.1 b.2   # the bus") == "link a.1 b.2");
    CHECK(strip_comment("# only a comment").empty() && strip_comment("   ").empty());
    const Params p = parse_params({"comp", "x", "kappa=0.25", "excess_db=1e-1"}, 2);
    CHECK(p.size() == 2 && p.at("kappa") == 0.25 && p.at("excess_db") == 0.1);
    CHECK(get(p, "kappa", 9.0) == 0.25 && get(p, "missing", 9.0) == 9.0);
    CHECK(require(p, "kappa", "coupler") == 0.25);
    CHECK_THROWS(require(p, "length", "waveguide"));
    CHECK_THROWS(parse_params({"kappa"}, 0));
    CHECK_THROWS(parse_params({"=3"}, 0));
    CHECK_THROWS(parse_params({"kappa=abc"}, 0));
    CHECK_THROWS(to_number("1.5x"));
    CHECK(to_number("-2.5e3") == -2500.0);
}
