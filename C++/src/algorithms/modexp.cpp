/* 1 задание */
#include <iostream>
#include <limits>
#include <cmath>
#include <gmpxx.h>

#include "math_utils.hpp"

using namespace std;

mpz_class fermat_mod(mpz_class a, mpz_class x, mpz_class p) {
    /* Вычисляет a^x mod p, используя теорему Ферма */
    mpz_class result = 1;
    mpz_class base = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * base) % p;
        }
        base = (base * base) % p;
        x >>= 1;
    }
    return result;
}

void modexp() {
    mpz_class a = 0;
    mpz_class x = 0;
    mpz_class p = 0;
    
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
            cout << "Ошибка (" << e.what() << "). Введите 2 целых числа: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cout << L"Ошибка. " << e.what();
        }
    }

    mpz_class mod_result = fermat_mod(a, x, p);
    cout << "a^x mod p = " << mod_result << endl << endl;
}