#include <iostream>
#include <stdexcept>
#include <gmpxx.h>

#include "algorithms.hpp"
#include "math_utils.hpp"

using namespace std;

void encrypt() {
    /* Шифрование по Шамиру */

}

void decrypt() {
    /* Дешифрование по Шамиру */

}

void shamir() {
    /* Реализация алгоритма Шамира */
    int userChoice = 0;
    int n = 0, k = 0;

    wcin.exception(ios::failbit);
    
    while (true) {
        cout << "Выберите режим:" << endl;
        cout << "1. Зашифровать файл" << endl;
        cout << "2. Расшифровать файл" << endl;
        cout << "Введите номер действия: ";

        string errorText = "Введите число от 1 до 2";

        try {
            cin >> userChoice;
            if ()
        } catch (const ios::failure& e) {
            userInputError(e, errorText);
        } catch (const ios::failure& e) {
            userInputError(e, errorText);
        }
    }

    wstring filePath;
    wstring fileEncryptedPath;
    wstring fileDecryptedPath;
    
    FilePathMode userMode = static_cast<FailePathMode>userChoice;
    while (true) {
        switch (userMode) {
            case userMode::TextFilePath:
                break;
            case userMode::EncryptedFilePath:
                break;
            case userMode::DecryptedFilePath:
                break;
        }
    }
}
