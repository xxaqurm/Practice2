#include <iostream>
#include <limits>
#include <fstream>
#include <tuple>

#include <string>

#include "menu_utils.hpp"
#include "math_utils.hpp"
#include "algorithms.hpp"
#include "mitm_attack.hpp"

using namespace std;

void showUserMenu(int mode) {
    /* Выводит пользовательское меню */
    UserMenu menuMode = static_cast<UserMenu>(mode);
    switch (menuMode) {
        case UserMenu::MainMenu:
            cout << "Выбирите одну из следующих програм:" << endl;
            cout << "0. Выход из программы" << endl;
            cout << "1. Находит значение выражения a^x mod p" << endl;
            cout << "2. Находит значение d выражения (c*d) mod m (через u v)" << endl;
            cout << "3. Находит значение c выражения c^(-1) mod m = d" << endl;
            cout << "4. Шифрует вашу строку при помощи алгоритма Шамира" << endl;
            cout << "5. Реашет уравнение 275a + 145b = 10, а также находит цепную дробь выражения 275 / 145" << endl;
            cout << "6. Демонстрация эмуляции атаки на алгоритм Шамира" << endl;
            cout << "Выберите одну из задач: ";
            break;
        case UserMenu::ModExpMenu:
            cout << "Введите свои a, x, p (где p - простое): ";
            break;
        case UserMenu::ModInverse1Menu:
            cout << "Введите свои c и m для выражения c*d mod m = 1: ";
            break;
        case UserMenu::ModInverse2Menu:
            cout << "Введите свои c и m для выражения c^(-1) mod m = d: ";
            break;
        case UserMenu::ShamirMenu:
            cout << "Введите путь до шифруемого файла: ";
            break;
        case UserMenu::DiophantineMenu:
            break;
        case UserMenu::AttackSimulations:
            cout << "Симуляция атаки MitM на алгоритм Шамира: " << endl;
            break;
        case UserMenu::ExitMenu:
            break;
    }
}

void userInputError(const exception& e, const string& errorText) {
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

void executeTask(Tasks task, int mode) {
    /* Запуск выбранной программы */
    showUserMenu(mode);
    switch (task) {
        case Tasks::ExitProgram:
            break;
        case Tasks::Fermat:
            modexp();
            break;
        case Tasks::Euclid_uv:
            mod_inverse1();
            break;
        case Tasks::Euclid:
            mod_inverse2();
            break;
        case Tasks::Shamir:
            shamir();
            break;
        case Tasks::Diophantine:
            solve_dioph();
            break;
        case Tasks::AttackSimulations:
            mitmDemo();
            break;
        default:
            cout << "Something wrong" << endl;
            break;
    }
}

int getProgramChoice() {
    /* Считывание программы на выполнение */
    string inputError = "Ошибка ввода. Пожалуйста, введите целое число.\n";
    string rangeError = "Ошибка диапазона. Пожалуйста, введите число от 0 до 5\n";
    int menuMode = 7;
    
    while (true) {
        showUserMenu(menuMode);
        int userChoice = 0;
        try {
            cin >> userChoice;
            if (userChoice < 0 || userChoice > 6) {
                throw invalid_argument("incorrect_user_choice");
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return userChoice;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, rangeError);
        }
    }
}
