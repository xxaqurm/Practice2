#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include "math_utils.h"

using namespace std;

void mod_inverse1() {
    int c = 0, m = 0;
    wcout << L"Введите свои c и m: ";
    
    wcin.exceptions(ios::failbit);

    while (true) {
        try {
            wcin >> c >> m;
            if (m < 1) {
                throw runtime_error("m must be greater than 0");
            } else if (find_gcd(c, m) != 1) {
                throw runtime_error("c and m must be simple to each other (NODE(c, m) = 1)");
            }
            break;
        } catch (const ios_base::failure& e) {
            wcout << L"Ошибка (" << e.what() << L"). Введите 2 целых числа: ";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
            wcout << L"Ошибка (" << e.what() << L"). Попробуйте еще раз: ";
        }
    }

    wcin.clear();
    wcin.ignore(numeric_limits<streamsize>::max(), '\n');

    int d = 0;
    d = mod_inverse(c, m);

    wcout << L"d = " << d << endl << endl; 
}
