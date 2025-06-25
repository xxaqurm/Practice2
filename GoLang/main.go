package main

import (
    "fmt"
    "practice2/algorithms"
)

type Program = int
type  MenuMode = int

const (
	ExitProgram Program = iota
	ExponentiationModuloProgram
	ModInverse1Program
	ModInverse2Program
	ShamirEncryptionProgram
	DiophantineProgram
	AttackSimulationsProgram
)

const (
	StartMenu MenuMode = iota
	ExponentiationModuloMenu
	ExtendedEuclidMenu
	BasicEuclidMenu
	ShamirEncryptionMenu
	DiophantineMenu
	AttackSimulationsMenu
)

func showUserMenu(mode MenuMode) {
	/* Выводит пользовательское меню */
	switch (mode) {
		case StartMenu:
			fmt.Println("Выберите одну из следующих программ:")
			fmt.Println("0. Выход из программы")
			fmt.Println("1. Находит значение выражения a^x mod p")
			fmt.Println("2. Находит значение d и (u, v) для выражения (c*d) mod m")
			fmt.Println("3. Находит значение c выражения c^(-1) mod m = d")
			fmt.Println("4. Шифрует ваш файл при помощи алгоритма Шамира")
			fmt.Println("5. Решает уравнение 275a + 145b = 10, а также находит цепную дробь выражения 275 / 145")
			fmt.Println("6. Демонстрация эмуляции атаки на алгоритм Шамира")
			fmt.Print("Выберите одну из задач: ")
		case ExponentiationModuloMenu:
			fmt.Print("Введите свои a, x, p (где p — простое): ")
		case ExtendedEuclidMenu:
			fmt.Print("Введите свои c и m для выражения c*d mod m = 1: ")
		case BasicEuclidMenu:
			fmt.Print("Введите свои c и m для выражения c^(-1) mod m = d: ")
		case ShamirEncryptionMenu:
			fmt.Print("Введите путь до шифруемого файла: ")
		case DiophantineMenu:
			fmt.Println("Решение диофанового уравнения при помощи цепной дроби:")
		case AttackSimulationsMenu:
			fmt.Println("Симуляция атаки MitM на алгоритм Шамира:")
		default:
			fmt.Println(">>> Ошибка: неизвестный режим (showUserMenu function)")
	}
}

func getProgramChoice(mode MenuMode) Program {
	/* Считывание номера программы на выполнение */
	inputError := ">>> Пожалуйста, введите число от 0 до 5."

	showUserMenu(mode)
	for {
		userChoice := 0
		fmt.Scanf("%d", &userChoice)
		if (userChoice < 0 || userChoice > 6) {
			fmt.Println(inputError)
            fmt.Print("Попробуйте еще раз: ")
			continue
		}
		var userProgram Program = Program(userChoice)
		return userProgram
	}
}

func executeTask(task Program, mode MenuMode) {
	/* Запуск выбранной программы */
	showUserMenu(mode)
	switch (task) {
		case ExponentiationModuloProgram:
			algorithms.ExponentiationModulo()
		case ModInverse1Program:
			algorithms.ModInverse1()
		case ModInverse2Program:
			algorithms.ModInverse2()
		case ShamirEncryptionProgram:
			algorithms.Shamir()
		case DiophantineProgram:
			algorithms.SolveDioph()
		case AttackSimulationsProgram:
			algorithms.MitmDemo()
		default:
			fmt.Println(">>> Something went wrong (executeTask function)")
	}
}

func clearScreen() {
	/* Очищает консоль */
	fmt.Print("\033[H\033[2J")
}

func main() {
    clearScreen()
    for {
        program := getProgramChoice(StartMenu)
        clearScreen()

        mode := MenuMode(program)
        executeTask(program, mode)

        if program == ExitProgram {
            clearScreen()
            break
        }
    }
}