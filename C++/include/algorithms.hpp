#pragma once

#include <gmpxx.h>
#include <string>
#include <vector>

using namespace std;

typedef pair<mpz_class, mpz_class> Share;
typedef vector<Share> ShareGroup;
typedef vector<ShareGroup> ShareMatrix;

void modexp();
void mod_inverse1();
void mod_inverse2();
void shamir();
void solve_dioph();
void encrypt(const string& fp, const string& efp, const int& n, const int& k, ShareMatrix& es);
void decrypt(const string& dfp, const int& userK, const ShareMatrix& es);
void createEncDecFiles(string& fp, string& encryptedFilePath, string& decryptedFilePath);
void readShamirParameters(int& n, int& k, int& userK);

mpz_class fermat_mod(mpz_class a, mpz_class x, mpz_class p);
