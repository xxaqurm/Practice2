#include <iostream>
#include <limits>
#include <fstream>
#include <tuple>

#include <string>

#include "menuUtils.hpp"
#include "mathUtils.hpp"
#include "algorithms.hpp"

using namespace std;

void showUserMenu(MenuMode mode) {
    /* Выводит пользовательское меню */
    switch (mode) {
        case MenuMode::StartMenu:
            cout << "Выбирите одну из следующих програм:" << endl;
            cout << "0. Выход из программы" << endl;
            cout << "1. Находит значение выражения a^x mod p" << endl;
            cout << "2. Находит значение d и (u, v) для выражения (c*d) mod m " << endl;
            cout << "3. Находит значение c выражения c^(-1) mod m = d" << endl;
            cout << "4. Шифрует вашу строку при помощи алгоритма Шамира" << endl;
            cout << "5. Реашет уравнение 275a + 145b = 10, а также находит цепную дробь выражения 275 / 145" << endl;
            cout << "6. Демонстрация эмуляции атаки на алгоритм Шамира" << endl;
            cout << "Выберите одну из задач: ";
            break;
        case MenuMode::ExponentiationModuloMenu:
            cout << "Введите свои a, x, p (где p - простое): ";
            break;
        case MenuMode::ModInverse1Menu:
            cout << "Введите свои c и m для выражения c*d mod m = 1: ";
            break;
        case MenuMode::ModInverse2Menu:
            cout << "Введите свои c и m для выражения c^(-1) mod m = d: ";
            break;
        case MenuMode::ShamirEncryptionMenu:
            cout << "Введите путь до шифруемого файла: ";
            break;
        case MenuMode::DiophantineMenu:
            break;
        case MenuMode::AttackSimulationsMenu:
            cout << "Симуляция атаки MitM на алгоритм Шамира: " << endl;
            break;
        default:
            cout << ">>> Error: something wrong (showUserMenu function)";
            break;
    }
}

Program getProgramChoice(MenuMode mode) {
    /* Считывание номера программы на выполнение */
    string inputError = "Пожалуйста, введите число от 0 до 5\n";
    
    while (true) {
        showUserMenu(mode);
        int userChoice = 0;
        try {
            cin >> userChoice;
            if (userChoice < 0 || userChoice > 6) {
                throw invalid_argument("incorrect_user_choice");
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Program userProgram = static_cast<Program>(userChoice);
            return userProgram;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, inputError);
        }
    }
}

void executeTask(Program task, MenuMode mode) {
    /* Запуск выбранной программы */
    showUserMenu(mode);
    switch (task) {
        case Program::ExponentiationModuloProgram:
            exponentiationModulo();
            break;
        case Program::ModInverse1Program:
            modInverse1();
            break;
        case Program::ModInverse2Program:
            modInverse2();
            break;
        case Program::ShamirEncryptionProgram:
            shamir();
            break;
        case Program::DiophantineProgram:
            solveDioph();
            break;
        case Program::AttackSimulationsProgram:
            mitmDemo();
            break;
        default:
            cout << ">>> Something wrong (executeTask function)" << endl;
            break;
    }
}

void userInputError(const exception e, const string errorText) {
    /* Выводим ошибку ввода */
    cout << ">>> Ошибка (" << e.what() << "): " << errorText << endl;
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Попробуйте еще раз: ";
}

void clearScreen() {
    /* Очищает консоль */
    system("clear");
}
