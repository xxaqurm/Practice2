#pragma once

#include <gmpxx.h>

void modexp();
void mod_inverse1();
void mod_inverse2();
void shamir();
void solve_dioph();

mpz_class fermat_mod(mpz_class a, mpz_class x, mpz_class p);
