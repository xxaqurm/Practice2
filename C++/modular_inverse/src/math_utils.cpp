#include <tuple>
#include "math_utils.h"

using namespace std;

int find_gcd(int a, int b) {
    /* Находит НОД(a, b) */
    while (b != 0) {
        int prevB = b;
        b = a % b;
        a = prevB;
    }
    return a;
}

tuple<int, int, int> extended_gcd(int a, int b) {
    /* находит d в выражении (c * d) mod m = 1 */
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
    int gcd, u, v;
    tie(gcd, u, v) = extended_gcd(c, m);

    u = u < 0 ? u + m : u;
    return u;
}