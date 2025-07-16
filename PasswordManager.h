#pragma once
// passwordManager.h

#include <string>
#include <vector>

using namespace std;

//output helpers
void displayMessage(const string& msg);
void displayMenu();

//core functions
void savePassword(const string& site, const string& password);
void loadPasswords();
void deletePassword();

