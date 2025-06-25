package algorithms

import (
	"fmt"
	"math"
	"practice2/utils"
)

func SolveDiophantine(a, b, d int64) (int64, int64, []int64) {
	/* Находит x, y для уравнения ax + by = d и цепную дробь a / b */
	gcd := utils.FindGcd(utils.FindGcd(a, b), d)
	finalCoeff := d / gcd

	a /= gcd
	b /= gcd
	d /= gcd

	numerator := a
	denominator := b
	var cf []int64

	termCount := 0
	for denominator != 1 {
		cf = append(cf, numerator / denominator)

		remains := numerator % denominator

		numerator = denominator
		denominator = remains
		termCount++
	}

	finalNumerator := int64(1)
	finalDenominator := cf[termCount - 1]
	for _, val := range cf {
		finalNumerator = val * finalDenominator + finalNumerator
		temp := finalDenominator
		finalDenominator = finalNumerator
		finalNumerator = temp
	}

	x := int64(math.Pow(-1, float64(termCount - 1))) * finalNumerator * finalCoeff
	y := int64(math.Pow(-1, float64(termCount))) * finalDenominator * finalCoeff

	return x, y, cf
}

func SolveDioph() {
	var a int64 = 275
	var b int64 = 145
	var d int64 = 10

	x, y, chainFractions := SolveDiophantine(a, b, d)
	
	fmt.Printf("Найденный X: %d \n", x)
	fmt.Printf("Найденный Y: %d \n", y)

	fmt.Print("Цепная дробь: [")
	for i, val := range chainFractions {
		fmt.Print(val)
		if i == 0 {
			fmt.Print("; ")
		} else if i != len(chainFractions) - 1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")

	fmt.Printf("Решение уравнения: %d*x + %d*y = %d:\n", a, b, d)
	fmt.Printf("x = %d \ny = %d \n\n", x, y)
}
