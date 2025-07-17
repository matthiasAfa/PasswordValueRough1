#pragma once

#include <string>

using namespace std;

void setEncryptionKey(const string& key);

string encrypt(const string& plaintext);
string decrypt(const string& cipher);


