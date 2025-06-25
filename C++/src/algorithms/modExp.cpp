/* 1 задание */
#include <iostream>
#include <limits>
#include <cmath>
#include <gmpxx.h>

#include "mathUtils.hpp"
#include "menuUtils.hpp"
#include "algorithms.hpp"

using namespace std;

mpz_class modPow(mpz_class a, mpz_class x, mpz_class p) {
    /* Вычисляет a^x mod p, используя малую теорему Ферма */
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

void exponentiationModulo() {
    cin.exceptions(ios::failbit);

    mpz_class a = 0;
    mpz_class x = 0;
    mpz_class p = 0;
    
    string inputError = "Ошибка ввода. Пожалуйста, введите 3 целых чисела.";
    string invalidP = "Некорректное p. Пожалуйста, введите простое p.";
    while (true) {
        try {
            cin >> a >> x >> p;
            if (!millerTest(p)) {  // проверка числа на простоту вероятностным тестом миллера
                throw invalid_argument("ivalid_p");
            }
            break;
        } catch (const ios_base::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, invalidP);
        }
    }

    mpz_class mod_result = modPow(a, x, p);
    cout << a << "^" << x << " mod " << "p = " << mod_result << endl << endl;
}
