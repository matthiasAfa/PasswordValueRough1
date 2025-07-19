#include "masterPassword.h"
#include "encryptionfile.h"
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

using namespace std;



// these get set by setUser(...)
string MASTER_FILE;
string KEY_FILE;
string VAULT_FILE;

// length of the session key
static const size_t DEFAULT_KEY_LENGTH = 32;

// helper: generate a printable-ASCII random key
static string randomKey(size_t len) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> d(33, 126);
    string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        s.push_back(char(d(gen)));
    }
    return s;
}

// Step 1: pick files based on username
void setUser(const string& username) {
    MASTER_FILE = username + "_master.txt";
    KEY_FILE = username + "_key.txt";
    VAULT_FILE = username + "_vault.txt";
}

void initializeMaster() {
    // --- Load or create master password ---
    string master;
    ifstream fin(MASTER_FILE);
    if (!fin) {
        // first time for this user
        cout << "Set master password for " << MASTER_FILE << ": ";
        getline(cin, master);
        ofstream fout(MASTER_FILE);
        fout << master;
    }
    else {
        getline(fin, master);
    }

    // --- Verify ---
    cout << "Enter master password: ";
    string attempt;
    getline(cin, attempt);
    if (attempt != master) {
        cerr << "Wrong master password\n";
        exit(1);
    }

    // --- Load old session key (or make a new one) ---
    string oldKey;
    ifstream kin(KEY_FILE);
    if (!kin) {
        oldKey = randomKey(DEFAULT_KEY_LENGTH);
    }
    else {
        getline(kin, oldKey);
    }

    // --- Decrypt that user’s vault into memory ---
    vector<pair<string, string>> vault;
    {
        ifstream vin(VAULT_FILE);
        setEncryptionKey(oldKey);
        string line;
        while (getline(vin, line)) {
            auto pos = line.find_last_of(' ');
            if (pos == string::npos) continue;
            string site = line.substr(0, pos);
            string enc = line.substr(pos + 1);
            vault.emplace_back(site, decrypt(enc));
        }
    }

    // --- Rotate to a new session key ---
    string newKey = randomKey(oldKey.size());
    setEncryptionKey(newKey);

    // --- Re-encrypt and save the vault ---
    {
        ofstream vout(VAULT_FILE, ios::trunc);
        for (auto& e : vault) {
            vout << e.first << ' ' << encrypt(e.second) << '\n';
        }
    }

    // --- Save new session key for next run ---
    ofstream kout(KEY_FILE, ios::trunc);
    kout << newKey;
}
