#include "PasswordManager.h"
#include "encryptionfile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main() {
    int choice = 0;
    string site;
    string password;

    string encryptionKey;
    cout << "Enter encryption key: ";
    getline(cin, encryptionKey);
    setEncryptionKey(encryptionKey);

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            displayMessage("Enter site name (multiple words allowed): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, site);
            displayMessage("Enter password: ");
            cin >> password;
            savePassword(site, password);
            break;
        case 2:
            loadPasswords();
            break;
        case 3:
            deletePassword();
            break;
        case 4:
            displayMessage("[system] Exiting...");
            break;
        default:
            displayMessage("[system] Invalid choice. Please try again.");
            break;
        }

    } while (choice != 4);

    return 0;
}