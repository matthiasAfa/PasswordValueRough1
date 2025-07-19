#include "PasswordManager.h"
#include "encryptionfile.h"
#include "masterPassword.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main() {
    initializeMaster();  // ? unlock & rotate session key

    int choice = 0;
    string site, pw;
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
            displayMessage("Enter site name:");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, site);
            displayMessage("Enter password:");
            cin >> pw;
            savePassword(site, pw);
            break;
        case 2: loadPasswords(); break;
        case 3: deletePassword(); break;
        case 4: displayMessage("[Goodbye]"); break;
        default: displayMessage("[Error] Invalid choice.");
        }
    } while (choice != 4);

    return 0;
}