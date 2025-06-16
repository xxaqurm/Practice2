#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include <gmpxx.h>

#include "math_utils.hpp"
#include "menu_utils.hpp"
#include "algorithms.hpp"

using namespace std;

void mod_inverse1() {
    mpz_class c = 0, m = 0;
    
    cin.exceptions(ios::failbit);

    string inputError = "Введите 2 целых числа.";
    string invalidArgument = "m должно быть больше 0. c и m должны быть взаимно простыми.";
    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw invalid_argument("invalid_m");
            } else if (find_gcd(c, m) != 1) {
                throw invalid_argument("invalid_gcd(c,m)");
            }
            break;
        } catch (const ios_base::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, invalidArgument);
        }
    }

    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    mpz_class d = 0;
    d = mod_inverse(c, m);

    cout << c << "*d mod " << m << " = 1" << endl;
    cout << "d = " << d << endl << endl;
}
