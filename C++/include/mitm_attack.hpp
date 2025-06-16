#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <gmpxx.h>

typedef std::pair<mpz_class, mpz_class> Share;
typedef std::vector<Share> ShareGroup;
typedef std::vector<ShareGroup> ShareMatrix;

void mitmDemo();
void simulateMitMAttack(ShareMatrix& es, int sharesToCorrupt = 1);
