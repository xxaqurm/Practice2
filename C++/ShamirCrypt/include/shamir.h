#pragma once

#include <vector>
#include <cstdint>

using namespace std;

vector<pair<uint64_t, uint64_t>> generate_shares(uint64_t secret, uint64_t p, int k, int n);
uint64_t reconstruct_secret(const vector<pair<uint64_t, uint64_t>>& shares, uint64_t p, uint64_t k);
