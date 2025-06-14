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

enum class FilePathMode {
    TextFilePath,
    EncryptedFilePath,
    DecryptedFilePath
};

enum class UserMenu {
    MainMenu,
    ShamirMenu
};

void showUserMenu();
void userInputError(const exception& e);
void clearScreen();
void executeTask(Tasks task);
int getProgramChoice();
