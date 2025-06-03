/* 1 задание */
#include <iostream>
#include <stdexcept>
#include <limits>
#include "math_utils.h"
#include "prime_utils.h"

using namespace std;

int main() {
    int a = 0, x = 0, p = 0;
    cout << "Введите свои a, x, p (пример ввода: a x p): ";

    cin.exceptions(ios::failbit);
    
    while (true) {
        try {
            cin >> a >> x >> p;
            if (!is_prime(p)) {
                throw runtime_error("p должно быть простым. Попробуйте еще раз: ");
            }
            break;
        } catch (const ios_base::failure& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка (" << e.what() << "). Введите 2 целых числа: ";
        } catch (const exception& e) {
            cout << "Ошибка. " << e.what();
        }
    }

    int mod_result = fermat_mod(a, x, p);
    cout << "a^x mod p = " << mod_result << endl;
}