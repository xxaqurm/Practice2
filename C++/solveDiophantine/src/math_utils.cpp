#include "math_utils.h"
#include <stdexcept>
#include <iostream>
#include <vector>
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
    cout << "[";
    for (size_t i = 0; i < cf.size(); i++) {
        cout << cf[i];
        if (i == 0 && cf.size() > 0) cout << "; ";
        else if (i < cf.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}