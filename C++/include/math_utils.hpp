#pragma once

#include <tuple>
#include <gmpxx.h>

using namespace std;

mpz_class find_gcd(mpz_class a, mpz_class b);
mpz_class mod_inverse(mpz_class c, mpz_class m);
tuple<mpz_class, mpz_class, mpz_class> extended_gcd(mpz_class a, mpz_class b);
mpz_class generateRandomPrime(int bitLength, int testRounds = 8);

bool is_prime(mpz_class a);
