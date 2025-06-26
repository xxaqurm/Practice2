package algorithms

import (
	"os"
	"fmt"
	"bufio"
	"strings"
	"path/filepath"
)

func MitmDemo() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Введите путь к файлу, который вы хотите зашифровать: ")
	inputPathRaw, _ := reader.ReadString('\n')
	inputPath := strings.TrimSpace(inputPathRaw)

	content, err := os.ReadFile(inputPath)
	if err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	var n int
	for {
		fmt.Print("Введите общее количество долей (n): ")
		_, err = fmt.Scanf("%d\n", &n)
		if err != nil || n < 1 {
			fmt.Println("Ошибка: введите положительное целое число.")
			continue
		}
		break
	}

	var k int
	for {
		fmt.Print("Введите минимальное количество долей для расшифровки (k): ")
		_, err = fmt.Scanf("%d\n", &k)
		if err != nil || k < 1 || k > n {
			fmt.Println("Ошибка: k должно быть положительным и не больше n.")
			continue
		}
		break
	}
	userK := k

	fmt.Print("Введите количество символов, которые хотите изменить (для атаки MitM): ")
	var sharesToCorrupt int
	_, err = fmt.Scanf("%d\n", &sharesToCorrupt)
	if err != nil || sharesToCorrupt < 1 {
		fmt.Println("Ошибка: введите корректное положительное число.")
		return
	}

	shares := splitSecret(content, n, k)

	SimulateMitMAttack(shares, sharesToCorrupt)

	dir := filepath.Dir(inputPath)
	recovered := reconstructSecret(shares[:userK])

	err = os.WriteFile(filepath.Join(dir, "mitm_decrypted.txt"), recovered, 0644)
	if err != nil {
		fmt.Println("Ошибка записи файла mitm_decrypted.txt:", err)
		return
	}
	fmt.Println("\nЗавершено. Проверьте файл:", filepath.Join(dir, "mitm_decrypted.txt"))
	fmt.Println("Если доли были повреждены, то текст должен быть искажён.")
}
