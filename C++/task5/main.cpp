#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

// Расширенный алгоритм Евклида
// Возвращает: (gcd, x, y) такое, что a*x + b*y = gcd
tuple<int, int, int> extendedGCD(int a, int b) {
    if (b == 0)
        return {a, 1, 0};
    int gcd, x1, y1;
    tie(gcd, x1, y1) = extendedGCD(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1};
}

// Решение уравнения: a*x + b*y = d
bool solveDiophantine(int a, int b, int d, int &x0, int &y0) {
    int g, x, y;
    tie(g, x, y) = extendedGCD(abs(a), abs(b));
    if (d % g != 0)
        return false; // решения нет

    x0 = x * (d / g);
    y0 = y * (d / g);

    // учитываем знак
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// Цепная дробь для рационального числа a / b
vector<int> continuedFraction(int a, int b) {
    vector<int> result;
    while (b != 0) {
        result.push_back(a / b);
        int temp = a % b;
        a = b;
        b = temp;
    }
    return result;
}

// Печать цепной дроби
void printContinuedFraction(vector<int> &cf) {
    cout << "[";
    for (size_t i = 0; i < cf.size(); ++i) {
        cout << cf[i];
        if (i == 0 && cf.size() > 1) cout << ";";
        else if (i < cf.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    int a = 275, b = 145, d = 10;
    int x, y;

    if (solveDiophantine(a, b, d, x, y)) {
        cout << "Решение уравнения " << a << "*x + " << b << "*y = " << d << ":\n";
        cout << "x = " << x << ", y = " << y << endl;
    } else {
        cout << "Нет решений\n";
    }

    cout << "\nЦепная дробь для " << a << "/" << b << ":\n";
    auto cf = continuedFraction(a, b);
    printContinuedFraction(cf);

    return 0;
}
