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
    cin.imbue(locale());
    cout.imbue(locale());

    cin.exceptions(ios::failbit);

    bool exitProgram = false;
    while (!exitProgram) {
        int programNumber = getProgramChoice();
        clearScreen();

        executeTask(static_cast<Tasks>(programNumber), programNumber);

        if (programNumber == 0) {
            exitProgram = true;
            continue;
        }
    }
}
