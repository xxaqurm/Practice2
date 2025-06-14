#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <limits>
#include <tuple>
#include <vector>
#include <random>

#include "algorithms.hpp"

using namespace std;
const uint64_t PRIME = 208351617373;

mpz_class modinv(mpz_class a, mpz_class mod) {
    /* Находит обратный элемент по модулю */
    return fermat_mod(a, mod - 2, mod);
}

mpz_class evaluate_polynomial(mpz_class x, uint64_t p, const vector<mpz_class>& coeffs) {
    /* Вычисление многочлена f(x) по коэффициентам */
    mpz_class result = 0;
    mpz_class power = 1;
    for (auto c : coeffs) {
        result = (result + (mpz_class)c * power % p) % p;
        power = (mpz_class)power * x % p;
    }
    return result;
}

vector<pair<mpz_class, mpz_class>> generate_shares(mpz_class secret, uint64_t p, int k, int n) {
    /* Генерация n частей секрета */
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(0, p - 1);

    vector<mpz_class> coeffs;
    coeffs.push_back(secret);
    for (mpz_class i = 1; i < k; i++)
        coeffs.push_back(dist(gen));

    vector<pair<mpz_class, mpz_class>> shares;
    for (int i = 1; i <= n; i++) {
        mpz_class x = i;
        mpz_class y = evaluate_polynomial(x, p, coeffs);
        shares.push_back({x, y});
    }
    return shares;
}

uint64_t reconstruct_secret(const vector<pair<mpz_class, mpz_class>>& shares, uint64_t p, int k) {
    /* Восстановление секрета по k частям */
    mpz_class secret = 0;
    for (int i = 0; i < k; i++) {
        mpz_class xi = shares[i].first;
        mpz_class yi = shares[i].second;

        mpz_class num = 1, denom = 1;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                mpz_class xj = shares[j].first;
                num = (mpz_class)num * (p - xj) % p;
                denom = (mpz_class)denom * (xi + p - xj) % p;
            }
        }
        mpz_class lagrange = (mpz_class)num * modinv(denom, p) % p;
        secret = (secret + yi * lagrange % p) % p;
    }
    return secret.get_ui();
}

void shamir() {
    cin.exceptions(ios::failbit);

    int k = 0;
    int n = 0;

    while (true) {
        try {
            if (n == 0) {
                cout << "Введите количество частей (n), на которое будет разбит ваш текст: ";
                cin >> n;
                if (n < 1) {
                    n = 0;
                    throw runtime_error("n cannot be less than 1");
                }
            }
            cout << "Введите количество ключей (k), которых достаточно для расшифровки: ";
            cin >> k;
            if (k < 1) {
                k = 0;
                throw runtime_error("k cannot be less than 1");
            } else if (k > n) {
                k = 0;
                throw runtime_error("k cannot be greater than n");
            }
            break;
        } catch (const ios_base::failure& e) {
            cout << ">>> Ошибка(" << e.what() << "). Следует ввести число. Попробуйте еще раз: " << endl; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cout << ">>> Ошибка(" << e.what() << "): Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    wstring text;
    
    cout << "\nВведите строку, которую хотите зашифровать: ";
    getline(wcin, text);
 
    vector<vector<pair<mpz_class, mpz_class>>> encrypted;
    for (wchar_t wc : text) {
        mpz_class code = (mpz_class)wc;
        encrypted.push_back(generate_shares(code, PRIME, k, n));
    }
    text.clear();

    mpz_class numSymb = 1;
    cout << "\nНесколько частей:\n";
    for (auto& symb : encrypted) {
        cout << numSymb++;
        for (auto& share : symb) {
            cout << " (" << share.first << ", " << share.second << ") ";
        }
        cout << "\n";
        if (numSymb == 5) {
            break;
        }
    }
    cout << endl;
    
    int userK = 0;
    while (true) {
        try {
            cout << "Введите кол-во частей (k) для расшифровки: ";
            cin >> userK;
            if (userK > n) {
                throw runtime_error("user_k can't be more than n");
            }
            break;
        } catch (const exception& e) {
            cout << "Ошибка (" << e.what() << "). Попробуйте еще раз.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    for (auto& symb : encrypted) {
        text += (wchar_t)reconstruct_secret(symb, PRIME, userK);
    }

    wcout << L"Расшифрованный текст:\n" << text << endl << endl;
}
