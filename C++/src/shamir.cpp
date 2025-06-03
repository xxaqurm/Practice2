#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <limits>
#include <tuple>
#include <vector>
#include <random>

using namespace std;
const uint64_t PRIME = 208351617373;

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t mod) {
    /* Возведение в степень по модулю*/
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (__uint128_t)result * base % mod;
        base = (__uint128_t)base * base % mod;
        exp >>= 1;
    }
    return result;
}

uint64_t modinv(uint64_t a, uint64_t mod) {
    /* Находит обратный элемент по модулю */
    return modpow(a, mod - 2, mod);
}

uint64_t evaluate_polynomial(uint64_t x, uint64_t p, const vector<uint64_t>& coeffs) {
    /* Вычисление многочлена f(x) по коэффициентам */
    uint64_t result = 0;
    uint64_t power = 1;
    for (auto c : coeffs) {
        result = (result + (__uint128_t)c * power % p) % p;
        power = (__uint128_t)power * x % p;
    }
    return result;
}

vector<pair<uint64_t, uint64_t>> generate_shares(uint64_t secret, uint64_t p, int k, int n) {
    /* Генерация n частей секрета */
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(0, p - 1);

    vector<uint64_t> coeffs;
    coeffs.push_back(secret);
    for (int i = 1; i < k; i++)
        coeffs.push_back(dist(gen));

    vector<pair<uint64_t, uint64_t>> shares;
    for (int i = 1; i <= n; i++) {
        uint64_t x = i;
        uint64_t y = evaluate_polynomial(x, p, coeffs);
        shares.push_back({x, y});
    }
    return shares;
}

uint64_t reconstruct_secret(const vector<pair<uint64_t, uint64_t>>& shares, uint64_t p, uint64_t k) {
    /* Восстановление секрета по k частям */
    uint64_t secret = 0;
    for (size_t i = 0; i < k; i++) {
        uint64_t xi = shares[i].first;
        uint64_t yi = shares[i].second;

        uint64_t num = 1, denom = 1;
        for (size_t j = 0; j < k; j++) {
            if (i != j) {
                uint64_t xj = shares[j].first;
                num = (__uint128_t)num * (p - xj) % p;
                denom = (__uint128_t)denom * (xi + p - xj) % p;
            }
        }
        uint64_t lagrange = (__uint128_t)num * modinv(denom, p) % p;
        secret = (secret + (__uint128_t)yi * lagrange % p) % p;
    }
    return secret;
}

void shamir() {
    wcin.exceptions(ios::failbit);

    int k = 0;
    int n = 0;

    while (true) {
        try {
            if (n == 0) {
                wcout << L"Введите количество частей (n), на которое будет разбит ваш текст: ";
                wcin >> n;
                if (n < 1) {
                    n = 0;
                    throw runtime_error("n cannot be less than 1");
                }
            }
            wcout << L"Введите количество ключей (k), которых достаточно для расшифровки: ";
            wcin >> k;
            if (k < 1) {
                k = 0;
                throw runtime_error("k cannot be less than 1");
            } else if (k > n) {
                k = 0;
                throw runtime_error("k cannot be greater than n");
            }
            break;
        } catch (const ios_base::failure& e) {
            wcout << L">>> Ошибка(" << e.what() << L"). Следует ввести число. Попробуйте еще раз: " << endl; 
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            wcout << L">>> Ошибка(" << e.what() << L"): Попробуйте еще раз.\n";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    wcin.clear();
    wcin.ignore(numeric_limits<streamsize>::max(), '\n');

    wstring text;
    
    wcout << L"\nВведите строку, которую хотите зашифровать: ";
    getline(wcin, text);
 
    vector<vector<pair<uint64_t, uint64_t>>> encrypted;
    for (wchar_t wc : text) {
        uint64_t code = (uint64_t)wc;
        encrypted.push_back(generate_shares(code, PRIME, k, n));
    }
    text.clear();

    uint64_t numSymb = 1;
    wcout << L"\nНесколько частей:\n";
    for (auto& symb : encrypted) {
        wcout << numSymb++;
        for (auto& share : symb) {
            wcout << " (" << share.first << ", " << share.second << ") ";
        }
        wcout << "\n";
        if (numSymb == 5) {
            break;
        }
    }
    wcout << endl;
    
    int userK = 3;
    while (true) {
        try {
            wcout << L"Введите кол-во частей (k) для расшифровки: ";
            wcin >> userK;
            if (userK > n) {
                throw runtime_error("user_k can't be more than n");
            }
            break;
        } catch (const exception& e) {
            wcout << L"Ошибка (" << e.what() << L"). Попробуйте еще раз.\n";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    for (auto& symb : encrypted) {
        text += (wchar_t)reconstruct_secret(symb, PRIME, userK);
    }

    wcout << L"Расшифрованный текст:\n" << text << endl << endl;
}
