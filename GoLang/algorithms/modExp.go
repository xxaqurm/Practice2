package algorithms

import (
    "fmt"
    "practice2/utils"
)

func ExponentiationModulo() {
    var a, x, p int64;
    fmt.Scanf("%d %d %d", &a, &x, &p);

    result := utils.ModPow(a, x, p)
    fmt.Printf("%d^%d mod %d = %d\n\n", a, x, p, result)
}
