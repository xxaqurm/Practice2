#include <iostream>
#include <stdexcept>
#include <locale>

#include <gmpxx.h>

#include "algorithms.hpp"
#include "math_utils.hpp"
#include "menu_utils.hpp"

using namespace std;

int main() {
    locale::global(locale(""));
    wcin.imbue(locale());
    wcout.imbue(locale());

    wcin.exceptions(ios::failbit);

    bool exitProgram = false;
    while (!exitProgram) {
        int programNumber = getProgramChoice();
        clearScreen();

        if (programNumber == 0) {
            exitProgram = true;
            continue;
        }

        executeTask(static_cast<Tasks>(programNumber));

        wcin.clear();
        wcin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    wcout << L"Программа завершена!" << endl;
}
