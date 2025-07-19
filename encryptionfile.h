//encryptionfile.h
#pragma once

#ifndef ENCRYPTIONFILE_H
#define ENCRYPTIONFILE_H

#include <string>

using namespace std;

extern string encryptionKey;

void setEncryptionKey(const string& key);

string encrypt(const string& plaintext);
string decrypt(const string& cipher);

#endif // ENCRYPTIONFILE_H
