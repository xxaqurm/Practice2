#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include "math_utils.h"
#include "shamir.h"

using namespace std;

vector<pair<uint64_t, uint64_t>> generate_shares(uint64_t secret, uint64_t p, int k, int n) {
    /* Генерация n частей секрета */
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(0, p - 1);

    vector<uint64_t> coeffs;
    coeffs.push_back(secret);
    for (int i = 1; i < k; i++)
        coeffs.push_back(dist(gen));

    vector<pair<uint64_t, uint64_t>> shares;
    for (int i = 1; i <= n; i++) {
        uint64_t x = i;
        uint64_t y = evaluate_polynomial(x, p, coeffs);
        shares.push_back({x, y});
    }
    return shares;
}

uint64_t reconstruct_secret(const vector<pair<uint64_t, uint64_t>>& shares, uint64_t p, uint64_t k) {
    /* Восстановление секрета по k частям */
    uint64_t secret = 0;
    for (size_t i = 0; i < k; i++) {
        uint64_t xi = shares[i].first;
        uint64_t yi = shares[i].second;

        uint64_t num = 1, denom = 1;
        for (size_t j = 0; j < k; j++) {
            if (i != j) {
                uint64_t xj = shares[j].first;
                num = (__uint128_t)num * (p - xj) % p;
                denom = (__uint128_t)denom * (xi + p - xj) % p;
            }
        }
        uint64_t lagrange = (__uint128_t)num * modinv(denom, p) % p;
        secret = (secret + (__uint128_t)yi * lagrange % p) % p;
    }
    return secret;
}
