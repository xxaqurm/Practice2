#include <iostream>
#include <stdexcept>
#include <locale>
#include <gmpxx.h>

#include "menuUtils.hpp"

using namespace std;

int main(void) {
    cin.exceptions(ios::failbit);
    clearScreen();
    while (true) {
        Program program = getProgramChoice(MenuMode::StartMenu);
        clearScreen();

        MenuMode mode = static_cast<MenuMode>(program);
        executeTask(program, mode);

        if (program == Program::ExitProgram) {
            clearScreen();
            return 0;
        }
    }
}
