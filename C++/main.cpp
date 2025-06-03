#include <iostream>
#include <stdexcept>
#include <limits>
#include <clocale>
#include "include/task_functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    wcin.exceptions(ios::failbit);

    bool exitProgram = false;
    while (!exitProgram) {
        int programNumber = 0;
        while (true) {
            try {
                wcout << L"Выбирите одну из следующих програм:" << endl;
                wcout << L"1. Находит значение выражения a^x mod p" << endl;
                wcout << L"2. Находит значение d выражения (c*d) mod m" << endl;
                wcout << L"3. Находит значение c выражения c^(-1) mod m = d" << endl;
                wcout << L"4. Шифрует вашу строку при помощи алгоритма Шамира" << endl;
                wcout << L"5. Реашет уравнение 275a + 145b = 10, а также находит цепную дробь выражения 275 / 145" << endl;
                wcout << L"0. Выход из программы" << endl;
                wcout << L"Выберите одну из задач: ";

                wcin >> programNumber;
                if (programNumber < 0 || programNumber > 5) {
                    throw runtime_error("incorrect_programNumber");
                }
                break;
            } catch(const ios_base::failure& e) {
                //system("clear");
                wcout << L">>> Ошибка (" << e.what() << L"): Введите номер задачи (0 - 5). Попробуйте еще раз.";
                wcin.clear();
                wcin.ignore(numeric_limits<streamsize>::max(), '\n');
            } catch(const exception& e) {
                //system("clear");
                wcout << L">>> Ошибка (" << e.what() << L"): Выберите номер задачи (0 - 5). Попробуйте еще раз.";
                wcin.clear();
                wcin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (programNumber) {
            case 0:
                exitProgram = true;
                break;
            case 1:
                modexp();
                break;
            case 2:
                mod_inverse1();
                break;
            case 3:
                mod_inverse2();
                break;
            case 4:
                shamir();
                break;
            case 5:
                solve_dioph();
                break;
            default:
                wcout << L"ERROR" << endl;
                break;
        }

        wcin.clear();
        wcin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}