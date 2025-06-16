#pragma once

#include <stdexcept>
#include <string>
#include <tuple>

using namespace std;

enum class Tasks {
    ExitProgram,
    Fermat,
    Euclid_uv,
    Euclid,
    Shamir,
    Diophantine,
    AttackSimulations
};

enum class UserMenu {
    ExitMenu,
    ModExpMenu,
    ModInverse1Menu,
    ModInverse2Menu,
    ShamirMenu,
    DiophantineMenu,
    AttackSimulations,
    MainMenu
};

void showUserMenu(int mode);
void userInputError(const exception& e, const string& errorText);
void clearScreen();
void executeTask(Tasks modeTask, int mode);

int getProgramChoice();
