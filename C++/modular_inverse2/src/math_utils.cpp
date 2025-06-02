#include <tuple>
#include "math_utils.h"

using namespace std;

int find_gcd(int a, int b) {
    /* Находит НОД(a, b) */
    if (b == 0) {
        return a;
    }
    return find_gcd(b, a % b);
}

tuple<int, int, int> extended_gcd(int a, int b) {
    /* Расширенный алгоритм евклида для нахождения gcd и "u", "v" */
    if (b == 0) {
        return {a, 1, 0};
    }

    int gcd, u1, v1;
    tie(gcd, u1, v1) = extended_gcd(b, a % b);

    int u = v1;
    int v = u1 - (a / b) * v1;

    return {gcd, u, v};
}

int mod_inverse(int c, int m) {
    /* Находит обратный элемент к "c" по модолю "m" */
    int gcd, u, v;
    tie(gcd, u, v) = extended_gcd(c, m);

    if (u < 0) {
        u += m;
    }
    return u;
}