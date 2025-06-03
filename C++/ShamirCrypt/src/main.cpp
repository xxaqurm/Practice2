#include <iostream>
#include <stdexcept>
#include <clocale>
#include <cstdint>
#include <string>
#include <limits>
#include "shamir.h"
#include "math_utils.h"

using namespace std;
const uint64_t PRIME = 208351617373;

int main() {
    setlocale(LC_ALL, "");
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

    wcout << L"Расшифрованный текст:\n" << text << endl;
}
