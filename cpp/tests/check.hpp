// A very small test harness: CHECK records a failure and carries on, each test file registers one function.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

struct Suite {
    int checks = 0;
    int failures = 0;
    void record(bool ok, const char* expr, const char* file, int line) {
        ++checks;
        if (!ok) {
            ++failures;
            std::printf("FAILED %s:%d  %s\n", file, line, expr);
        }
    }
};

#define CHECK(cond) suite.record((cond), #cond, __FILE__, __LINE__)
#define CHECK_NEAR(x, y, tol) suite.record(std::fabs((x) - (y)) <= (tol), #x " ~ " #y, __FILE__, __LINE__)
#define CHECK_THROWS(expr)                                 \
    do {                                                   \
        bool threw_ = false;                               \
        try {                                              \
            (void)(expr);                                  \
        } catch (const std::exception&) {                  \
            threw_ = true;                                 \
        }                                                  \
        suite.record(threw_, #expr " throws", __FILE__, __LINE__); \
    } while (0)

void test_cmatrix(Suite& suite);
void test_lu(Suite& suite);
void test_medium(Suite& suite);
void test_strutil(Suite& suite);
void test_waveguide(Suite& suite);
void test_coupler(Suite& suite);
void test_splitter(Suite& suite);
void test_reflector(Suite& suite);
void test_bragg(Suite& suite);
void test_netlist(Suite& suite);
void test_circuit(Suite& suite);
void test_sweep(Suite& suite);
void test_analysis(Suite& suite);
void test_expect(Suite& suite);
