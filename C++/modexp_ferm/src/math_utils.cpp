#include "math_utils.h"

int fermat_mod(int a, int x, int p) {
    /* Вычисляет a^x mod p, используя теорему Ферма */
    int result = 1;
    int base = a % p;
    while (x > 0) {
        if (x & 1) {
            result = (result * base) % p;
        }
        base = (base * base) % p;
        x >>= 1;
    }
    return result;
}
