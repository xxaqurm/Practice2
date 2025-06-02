#pragma once

#include <cstdint>
#include <vector>

using namespace std;

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t mod);
uint64_t modinv(uint64_t a, uint64_t mod);
uint64_t evaluate_polynomial(uint64_t x, uint64_t p, const vector<uint64_t>& coeffs);
