//encryptionfile.cpp 

#include "encryptionfile.h"
#include <string>

using namespace std;

string encryptionKey;

void setEncryptionKey(const string& key) {
	encryptionKey = key;
}

string encrypt(const string& plaintext) { // relook and make better
	string cipher;
	cipher.reserve(plaintext.size());
	for (int i = 0; i < plaintext.size(); ++i) {
		unsigned char p = static_cast<unsigned char>(plaintext[i]);
		unsigned char k = static_cast<unsigned char>(encryptionKey[i % encryptionKey.size()]);
		cipher.push_back(static_cast<char>((p + k) % 256));  
	}
	return cipher;
} 

string decrypt(const string& cipher) { // relook and make better
	string plaintext;
	plaintext.reserve(cipher.size());
	for (int i = 0; i < cipher.size(); ++i) {
		unsigned char c = static_cast<unsigned char>(cipher[i]);
		unsigned char k = static_cast<unsigned char>(encryptionKey[i % encryptionKey.size()]);
		plaintext.push_back(static_cast<char>((c - k + 256) % 256)); // ensure non-negative
	}
	return plaintext;
}