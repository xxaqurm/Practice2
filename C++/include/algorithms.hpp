#pragma once

#include <gmpxx.h>
#include <string>
#include <vector>

using namespace std;

typedef pair<mpz_class, mpz_class> Share;
typedef vector<Share> ShareGroup;
typedef vector<ShareGroup> ShareMatrix;

void exponentiationModulo();
void modInverse1();
void modInverse2();
void shamir();
void solveDioph();
void mitmDemo();
void simulateMitMAttack(ShareMatrix& es, int sharesToCorrupt = 1);

void encrypt(string fp, string efp, int n, int k, ShareMatrix& es);
void decrypt(string dfp, int userK, ShareMatrix es);
void createEncDecFiles(string& fp, string& encryptedFilePath, string& decryptedFilePath);
void readShamirParameters(int& n, int& k, int& userK);
