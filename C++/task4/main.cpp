#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

typedef long long ll;

const ll PRIME = 104729; // Простое число > 255

ll modulo(ll a, ll m) {
    ll ret = a % m;
    return ret < 0 ? ret + m : ret;
}

ll modPow(ll base, ll exp, ll mod) {
    ll result = 1;
    base = modulo(base, mod);
    while (exp > 0) {
        if (exp & 1) result = modulo(result * base, mod);
        base = modulo(base * base, mod);
        exp >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll p) {
    return modPow(a, p - 2, p);
}

vector<ll> generatePolynomial(int degree, ll secret) {
    vector<ll> poly(degree + 1);
    poly[0] = secret;
    for (int i = 1; i <= degree; i++) {
        poly[i] = rand() % PRIME;
    }
    return poly;
}

ll evaluatePolynomial(const vector<ll> &poly, ll x) {
    ll result = 0;
    ll power = 1;
    for (ll coeff : poly) {
        result = modulo(result + coeff * power, PRIME);
        power = modulo(power * x, PRIME);
    }
    return result;
}

ll lagrangeInterpolation(const vector<pair<ll,ll>> &points) {
    ll secret = 0;
    int k = points.size();

    for (int i = 0; i < k; i++) {
        ll xi = points[i].first;
        ll yi = points[i].second;

        ll numerator = 1;
        ll denominator = 1;

        for (int j = 0; j < k; j++) {
            if (i == j) continue;
            ll xj = points[j].first;
            numerator = modulo(numerator * (-xj), PRIME);
            denominator = modulo(denominator * (xi - xj), PRIME);
        }

        ll inv_denominator = modInverse(denominator, PRIME);
        ll term = modulo(yi * numerator, PRIME);
        term = modulo(term * inv_denominator, PRIME);

        secret = modulo(secret + term, PRIME);
    }
    return secret;
}

int main() {
    srand(time(nullptr));

    string text;
    int n, k;

    cout << "Введите UTF-8 текст для шифрования: ";
    getline(cin, text);

    cout << "Введите общее количество долей (n): ";
    cin >> n;
    cout << "Введите количество долей для восстановления секрета (k): ";
    cin >> k;

    if (k > n) {
        cout << "Ошибка: k не может быть больше n" << endl;
        return 1;
    }

    // Преобразуем строку в вектор байт
    vector<unsigned char> bytes(text.begin(), text.end());

    // Для каждого байта создаём n долей
    vector<vector<pair<ll,ll>>> shares(bytes.size(), vector<pair<ll,ll>>(n));

    for (size_t i = 0; i < bytes.size(); i++) {
        ll secret = bytes[i];
        vector<ll> poly = generatePolynomial(k - 1, secret);
        for (ll j = 1; j <= n; j++) {
            shares[i][j - 1] = {j, evaluatePolynomial(poly, j)};
        }
    }

    cout << "\nДоли (для каждого байта):\n";
    for (int j = 0; j < n; j++) {
        cout << "Доля #" << j + 1 << ": ";
        for (size_t i = 0; i < bytes.size(); i++) {
            cout << shares[i][j].second << " ";
        }
        cout << endl;
    }

    cout << "\nДля восстановления введите " << k << " номеров долей (от 1 до " << n << "):\n";
    vector<int> chosenShares(k);
    for (int i = 0; i < k; i++) {
        cin >> chosenShares[i];
        if (chosenShares[i] < 1 || chosenShares[i] > n) {
            cout << "Неверный номер доли!" << endl;
            return 1;
        }
    }

    // Восстанавливаем байты
    vector<unsigned char> recoveredBytes(bytes.size());

    for (size_t i = 0; i < bytes.size(); i++) {
        vector<pair<ll,ll>> pointsForByte;
        for (int idx : chosenShares) {
            pointsForByte.push_back(shares[i][idx - 1]);
        }
        ll recoveredByte = lagrangeInterpolation(pointsForByte);
        recoveredBytes[i] = static_cast<unsigned char>(recoveredByte);
    }

    // Преобразуем байты обратно в строку UTF-8
    string recoveredText(recoveredBytes.begin(), recoveredBytes.end());

    cout << "\nВосстановленный текст: " << recoveredText << endl;

    return 0;
}
