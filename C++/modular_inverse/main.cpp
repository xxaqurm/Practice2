#include <iostream>
#include <algorithm>
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

int reverse_gcd(int a, int m){
    tuple<int, int> x = {m, 0};
    tuple<int, int> y = {a, 1};

    int q = 0;
    tuple<int, int> t;
    while (get<0>(y) > 0){
        q = get<0>(x) / get<0>(y);
        t = {get<0>(x) % get<0>(y), get<1>(x) - q * get<1>(y)};
        x = y;
        y = t;
    }
    int u = get<1>(x);

    return (u % m + m) % m;
}

tuple<int, int, int> extend_gcd(int a, int b){
    tuple<int, int, int> x = {a, 1, 0};
    tuple<int , int ,int> y =  {b, 0, 1};

    int q = 0;
    tuple<int, int, int> t;
    while(get<0>(y) != 0){
        q = get<0>(x) / get<0>(y);
        t = {get<0>(x) % get<0>(y), get<1>(x) - q * get<1>(y), get<2>(x) - q * get<2>(y)};
        x = y;
        y = t;
    }

    return x;
}

int findD(int c, int m){
    if (gcd(c, m) != 1){
        cout << "Wrong numbers" << endl;
        return 0;
    }

    tuple<int, int, int> evk = extend_gcd(c, m);

    int u = get<1>(evk);
    return ((u % m) + m) % m;
}

int main() {
    int c = 0;
    int m = 0;

    cout << "Enter your c, m (expl: c m): ";
    cin >> c >> m;

    int d = findD(c, m);
    cout << "Result: " << d;
}