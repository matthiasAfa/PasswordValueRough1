// PasswordManager.cpp

#include "PasswordManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void displayMessage(const string& msg) {
    cout << msg << endl;
}

void displayMenu() {
    displayMessage("\nPassword Manager");
    displayMessage("1. Add Password");
    displayMessage("2. View Passwords");
    displayMessage("3. Delete Password");
    displayMessage("4. Exit");
    displayMessage("Enter your choice: ");
}

void savePassword(const string& site, const string& password) {
    ofstream file("passwords.txt", ios::app);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }
    file << site << ' ' << password << '\n';
    displayMessage("Password saved successfully.");
}

void loadPasswords() {
    ifstream file("passwords.txt");
    if (!file) {
        cerr << "[system] No passwords saved yet." << endl;
        return;
    }

    displayMessage("\nSaved Passwords:");
    string line;
    while (getline(file, line)) {
        auto pos = line.find_last_of(' ');
        if (pos == string::npos) continue;
        string site = line.substr(0, pos);
        string password = line.substr(pos + 1);
        cout << "Site: " << site
            << "  Password: " << password << endl;
    }
}

void deletePassword() {
    vector<pair<string, string>> entries;
    ifstream inFile("passwords.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        auto pos = line.find_last_of(' ');
        if (pos == string::npos) continue;
        entries.emplace_back(
            line.substr(0, pos),
            line.substr(pos + 1)
        );
    }
    inFile.close();

    if (entries.empty()) {
        displayMessage("[system] No passwords to delete.");
        return;
    }

    while (true) {
        displayMessage("\nSelect a password to delete:");
        for (size_t i = 0; i < entries.size(); ++i) {
            cout << i + 1 << ". Site: " << entries[i].first
                << "  Password: " << entries[i].second << endl;
        }
        int backVar = static_cast<int>(entries.size()) + 1;
        cout << backVar << ". Back to main menu" << endl;

        displayMessage("Enter the number of the entry to delete: ");
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            displayMessage("[system] Invalid input; please enter a number.");
            continue;
        }
        if (choice == backVar) {
            return;
        }
        if (choice < 1 || choice > static_cast<int>(entries.size())) {
            displayMessage("[system] Selection out of range; try again.");
            continue;
        }

        entries.erase(entries.begin() + (choice - 1));
        ofstream outFile("passwords.txt", ios::trunc);
        if (!outFile) {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }
        for (const auto& p : entries) {
            outFile << p.first << ' ' << p.second << '\n';
        }
        displayMessage("Password deleted successfully.");
        return;
    }
}
