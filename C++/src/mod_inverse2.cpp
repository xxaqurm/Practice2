#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include "math_utils.h"

using namespace std;

void mod_inverse2() {
    int c = 0, m = 0;
    wcout << L"Введите свои c и m: ";

    wcin.exceptions(ios::failbit);

    while (true) {
        try {
            wcin >> c >> m;
            if (m < 1) {
                throw runtime_error("m должно быть больше 0. Попробуйте еще раз: ");
            }
            break;
        } catch (const ios::failure& e) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
            wcout << L"Ошибка (" << e.what() << L"). Введите 2 целых числа: ";
        } catch (const exception& e) {
            wcout << L"Ошибка: " << e.what();
        }
    }

    int d = mod_inverse(c, m);
    wcout << c << L"^(-1) mod " << m << L" = " << c * d % m << endl << endl;
}
