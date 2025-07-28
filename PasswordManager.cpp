#include "PasswordManager.h"
#include "masterPassword.h"
#include "encryptionfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void displayMessage(const string& msg) {
    cout << msg << "\n";
}
void displayMenu() {
    displayMessage("\nPassword Manager");
    displayMessage("1. Add Password");
    displayMessage("2. View Passwords");
    displayMessage("3. Delete Password");
    displayMessage("4. Switch User");
    displayMessage("5. Exit");
	cout << "Choose your choice: ";
}

void savePassword(const string& site, const string& password) {
    ofstream fout(VAULT_FILE, ios::app);
    if (!fout) { cerr << "Cannot open vault\n"; return; }
    fout << site << ' ' << encrypt(password) << '\n';
    displayMessage("Saved.");
}

void loadPasswords() {
    ifstream fin(VAULT_FILE);
    if (!fin) { displayMessage("No entries."); return; }
    displayMessage("\nYour entries:");
    string line;
    setEncryptionKey(encryptionKey); // already set
    while (getline(fin, line)) {
        auto pos = line.find_last_of(' ');
        if (pos == string::npos) continue;
        cout << "Site: " << line.substr(0, pos)
            << "  Pass: " << decrypt(line.substr(pos + 1)) << "\n";
    }
}

void deletePassword() {
    vector<pair<string, string>> entries;
    ifstream fin(VAULT_FILE);
    setEncryptionKey(encryptionKey);
    string line;
    while (getline(fin, line)) {
        auto pos = line.find_last_of(' ');
        if (pos == string::npos) continue;
        entries.emplace_back(
            line.substr(0, pos),
            line.substr(pos + 1)
        );
    }
    if (entries.empty()) { displayMessage("Nothing to delete."); return; }

    while (true) {
        displayMessage("Select number to delete:");
        for (size_t i = 0; i < entries.size(); ++i) {
            cout << i + 1 << ". " << entries[i].first
                << " (" << decrypt(entries[i].second) << ")\n";
        }
        size_t back = entries.size() + 1;
        cout << back << ". Back\nChoice: ";
        int c; cin >> c;
        if (!cin.good() || c<1 || c>back) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            displayMessage("Invalid.");
            continue;
        }
        if (c == back) return;
        entries.erase(entries.begin() + c - 1);
        ofstream fout(VAULT_FILE, ios::trunc);
        for (auto& e : entries)
            fout << e.first << ' ' << e.second << '\n';
        displayMessage("Deleted.");
        return;
    }
}
