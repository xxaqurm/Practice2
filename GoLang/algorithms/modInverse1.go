package algorithms

import (
	"fmt"
	"practice2/utils"
)

func ModInverse1() {
	var c, m int64
	for {
		fmt.Scanf("%d %d", &c, &m)
		if m < 1 || utils.FindGcd(c, m) != 1 {
			fmt.Println("m должно быть больше 0. c и m должны быть взаимно простыми.")
			fmt.Print("Попробуйте снова: ")
			continue
		}
		break
	}

	_, u, _ := utils.ExtendedEuclid(c, m)
	
	d :=  (u % m + m) % m

	fmt.Printf("%d*d mod %d = 1\n", c, m)
	fmt.Printf("d = %d \n\n", d)
}
