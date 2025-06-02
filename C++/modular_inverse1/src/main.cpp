/* 2 задание */
#include <iostream>
#include <stdexcept>
#include <limits>
#include <tuple>
#include "math_utils.h"

using namespace std;

int main() {
    int c = 0, m = 0;
    cout << "Введите свои c и m: ";
    
    cin.exceptions(ios::failbit);

    while (true) {
        try {
            cin >> c >> m;
            if (m < 1) {
                throw runtime_error("m должно быть больше 0. Попробуйтее еще раз: ");
            } else if (find_gcd(c, m) != 1) {
                throw runtime_error("c и m должны быть взаимо простыми (НОД(c, m) = 1). Попробуйте еще раз: ");
            }
            break;
        } catch (const ios_base::failure& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // отображаем неверный ввод
            cout << "Ошибка (" << e.what() << "). Введите 2 целых числа: ";
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what();
        }
    }

    int d = 0;
    d = mod_inverse(c, m);

    cout << "d = " << d << endl; 
}