#include <iostream>
#include <stdexcept>
#include <fstream>
#include <gmpxx.h>
#include <vector>
#include <tuple>
#include <ctime>
#include <cstdint>

#include "algorithms.hpp"
#include "math_utils.hpp"
#include "menu_utils.hpp"

using namespace std;

typedef pair<mpz_class, mpz_class> Share;
typedef vector<Share> ShareGroup;
typedef vector<ShareGroup> ShareMatrix;

const mpz_class PRIME = generateRandomPrime(40);

mpz_class evalPolynomial(const vector<mpz_class>& coeffs, const mpz_class& x, const mpz_class& p) {
    mpz_class result = 0, powX = 1;
    for (auto& coef : coeffs) {
        result = (result + coef * powX) % p;
        powX = (powX * x) % p;
    }
    return result;
}

ShareGroup shamirSplit(const mpz_class& secret, int n, int k, const mpz_class& p, gmp_randclass& rng) {
    vector<mpz_class> coeffs(k);
    coeffs[0] = secret;
    for (int i = 1; i < k; ++i) {
        coeffs[i] = rng.get_z_range(p);
    }

    ShareGroup shares;
    for (int i = 1; i <= n; ++i) {
        mpz_class x = i;
        mpz_class y = evalPolynomial(coeffs, x, p);
        shares.emplace_back(x, y);
    }
    return shares;
}

mpz_class bytesToMpz(const vector<unsigned char>& bytes) {
    mpz_class result = 0;
    for (unsigned char byte : bytes) {
        result <<= 8;
        result += byte;
    }
    return result;
}

vector<unsigned char> mpzToBytes(mpz_class val, size_t byteCount) {
    vector<unsigned char> bytes(byteCount, 0);
    mpz_export(bytes.data(), nullptr, 1, 1, 1, 0, val.get_mpz_t());
    return bytes;
}

mpz_class lagrangeInterpolation(const ShareGroup& points, const mpz_class& x, const mpz_class& p) {
    mpz_class result = 0;
    for (size_t i = 0; i < points.size(); i++) {
        mpz_class xi = points[i].first;
        mpz_class yi = points[i].second;
        mpz_class li = 1;

        for (size_t j = 0; j < points.size(); j++) {
            if (i != j) {
                mpz_class xj = points[j].first;
                mpz_class numerator = (x - xj + p) % p;
                mpz_class denominator = (xi - xj + p) % p;
                mpz_class inv_denominator;
                mpz_invert(inv_denominator.get_mpz_t(), denominator.get_mpz_t(), p.get_mpz_t());
                li = (li * numerator * inv_denominator) % p;
            }
        }
        result = (result + yi * li) % p;
    }
    return result;
}

void createEncDecFiles(string& fp, string& encryptedFilePath, string& decryptedFilePath) {
    string filePathError = "Ошибка ввода. Такого файла не существует.";
    while (true) {
        try {
            getline(cin, fp);
            ifstream file(fp, ios::binary);
            if (!file)
                throw invalid_argument("invalid_file_path");
            break;
        } catch (const exception& e) {
            cout << "Ошибка (" << e.what() << "): " << filePathError << endl;
            cout << "Попробуйте еще раз: ";
        }
    }

    size_t slashPos = fp.find_last_of("/");
    string basePath = (slashPos != string::npos) ? fp.substr(0, slashPos + 1) : "";
    encryptedFilePath = basePath + "encrypted.txt";
    decryptedFilePath = basePath + "decrypted.txt";

    ofstream encryptedFile(encryptedFilePath, ios::binary);
    ofstream decryptedFile(decryptedFilePath, ios::binary);

    cout << "Файл будет зашифрован по пути: " << encryptedFilePath << endl;
    cout << "Файл будет расшифрован по пути: " << decryptedFilePath << endl;
}

void readShamirParameters(int& n, int& k, int& userK) {
    string inputError = "Введите 3 целых числа.";
    string invalidArguments = "n, k и userK не могут быть меньше 1. Также k и userK не могут быть больше n.";
    while (true) {
        try {
            cout << "Введите n, k и userK: ";
            cin >> n >> k >> userK;

            if (n < 1 || k < 1 || userK < 1 || k > n || userK > n)
                throw invalid_argument("invalid_args");

            break;
        } catch (const ios::failure& e) {
            userInputError(e, inputError);
        } catch (const exception& e) {
            userInputError(e, invalidArguments);
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void encrypt(string fp, string efp, int n, int k, ShareMatrix& es) {
    ifstream file(fp, ios::binary);
    if (!file) throw runtime_error("Ошибка открытия исходного файла.");

    ofstream out(efp, ios::binary);
    if (!out) throw runtime_error("Ошибка открытия файла шифрования.");

    gmp_randclass rng(gmp_randinit_mt);
    rng.seed(time(nullptr));

    const size_t blockSize = 4;
    vector<unsigned char> buffer(blockSize);

    while (file.read(reinterpret_cast<char*>(buffer.data()), blockSize) || file.gcount() > 0) {
        buffer.resize(file.gcount());
        mpz_class secret = bytesToMpz(buffer);

        ShareGroup shares = shamirSplit(secret, n, k, PRIME, rng);
        es.push_back(shares);

        for (const auto& [x, y] : shares) {
            vector<unsigned char> x_bytes = mpzToBytes(x, (mpz_sizeinbase(x.get_mpz_t(), 2) + 7) / 8);
            uint32_t x_len = x_bytes.size();
            out.write(reinterpret_cast<char*>(&x_len), sizeof(x_len));
            out.write(reinterpret_cast<char*>(x_bytes.data()), x_bytes.size());
            
            vector<unsigned char> y_bytes = mpzToBytes(y, (mpz_sizeinbase(y.get_mpz_t(), 2) + 7) / 8);
            uint32_t y_len = y_bytes.size();
            out.write(reinterpret_cast<char*>(&y_len), sizeof(y_len));
            out.write(reinterpret_cast<char*>(y_bytes.data()), y_bytes.size());
        }
        out.put('\n');
    }
}

void decrypt(string dfp, int userK, ShareMatrix es) {
    ofstream out(dfp, ios::binary);
    if (!out) throw runtime_error("Ошибка открытия файла для расшифровки.");

    for (const auto& group : es) {
        ShareGroup part(group.begin(), group.begin() + userK);
        mpz_class secret = lagrangeInterpolation(part, 0, PRIME);

        vector<unsigned char> bytes = mpzToBytes(secret, 4); // 4 байта
        out.write(reinterpret_cast<char*>(bytes.data()), bytes.size());
    }
}

void shamir() {
    string filePath, encryptedFilePath, decryptedFilePath;
    createEncDecFiles(filePath, encryptedFilePath, decryptedFilePath);

    int n = 0, k = 0, userK = 0;
    readShamirParameters(n, k, userK);

    ShareMatrix encryptionShares;
    encrypt(filePath, encryptedFilePath, n, k, encryptionShares);
    decrypt(decryptedFilePath, userK, encryptionShares);
    cout << endl;
}

