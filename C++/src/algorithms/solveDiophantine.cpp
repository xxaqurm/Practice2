#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <tuple>
#include <cmath>
#include <gmpxx.h>

#include "mathUtils.hpp"
#include "menuUtils.hpp"
#include "algorithms.hpp"

using namespace std;

void solveDiophantine(mpz_class a, mpz_class b, mpz_class c, mpz_class& x, mpz_class& y, vector<mpz_class>& chainFractions) {
    /* Находит x, y для уравнения вида ax + by = d */
    mpz_class gcd = findGcd(findGcd(a, b), c);
    mpz_class finalCoeff = c / gcd;

    a /= gcd;
    b /= gcd;
    c /= gcd;

    mpz_class numerator = a;
    mpz_class denominator = b;

    int termCount = 0;
    while (denominator != 1) {
        chainFractions.push_back(numerator / denominator);

        mpz_class remains = numerator % denominator;
        
        numerator = denominator;
        denominator = remains;
        termCount++;
    }

    mpz_class finalNumerator = 1;
    mpz_class finalDenominator = chainFractions[termCount - 1];
    for (int i = chainFractions.size() - 2; i >= 0; i--) {
        finalNumerator = chainFractions[i] * finalDenominator + finalNumerator;
        mpz_class temp = finalDenominator;
        finalDenominator = finalNumerator;
        finalNumerator = temp;
    }

    x = pow(-1, termCount - 1) * finalNumerator * finalCoeff;
    y = pow(-1, termCount) * finalDenominator * finalCoeff;
}

void solveDioph() {
    mpz_class a = 275, b = 145, d = 10;
    mpz_class x = 0, y = 0;

    vector<mpz_class> chainFractions;

    string inputError = "Невозможно решить при заданных значениях.";
    try {
        solveDiophantine(a, b, d, x, y, chainFractions);
        cout << "Найденный X: " << x << endl;
        cout << "Найденный Y: " << y << endl;

        cout << "Цепная дробь: [";
        for (size_t i = 0; i < chainFractions.size(); i++) {
            cout << chainFractions[i];
            if (i == 0) {
                cout << "; ";
            } else if (i != chainFractions.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        
        cout << "Решение уравнения: " << a << "*x + " << b << "*y = " << d << ":\n";
        cout << "x = " << x << "\ny = " << y << endl << endl;
    } catch(const exception& e) {
        userInputError(e, inputError);
    }
}
