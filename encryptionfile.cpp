// encryptionfile.cpp
#include "encryptionfile.h"
#include <string>
#include <random>

using namespace std;

// Generate a random printable?ASCII key
static string randomizedKey(size_t length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);

    string key;
    key.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        key += alphanum[dist(gen)];
    }
    return key;
}

// Global session key (32 chars) randomized at load time
static constexpr size_t DEFAULT_KEY_LENGTH = 32;
string encryptionKey = randomizedKey(DEFAULT_KEY_LENGTH);

void setEncryptionKey(const string& key) {
    encryptionKey = key;
}

string encrypt(const string& plaintext) {
    string cipher;
    cipher.reserve(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); ++i) {
        unsigned char p = static_cast<unsigned char>(plaintext[i]);
        unsigned char k = static_cast<unsigned char>(
            encryptionKey[i % encryptionKey.size()]
            );
        cipher.push_back(static_cast<char>((p + k) % 256));
    }
    return cipher;
}

string decrypt(const string& cipher) {
    string plaintext;
    plaintext.reserve(cipher.size());
    for (size_t i = 0; i < cipher.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(cipher[i]);
        unsigned char k = static_cast<unsigned char>(
            encryptionKey[i % encryptionKey.size()]
            );
        plaintext.push_back(
            static_cast<char>((c + 256 - k) % 256)
        );
    }
    return plaintext;
}
