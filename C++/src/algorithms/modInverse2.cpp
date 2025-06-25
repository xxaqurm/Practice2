#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>

#include "mathUtils.hpp"
#include "menuUtils.hpp"
#include "algorithms.hpp"

using namespace std;

void modInverse2() {
    mpz_class c = 0, m = 0;

    string inputError = "Введите 2 целых числа";
    string invalidArgument = "m должно быть больше 0. Числа c и m должны быть взаимно простыми.";
    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw invalid_argument("invalid_argument");
            } else if (findGcd(c, m) != 1) {
                throw invalid_argument("invalid_gcd(c, m)");
            }
            break;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, invalidArgument);
        }
    }

    mpz_class d = 0, u = 0, v = 0, gcd = 1;
    tie(gcd, u, v) = extendedEuclid(c, m);

    d = (u % m + m) % m;

    cout << c << "^(-1) mod " << m << " = " << d << endl << endl;
}
