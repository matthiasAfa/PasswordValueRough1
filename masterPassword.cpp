// masterPassword.cpp

#include "masterPassword.h"
#include "encryptionfile.h"
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;

const char* MASTER_FILE = "master.txt";
const char* KEY_FILE = "key.txt";
const size_t DEFAULT_KEY_LENGTH = 32;

// Generate a random printable-ASCII string
static string randomKey(size_t len) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(33, 126);
    string key;
    key.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        key += char(dist(gen));
    }
    return key;
}

void initializeMaster() {
    // 1) Load or create master password
    string master;
    ifstream mfin(MASTER_FILE);
    if (!mfin) {
        cout << "Set master password: ";
        getline(cin, master);
        ofstream mout(MASTER_FILE);
        mout << master;
    }
    else {
        getline(mfin, master);
    }

    // 2) Verify master password
    cout << "Enter master password: ";
    string guess;
    getline(cin, guess);
    if (guess != master) {
        cerr << "Wrong master password\n";
        exit(1);
    }

    // 3) Load old key (or generate new)
    string oldKey;
    ifstream kin(KEY_FILE);
    if (!kin) {
        oldKey = randomKey(DEFAULT_KEY_LENGTH);
    }
    else {
        getline(kin, oldKey);
    }

    // 4) Decrypt all entries under oldKey
    vector<pair<string, string>> vault;
    ifstream pin("passwords.txt");
    setEncryptionKey(oldKey);
    string line;
    while (getline(pin, line)) {
        auto pos = line.find_last_of(' ');
        if (pos == string::npos) continue;
        string site = line.substr(0, pos);
        string enc = line.substr(pos + 1);
        vault.emplace_back(site, decrypt(enc));
    }

    // 5) Rotate to a new session key
    string newKey = randomKey(oldKey.size());
    setEncryptionKey(newKey);

    // 6) Re-encrypt vault under newKey
    ofstream pout("passwords.txt", ios::trunc);
    for (auto& e : vault) {
        pout << e.first << ' ' << encrypt(e.second) << '\n';
    }

    // 7) Save newKey for next run
    ofstream kout(KEY_FILE, ios::trunc);
    kout << newKey;
}
