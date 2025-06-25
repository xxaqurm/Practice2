#pragma once

#include <tuple>
#include <gmpxx.h>

using namespace std;

tuple<mpz_class, mpz_class, mpz_class> extendedEuclid(mpz_class a, mpz_class b);
mpz_class generateRandomPrime(int bitLength);
mpz_class findGcd(mpz_class a, mpz_class b);

bool millerTest(mpz_class n, int t = 8);
