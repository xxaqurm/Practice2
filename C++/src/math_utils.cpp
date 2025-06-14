#include <tuple>
#include <cmath>
#include <gmpxx.h>
#include "math_utils.hpp"

using namespace std;

bool is_prime(mpz_class a) {
    /* Проверяет число на простоту */
    mpz_class numSqrt;
    mpz_sqrt(numSqrt.get_mpz_t(), a.get_mpz_t());
    for (mpz_class i = 2; i <= numSqrt; i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

mpz_class find_gcd(mpz_class a, mpz_class b) {
    /* Находит НОД(a, b) */
    while (b != 0) {
        mpz_class prevB = b;
        b = a % b;
        a = prevB;
    }
    return a;
}

tuple<mpz_class, mpz_class, mpz_class> extended_gcd(mpz_class a, mpz_class b) {
    /* находит d в выражении (c * d) mod m = 1 */
    if (b == 0) {
        return {a, 1, 0};
    }

    mpz_class gcd, u1, v1;
    tie(gcd, u1, v1) = extended_gcd(b, a % b);

    mpz_class u = v1;
    mpz_class v = u1 - (a / b) * v1;

    return {gcd, u, v};
}

mpz_class mod_inverse(mpz_class c, mpz_class m) {
    /* Находит обратный элемент к "c" по модолю "m" */
    mpz_class gcd, u, v;
    tie(gcd, u, v) = extended_gcd(c, m);

    if (u < 0) {
        u += m;
    }
    return u;
}
