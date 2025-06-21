#include <tuple>
#include <cmath>
#include <ctime>
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

mpz_class modexp(mpz_class a, mpz_class x, mpz_class m) {
    /* Модульное возведение в степень */
    mpz_class res = 1;
    mpz_class base = a % m;
    while (x > 0) {
        if (x % 2 == 1) {
            res = (res * base) % m;
        }
        base = (base * base) % m;
        x /= 2;
    }
    return res;
}

bool millerTest(const mpz_class& n, int t, gmp_randclass& rng) {
    if (n == 2 || n == 3) return true;
    if (n < 2 || n % 2 == 0) return false;

    mpz_class d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < t; i++) {
        mpz_class a = rng.get_z_range(n - 3) + 2; // [2, n-2]

        mpz_class x = modexp(a, d, n);

        if (x == 1 || x == n - 1) continue;

        bool continueLoop = false;
        for (int r = 1; r < s; r++) {
            x = (x  * x) % n;
            if (x == n - 1) {
                continueLoop = true;
                break;
            }
        }

        if (!continueLoop) return false;
    }

    return true;
}

mpz_class generateRandomPrime(int bitLength, int testRounds) {
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(time(nullptr));

    mpz_class candidate;
    while (true) {
        candidate = rng.get_z_bits(bitLength);
        mpz_setbit(candidate.get_mpz_t(), bitLength - 1); // Устанавливаем старший бит (обеспечивает нужную длину)
        mpz_setbit(candidate.get_mpz_t(), 0);             // Делаем нечётным

        if (millerTest(candidate, testRounds, rng)) {
            return candidate;
        }
    }
}

