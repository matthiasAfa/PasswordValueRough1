#pragma once
// passwordManager.h

#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

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

#endif // PASSWORDMANAGER_H