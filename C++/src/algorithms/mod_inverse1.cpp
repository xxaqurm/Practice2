#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include <gmpxx.h>

#include "math_utils.hpp"
#include "algorithms.hpp"

using namespace std;

void mod_inverse1() {
    mpz_class c = 0, m = 0;
    cout << "Введите свои c и m: ";
    
    cin.exceptions(ios::failbit);

    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw runtime_error("m must be greater than 0");
            } else if (find_gcd(c, m) != 1) {
                throw runtime_error("c and m must be simple to each other (NODE(c, m) = 1)");
            }
            break;
        } catch (const ios_base::failure& e) {
            cout << "Ошибка (" << e.what() << "). Введите 2 целых числа: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка (" << e.what() << "). Попробуйте еще раз: ";
        }
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    mpz_class d = 0;
    d = mod_inverse(c, m);

    cout << "d = " << d << endl << endl; 
}
