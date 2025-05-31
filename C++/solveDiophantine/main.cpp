#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

tuple<int, int, int> extendedGCD(int a, int b) {
    /* Находит НОД числа, а также x, y для уравнения ax + by = НОД(a, b) */
    if (b == 0)
        return {a, 1, 0};
    int gcd, x1, y1;
    tie(gcd, x1, y1) = extendedGCD(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1};
}

bool solveDiophantine(int a, int b, int d, int &x, int &y) {
    /* Решает уравнение a*c + b*y = d */
    int gcd, x0, y0;
    tie(gcd, x0, y0) = extendedGCD(abs(a), abs(b));
    if (d % gcd != 0)
        return false; // решения нет

    x = x0 * (d / gcd);
    y = y0 * (d / gcd);

    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

vector<int> continuedFraction(int a, int b) {
    /* Ищет цепную дробь для рационального числа a / b */
    vector<int> result;
    while (b != 0) {
        result.push_back(a / b);
        int quotient = a % b;
        a = b;
        b = quotient;
    }
    return result;
}

void printContinuedFraction(vector<int> &cf) {
    /* Вывод цепной дроби */
    cout << "[";
    for (size_t i = 0; i < cf.size(); ++i) {
        cout << cf[i];
        if (i == 0 && cf.size() > 1) cout << "; ";
        else if (i < cf.size() - 1) cout << ", ";
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
