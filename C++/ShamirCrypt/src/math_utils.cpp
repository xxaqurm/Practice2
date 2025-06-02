#include "math_utils.h"
#include "shamir.h"
#include <cstdint>

using namespace std;

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t mod) {
    /* Возведение в степень по модулю*/
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        exp >>= 1;
    }
    return result;
}

uint64_t modinv(uint64_t a, uint64_t mod) {
    /* Находит обратный элемент по модулю */
    return modpow(a, mod - 2, mod);
}

uint64_t evaluate_polynomial(uint64_t x, uint64_t p, const vector<uint64_t>& coeffs) {
    /* Вычисление многочлена f(x) по коэффициентам */
    uint64_t result = 0;
    uint64_t power = 1;
    for (auto c : coeffs) {
        result = (result + (__uint128_t)c * power % p) % p;
        power = (__uint128_t)power * x % p;
    }
    return result;
}
