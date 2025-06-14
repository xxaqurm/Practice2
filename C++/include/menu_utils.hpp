#pragma once

#include <stdexcept>
using namespace std;

enum class Tasks {
    ExitProgram,
    Fermat,
    Euclid_uv,
    Euclid,
    Shamir,
    Equation
};

void showUserMenu();
void userInputError(const exception& e);
void clearScreen();
void executeTask(Tasks task);
int getProgramChoice();
