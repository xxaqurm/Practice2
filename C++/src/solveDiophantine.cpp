#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <tuple>
#include <cmath>

using namespace std;

tuple<int, int, int> extendedGcd(int a, int b) {  // <gcd, u, v>
    /* Находит НОД(a, b), а также u, v для уравнеения au + bv = НОД(a, b) */
    if (b == 0) {
        return {a, 1, 0};
    }

    int gcd, x1, y1;
    tie(gcd, x1, y1) = extendedGcd(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1}; 
}

void solveDiophantine(int a, int b, int d, int& x, int& y) {
    /* Находит x, y для уравнения вида ax + by = d */
    int gcd, x0, y0;
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

vector<int> continuedFraction(int a, int b) {
    /* Ищет цепную дробь для рационального числа a / b */
    vector<int> cf;
    while (b != 0) {
        cf.push_back(a / b);
        int quotient = a % b;
        a = b;
        b = quotient;
    }
    return cf;
}

void printContinuedFraction(vector<int> cf) {
    /* Выводит цепную дробь */
    wcout << L"[";
    for (size_t i = 0; i < cf.size(); i++) {
        wcout << cf[i];
        if (i == 0 && cf.size() > 0) wcout << L"; ";
        else if (i < cf.size() - 1) wcout << L", ";
    }
    wcout << L"]" << endl;
}

void solve_dioph() {
    int a = 275, b = 145, d = 10;
    int x = 0, y = 0;

    try {
        solveDiophantine(a, b, d, x, y);
        wcout << L"Решение уравнения: " << a << L"*x + " << b << L"*y = " << d << ":\n";
        wcout << L"x = " << x << L"\ny = " << y << endl;
    } catch(const exception& e) {
        wcout << L"Ошибка: " << e.what();
    }

    wcout << L"\nЦепная дробь для " << a << L" / " << b << L":" << endl;
    vector<int> contFraction = continuedFraction(a, b);
    printContinuedFraction(contFraction);
    wcout << endl;
}
