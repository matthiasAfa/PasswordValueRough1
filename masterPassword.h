#pragma once

#ifndef MASTERPASSWORD_H
#define MASTERPASSWORD_H

#include <string>
using namespace std;

extern string MASTER_FILE;
extern string KEY_FILE;
extern string VAULT_FILE;

void setUser(const string& username);
void initializeMaster();

#endif // MASTERPASSWORD_H
