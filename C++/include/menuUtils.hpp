#pragma once

#include <stdexcept>
#include <string>
#include <tuple>

using namespace std;

enum class Program {
    ExitProgram,
    ExponentiationModuloProgram,
    ModInverse1Program,
    ModInverse2Program,
    ShamirEncryptionProgram,
    DiophantineProgram,
    AttackSimulationsProgram
};

enum class MenuMode {
    StartMenu,
    ExponentiationModuloMenu,
    ExtendedEuclidMenu,
    BasicEuclidMenu,
    ShamirEncryptionMenu,
    DiophantineMenu,
    AttackSimulationsMenu,
};

Program getProgramChoice(MenuMode mode);

void showUserMenu(MenuMode mode);
void userInputError(const exception e, const string errorText);
void clearScreen();
void executeTask(Program modeTask, MenuMode mode);
