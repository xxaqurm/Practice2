#include <iostream>

using namespace std;

int modinv(int c, int m) {
    int m0 = m;
    int u0 = 1, u1 = 0;
    int v0 = 0, v1 = 1;

    while (m != 0) {
        int q = c / m;
        int temp = c % m;
        c = m;
        m = temp;

        int tmp_u = u0 - q * u1;
        u0 = u1;
        u1 = tmp_u;

        int tmp_v = v0 - q * v1;
        v0 = v1;
        v1 = tmp_v;
    }

    if (c != 1) {
        throw std::invalid_argument("Обратного элемента не существует (НОД != 1)");
    }

    return (u0 % m0 + m0) % m0;
}

int main() {
    try {
        int c = 3;
        int m = 11;
        int inverse = modinv(c, m);
        cout << "modinv (" << c << ", " << m << ") = " << inverse << endl;
    } catch(const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}