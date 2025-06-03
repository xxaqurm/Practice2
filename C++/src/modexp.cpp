/* 1 задание */
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

int fermat_mod(int a, int x, int p) {
    /* Вычисляет a^x mod p, используя теорему Ферма */
    int result = 1;
    int base = a % p;
    while (x > 0) {
        if (x & 1) {
            result = (result * base) % p;
        }
        base = (base * base) % p;
        x >>= 1;
    }
    return result;
}

bool is_prime(int a) {
    /* Проверяет число на простоту */
    for (int i = 2; i <= (int)sqrt(a); i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}


void modexp() {
    int a = 0, x = 0, p = 0;
    wcout << L"Введите свои a, x, p (пример ввода: a x p): ";

    wcin.exceptions(ios::failbit);
    
    while (true) {
        try {
            wcin >> a >> x >> p;
            if (!is_prime(p)) {
                throw runtime_error("p должно быть простым. Попробуйте еще раз: ");
            }
            break;
        } catch (const ios_base::failure& e) {
            cout << L"Ошибка (" << e.what() << L"). Введите 2 целых числа: ";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            wcout << L"Ошибка. " << e.what();
        }
    }

    int mod_result = fermat_mod(a, x, p);
    wcout << L"a^x mod p = " << mod_result << endl << endl;
}