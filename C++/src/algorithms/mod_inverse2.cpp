#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>

#include "math_utils.hpp"
#include "algorithms.hpp"

using namespace std;

void mod_inverse2() {
    mpz_class c = 0, m = 0;
    cout << "Введите свои c и m: ";

    cin.exceptions(ios::failbit);

    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw runtime_error("m должно быть больше 0. Попробуйте еще раз: ");
            }
            break;
        } catch (const ios::failure& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка (" << e.what() << "). Введите 2 целых числа: ";
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what();
        }
    }

    mpz_class d = mod_inverse(c, m);
    cout << c << "^(-1) mod " << m << " = " << c * d % m << endl << endl;
}
