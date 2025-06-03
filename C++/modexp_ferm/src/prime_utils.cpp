#include <cmath>
#include "prime_utils.h"

bool is_prime(int a) {
    /* Проверяет число на простоту */
    for (int i = 2; i <= (int)sqrt(a); i++) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}
