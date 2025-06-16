#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>

#include "math_utils.hpp"
#include "menu_utils.hpp"
#include "algorithms.hpp"

using namespace std;

void mod_inverse2() {
    /* c * d = 1 (mod m) */
    mpz_class c = 0, m = 0;

    string inputError = "Введите 2 целых числа";
    string invalidArgument = "m должно быть больше 0. Числа c и m должны быть взаимно простыми.";
    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw invalid_argument("invalid_argument");
            } else if (find_gcd(c, m) != 1) {
                throw invalid_argument("invalid_gcd(c, m)");
            }
            break;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, invalidArgument);
        }
    }

    mpz_class d = mod_inverse(c, m);
    cout << c << "^(-1) mod " << m << " = " << d << endl << endl;
}
