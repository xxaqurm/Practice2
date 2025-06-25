package algorithms

import (
	"bufio"
	"crypto/rand"
	"fmt"
	"math/big"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

const prime = 7919 // Простое число > 255

type Share struct {
	X int
	Y []int
}

func randCoeff() int {
	nBig, _ := rand.Int(rand.Reader, big.NewInt(prime))
	return int(nBig.Int64())
}

func generatePolynomial(secretByte int, k int) []int {
	coeffs := make([]int, k)
	coeffs[0] = secretByte
	for i := 1; i < k; i++ {
		coeffs[i] = randCoeff()
	}
	return coeffs
}

func evalPolynomial(coeffs []int, x int) int {
	result := 0
	powX := 1
	for _, coeff := range coeffs {
		result = (result + coeff*powX) % prime
		powX = (powX * x) % prime
	}
	return result
}

func splitSecret(secret []byte, n, k int) []Share {
	shares := make([]Share, n)
	for i := 0; i < n; i++ {
		shares[i].X = i + 1
		shares[i].Y = make([]int, len(secret))
	}
	for idx, b := range secret {
		coeffs := generatePolynomial(int(b), k)
		for i := 0; i < n; i++ {
			shares[i].Y[idx] = evalPolynomial(coeffs, shares[i].X)
		}
	}
	return shares
}

func modInverse(a, m int) int {
	a = ((a % m) + m) % m
	t, newT := 0, 1
	r, newR := m, a
	for newR != 0 {
		quotient := r / newR
		t, newT = newT, t-quotient*newT
		r, newR = newR, r-quotient*newR
	}
	if r > 1 {
		panic("modular inverse does not exist")
	}
	if t < 0 {
		t += m
	}
	return t
}

func recoverByte(x []int, y []int) int {
	result := 0
	for i := range x {
		num, den := 1, 1
		for j := range x {
			if i != j {
				num = (num * (-x[j])) % prime
				den = (den * (x[i] - x[j])) % prime
			}
		}
		num = ((num % prime) + prime) % prime
		den = ((den % prime) + prime) % prime
		denInv := modInverse(den, prime)
		term := y[i] * num * denInv
		result = (result + term) % prime
	}
	if result < 0 {
		result += prime
	}
	return result
}

func reconstructSecret(shares []Share) []byte {
	length := len(shares[0].Y)
	result := make([]byte, length)
	for i := 0; i < length; i++ {
		x := make([]int, len(shares))
		y := make([]int, len(shares))
		for j, share := range shares {
			x[j] = share.X
			y[j] = share.Y[i]
		}
		result[i] = byte(recoverByte(x, y))
	}
	return result
}

func writeEncrypted(path string, shares []Share) error {
	file, err := os.Create(filepath.Join(path, "encrypted.txt"))
	if err != nil {
		return err
	}
	defer file.Close()
	writer := bufio.NewWriter(file)
	for _, share := range shares {
		line := fmt.Sprintf("%d:%v\n", share.X, share.Y)
		_, err := writer.WriteString(line)
		if err != nil {
			return err
		}
	}
	return writer.Flush()
}

func readEncrypted(path string, k int) ([]Share, error) {
	file, err := os.Open(filepath.Join(path, "encrypted.txt"))
	if err != nil {
		return nil, err
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	var shares []Share
	for scanner.Scan() {
		if len(shares) >= k {
			break
		}
		line := scanner.Text()
		parts := strings.SplitN(line, ":", 2)
		if len(parts) != 2 {
			continue
		}
		x, _ := strconv.Atoi(parts[0])
		yStr := strings.Trim(parts[1], "[]")
		yParts := strings.Split(yStr, " ")
		var y []int
		for _, val := range yParts {
			v, _ := strconv.Atoi(val)
			y = append(y, v)
		}
		shares = append(shares, Share{X: x, Y: y})
	}
	return shares, nil
}

func Shamir() {
	reader := bufio.NewReader(os.Stdin)
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

	// Ввод k (минимальное количество долей для восстановления)
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

	// Шифрование
	shares := splitSecret(content, n, k)
	dir := filepath.Dir(inputPath)
	err = writeEncrypted(dir, shares)
	if err != nil {
		fmt.Println("Ошибка при сохранении encrypted.txt:", err)
		return
	}
	fmt.Println("Файл encrypted.txt успешно создан.")

	// Дешифрование
	readShares, err := readEncrypted(dir, k)
	if err != nil {
		fmt.Println("Ошибка при чтении encrypted.txt:", err)
		return
	}
	recovered := reconstructSecret(readShares)

	err = os.WriteFile(filepath.Join(dir, "decrypted.txt"), recovered, 0644)
	if err != nil {
		fmt.Println("Ошибка записи файла decrypted.txt:", err)
		return
	}
	fmt.Println("Файл decrypted.txt успешно создан.")
}

func SimulateMitMAttack(shares []Share, sharesToCorrupt int) {
	fmt.Println("\n[!] MitM: Симулируется атака «человек посередине»...")

	corrupted := 0
	for i := 0; i < len(shares) && corrupted < sharesToCorrupt; i++ {
		if len(shares[i].Y) > 0 {
			for j := 0; j < len(shares[i].Y); j++ { // искажаем все байты доли
				shares[i].Y[j] = (shares[i].Y[j] + 1) % prime
			}
			corrupted++
		}
	}

	fmt.Printf("[!] MitM: %d доля(и) были изменены.\n", corrupted)
}
