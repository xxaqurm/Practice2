package utils

import (
	"math/rand"
	"time"
)

func ModPow(a, x, p int64) int64 {
    if p == 1 {
        return 0
    }

    result := int64(1)
    a = a % p
    
    for x > 0 {
        if x % 2 == 1 {
            result = (result * a) % p
        }
        x = x >> 1
        a = (a * a) % p
    }
    return result
}

func FindGcd(a int64, b int64) int64 {
	/* Находит НОД(a, b) */
	if b == 0 {
		return a
	}
	return FindGcd(b, a % b)
}

func ExtendedEuclid(a int64, b int64) (uint64, int64, int64) {
	/* Расширенный алгоритм Евклида */
	if b == 0 {
		return uint64(a), 1, 0
	}

	gcd, u1, v1 := ExtendedEuclid(b, a % b)
	u := v1
	v := u1 - int64(a / b) * v1

	return gcd, u, v
}

func EratosthenesSieve(limit int) []int64 {
	/* Строит решето Эратосфена */
	if limit < 2 {
		return []int64{}
	}

	isPrime := make([]bool, limit+1)
	for i := range isPrime {
		isPrime[i] = true
	}
	isPrime[0], isPrime[1] = false, false

	for p := 2; p*p <= limit; p++ {
		if isPrime[p] {
			for i := p * p; i <= limit; i += p {
				isPrime[i] = false
			}
		}
	}

	var primes []int64
	for i := 2; i <= limit; i++ {
		if isPrime[i] {
			primes = append(primes, int64(i))
		}
	}

	return primes
}

func Factorize(num int64) [][2]int64 {
	/* Разложение числа в канонический вид */
	primes := EratosthenesSieve(500)
	var result [][2]int64

	for _, prime := range primes {
		if prime > num {
			break
		}
		var exponent int64 = 0
		for num%prime == 0 && num > 0 {
			exponent++
			num /= prime
		}
		if exponent > 0 {
			result = append(result, [2]int64{prime, exponent})
		}
	}
	return result
}

func MillerTest(n int64, t int) bool {
	/* Вероятностный тест Миллера */
	if n == 2 || n == 3 || n == 5 || n == 7 {
		return true
	}
	if n < 10 || n%2 == 0 {
		return false
	}

	seed := time.Now().UnixNano()
	rng := rand.New(rand.NewSource(seed))

	nums := make(map[int64]bool)
	for len(nums) < t {
		candidate := rng.Int63n(n-2) + 2
		nums[candidate] = true
	}

	for a := range nums {
		if ModPow(a, n-1, n) != 1 {
			return false
		}
	}

	primeFactors := Factorize(n - 1)
	for _, factor := range primeFactors {
		q := factor[0]
		onlyOne := true
		for a := range nums {
			if ModPow(a, (n-1)/q, n) != 1 {
				onlyOne = false
				break
			}
		}
		if onlyOne {
			return false
		}
	}
	return true
}

func GenerateRandomPrime(bitLength uint) int64 {
    /* Генерация случайного числа длины bitLength */
    seed := time.Now().UnixNano()
    rng := rand.New(rand.NewSource(seed))

    for {
        var candidate int64 = rng.Int63()
        candidate |= 1
        candidate |= 1 << (bitLength - 1)

        if MillerTest(candidate, 8) {
            return candidate
        }
    }
}