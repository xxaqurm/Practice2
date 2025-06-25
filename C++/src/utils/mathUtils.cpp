#include <set>
#include <tuple>
#include <cmath>
#include <ctime>
#include <random>
#include <gmpxx.h>

#include "mathUtils.hpp"

using namespace std;

vector<mpz_class> eratosthenesSieve(int limit) {
    /* Строит решето Эратосфена */
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    vector<mpz_class> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

vector<pair<mpz_class, mpz_class>> factorize(mpz_class num) {
    /* Находит каноническое разложение числа */
    vector<pair<mpz_class, mpz_class>> result;
    vector<mpz_class> primes = eratosthenesSieve(500);
    
    for (auto& primeElm : primes) {
        mpz_class exponent = 0;
        while (num % primeElm == 0 && num > 0) {
            exponent++;
            num /= primeElm;
        }
        if (exponent) {
            result.push_back({primeElm, exponent});
        }
    }

    return result;
}

bool millerTest(mpz_class n, int t) {
    /* Вероятностный тест Миллера */
    static gmp_randclass rand_gen(gmp_randinit_default);
    static random_device rd;
    rand_gen.seed(rd());

    mpz_class lower = 2;
    mpz_class upper = n - 1;

    mpz_class range = upper - lower + 1;

    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n < 10) return false;

    set<mpz_class> nums;
    while ((int)nums.size() != t) {
        nums.insert(rand_gen.get_z_range(range) + lower);
    }

    for (auto& a : nums) {
        mpz_class base = a, exp = n - 1, mod = n, res = 0;
        mpz_powm(res.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
        if (res != 1) {
            return false;
        }
    }

    vector<pair<mpz_class, mpz_class>> primeFactors = factorize(n - 1);
    for (auto& factor : primeFactors) {
        mpz_class q = factor.first;
        bool onlyOne = true;
        for (auto& a : nums) {
            mpz_class base = a, exp = (n - 1) / q, mod = n, res = 0;
            mpz_powm(res.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
            if (res != 1) {
                onlyOne = false;
                break;
            }
        }
        if (onlyOne) {
            return false;
        }
    }
    return true;
}

mpz_class findGcd(mpz_class a, mpz_class b) {
    /* Ищет НОД(a, b) */
    if (b == 0) {
        return a;
    }

    return findGcd(b, a % b);
}

tuple<mpz_class, mpz_class, mpz_class> extendedEuclid(mpz_class a, mpz_class b) {
    /* Реализация расширенного алгоритма евклида */
    if (b == 0) {
        return {a, 1, 0};
    }

    mpz_class gcd = 0, u1 = 0, v1 = 0;
    tie(gcd, u1, v1) = extendedEuclid(b, a % b);

    mpz_class u = v1;
    mpz_class v = u1 - (a / b) * v1;

    return {gcd, u, v};
}

mpz_class modExp(mpz_class a, mpz_class x, mpz_class m) {
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

mpz_class generateRandomPrime(int bitLength) {
    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(time(nullptr));

    mpz_class candidate;
    while (true) {
        candidate = rng.get_z_bits(bitLength);
        mpz_setbit(candidate.get_mpz_t(), bitLength - 1);
        mpz_setbit(candidate.get_mpz_t(), 0);

        if (millerTest(candidate, 8)) {
            return candidate;
        }
    }
}

