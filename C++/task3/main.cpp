#include <iostream>

// Расширенный алгоритм Евклида
// Возвращает НОД и заполняет x и y такими, что: a*x + b*y = gcd(a, b)
int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Функция для нахождения обратного элемента по модулю
// Возвращает d = c^(-1) mod m, если обратный существует
int mod_inverse(int c, int m) {
    int x, y;
    int gcd = extended_gcd(c, m, x, y);
    if (gcd != 1) {
        std::cerr << "Обратного элемента не существует (не взаимно простые числа).\n";
        return -1;
    }
    // Приводим результат к положительному остатку
    return (x % m + m) % m;
}

int main() {
    int c, m;
    std::cout << "Введите c и m (для вычисления c^(-1) mod m): ";
    std::cin >> c >> m;

    int inverse = mod_inverse(c, m);
    if (inverse != -1) {
        std::cout << "Обратное число: " << inverse << "\n";
        // Проверка:
        std::cout << c << " * " << inverse << " mod " << m << " = " << (c * inverse) % m << "\n";
    }

    return 0;
}