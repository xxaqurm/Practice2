#include <iostream>
#include <limits>

#include "menu_utils.hpp"
#include "math_utils.hpp"
#include "algorithms.hpp"

using namespace std;

void showUserMenu() {
    /* Выводит пользовательское меню */
    cout << "Выбирите одну из следующих програм:" << endl;
    cout << "0. Выход из программы" << endl;
    cout << "1. Находит значение выражения a^x mod p" << endl;
    cout << "2. Находит значение d выражения (c*d) mod m (через u v)" << endl;
    cout << "3. Находит значение c выражения c^(-1) mod m = d" << endl;
    cout << "4. Шифрует вашу строку при помощи алгоритма Шамира" << endl;
    cout << "5. Реашет уравнение 275a + 145b = 10, а также находит цепную дробь выражения 275 / 145" << endl;
    cout << "Выберите одну из задач: ";
}

void userInputError(const exception& e) {
    cout << ">>> Ошибка (" << e.what() << "): Введите число от 0 до 5. Попробуйте еще раз: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
    /* Очищает консоль */
    system("clear");
}

void executeTask(Tasks task) {
    /* Запуск выбранной программы */
    switch (task) {
        case Tasks::ExitProgram: 
            return;
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
        default:
            cout << "Something wrong" << endl;
            break;
    }
}

int getProgramChoice() {
    /* Выбор программы */
    int choice = 0;
    while (true) {
        try {
            showUserMenu();
            wcin >> choice;

            if (choice < 0 || choice > 5) {
                throw invalid_argument("incorrect_user_choice");
            }
            return choice;
        } catch (const exception& e) {
            userInputError(e);
        }
    }
}
