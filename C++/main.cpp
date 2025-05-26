#include <iostream>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    /* Находит НОД чисел a и b */
    int bestGcd = 0;
    int smollerElm = a < b ? a : b;
    for (int i = 1; i <= (int)sqrt(smollerElm); i++) {
        if (a % i == 0 && b % i == 0) {
            bestGcd = i > bestGcd ? i : bestGcd;
        }
        if (a % (a / i) == 0 && b % (a / i) == 0 && (a / i) * i == a) {
            bestGcd = (a / i) > bestGcd ? (a / i) : bestGcd;
        }
        if (a % (b / i) == 0 && b % (b / i) == 0 && (b / i) * i == b) {
            bestGcd = (b / i) > bestGcd ? (b / i) : bestGcd;
        }
    }
    return bestGcd;
}

int main() {
    int a, b;
    cout << "Enter a, b: ";
    cin >> a >> b;

    int result = gcd(a, b);
    if (result == 0) {
        cout << "Undefinded" << endl;
    } else {
        cout << "Result: " << result << endl;
    }
}