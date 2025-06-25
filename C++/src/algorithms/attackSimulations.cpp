#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "mathUtils.hpp"
#include "menuUtils.hpp"
#include "algorithms.hpp"

using namespace std;

extern const mpz_class PRIME;

void simulateMitMAttack(ShareMatrix& es, int sharesToCorrupt) {
    /* Симуляция атаки MitM (подменяет часть долей) */
    std::cout << "\n[!] MitM: Симулируется атака «человек посередине»...\n";

    int corruptedCount = 0;

    for (auto& group : es) {
        if (corruptedCount >= sharesToCorrupt)
            break;

        if (!group.empty()) {
            group[0].second += 1;  // искажаем долю: y -> y + 1
            corruptedCount++;
        }
    }

    std::cout << "[!] MitM: " << corruptedCount << " доля(и) были изменены.\n";
}

void readSharesToCorrupt(int& sharesToCorrupt) {
    string inputError = "Введите целоче число, большее 0";
    while (true) {
        try {
            cout << "Введите количество символов, которое хотите изменить: ";
            cin >> sharesToCorrupt;
            if (sharesToCorrupt < 1) {
                throw invalid_argument("invalid_shares_count");
            }
            break;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, inputError);
        }
    }
}

void mitmDemo() {
    string filePath, encryptedFilePath, decryptedFilePath;

    cout << "Введите путь к файлу, который вы хотите зашифровать: ";
    createEncDecFiles(filePath, encryptedFilePath, decryptedFilePath);

    int n, k, userK;
    readShamirParameters(n, k, userK);

    int sharesToCorrupt = 1;
    ShareMatrix shares;
    string inputError = "ошибка во время демонстрации MitM-атаки";

    readSharesToCorrupt(sharesToCorrupt);
    try {
        encrypt(filePath, encryptedFilePath, n, k, shares);
        simulateMitMAttack(shares, sharesToCorrupt);
        decrypt(decryptedFilePath, userK, shares);

        cout << "\nЗавершено. Проверьте файл: " << decryptedFilePath << endl;
        cout << "Если доли были повреждены, то текст искажен.\n";
    } catch (const exception& e) {
        userInputError(e, inputError);
    }
    cout << endl;
}
