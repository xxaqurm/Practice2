#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <tuple>
#include <cmath>
#include <gmpxx.h>

#include "math_utils.hpp"
#include "algorithms.hpp"

using namespace std;

tuple<mpz_class, mpz_class, mpz_class> extendedGcd(mpz_class a, mpz_class b) {  // <gcd, u, v>
    /* Находит НОД(a, b), а также u, v для уравнеения au + bv = НОД(a, b) */
    if (b == 0) {
        return {a, 1, 0};
    }

    mpz_class gcd, x1, y1;
    tie(gcd, x1, y1) = extendedGcd(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1}; 
}

void solveDiophantine(mpz_class a, mpz_class b, mpz_class d, mpz_class& x, mpz_class& y) {
    /* Находит x, y для уравнения вида ax + by = d */
    mpz_class gcd, x0, y0;
    tie(gcd, x0, y0) = extendedGcd(abs(a), abs(b));
    
    if (d % gcd != 0) {
        throw runtime_error("Нет решения.");
        return;
    }

    x = x0 * (d / gcd);
    y = y0 * (d / gcd);

    if (a < 0) x = -x;
    if (b < 0) y = -y;
}

vector<mpz_class> continuedFraction(mpz_class a, mpz_class b) {
    /* Ищет цепную дробь для рационального числа a / b */
    vector<mpz_class> cf;
    while (b != 0) {
        cf.push_back(a / b);
        mpz_class quotient = a % b;
        a = b;
        b = quotient;
    }
    return cf;
}

void printContinuedFraction(vector<mpz_class> cf) {
    /* Выводит цепную дробь */
    cout << "[";
    for (size_t i = 0; i < cf.size(); i++) {
        cout << cf[i];
        if (i == 0 && cf.size() > 0) cout << "; ";
        else if (i < cf.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void solve_dioph() {
    mpz_class a = 275, b = 145, d = 10;
    mpz_class x = 0, y = 0;

    try {
        solveDiophantine(a, b, d, x, y);
        cout << "Решение уравнения: " << a << "*x + " << b << "*y = " << d << ":\n";
        cout << "x = " << x << "\ny = " << y << endl;
    } catch(const exception& e) {
        cout << "Ошибка: " << e.what();
    }

    cout << "\nЦепная дробь для " << a << " / " << b << ":" << endl;
    vector<mpz_class> contFraction = continuedFraction(a, b);
    printContinuedFraction(contFraction);
    cout << endl;
}
