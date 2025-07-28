#include <iostream>
#include <string>
#include <limits>
#include "masterPassword.h"
#include "encryptionfile.h"
#include "PasswordManager.h"
using namespace std;

int main() {


	bool running = true;

		while (running) {
			cout << "Enter your username: ";
			string username;
			getline(cin, username);
			setUser(username);
			initializeMaster();

			bool userActive = true;
			while (userActive) {
				displayMenu();
				int choice;
				if (!(cin >> choice)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "[Error] Please enter a number.\n";
					continue;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                case 1: {
                    cout << "Enter site name: ";
                    string site;
                    getline(cin, site);
                    cout << "Enter password: ";
                    string pw;
                    getline(cin, pw);
                    savePassword(site, pw);
                    break;
                }
                case 2:
                    loadPasswords();
                    break;
                case 3:
                    deletePassword();
                    break;
                case 4:
                    userActive = false;  // exit user loop
                    break;
                case 5:
                    running = false;     // exit main loop
                    userActive = false;  // also exit user loop
                    break;
                default:
                    cout << "[Error] Invalid choice.\n";
                    break;
                }
			}
		}

	return 0;
}