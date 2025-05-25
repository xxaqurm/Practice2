#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int a) {
    /* Проверяет число на простоту */
    for (int i = 2; i < (int)sqrt(a); i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

int fermat_mod(int a, int x, int p) {
    /* Вычисляет a^x mod p, используя теорему Ферма */
    int result = 1;
    int base = a % p;
    while (x > 0) {
        if (x & 1) {
            result = (result * base) % p;
        }
        base = (base * base) % p;
        x /= 2;
    }
    return result;
}

int main() {
    try {
        int a = 0;
        int x = 0;
        int p = 0;

        cout << "Введите свои a, x, p (пример ввода: a x p): ";
        while (true) {
            cin >> a >> x >> p;
            if (is_prime(p)) {
                break;
            }
            cout << "p должно быть простым. Попробуйте еще раз: ";
        }

        int mod_result = fermat_mod(a, x, p);
        cout << "a^x mod p = " << mod_result << endl;
    } catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}