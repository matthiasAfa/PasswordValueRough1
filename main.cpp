#include <iostream>
#include <string>
#include <limits>
#include "masterPassword.h"
#include "encryptionfile.h"
#include "PasswordManager.h"
using namespace std;

int main() {
    cout << "Enter your username: ";
    string username;
    getline(cin, username);
    setUser(username);
    initializeMaster();

    while (true) {
        displayMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[Error] Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter site name: ";
            string site;
            getline(cin, site);
            cout << "Enter password: ";
            string pw;
            getline(cin, pw);
            savePassword(site, pw);
        }
        else if (choice == 2) {
            loadPasswords();
        }
        else if (choice == 3) {
            deletePassword();
        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "[Error] Invalid choice.\n";
        }
    }

    return 0;
}
