#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include "math_utils.h"

using namespace std;

int main() {
    int a = 275, b = 145, d = 10;
    int x = 0, y = 0;

    try {
        solveDiophantine(a, b, d, x, y);
        cout << "Решение уравнения: " << a << "*x + " << b << "*y = " << d << ":\n";
        cout << "x = " << x << "\ny = " << y << endl;
    } catch(const exception& e) {
        cout << "Ошибка: " << e.what();
    }

    cout << "\nЦепная дробь для " << a << " / " << b << ":" << endl;
    vector<int> contFraction = continuedFraction(a, b);
    printContinuedFraction(contFraction);
}
