#include <iostream>
#include <fstream>
#include "string.h"
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;
//Ahigad genish
//Ahigad.genish@gmail.com
char intToChar(int s) {
	switch (s) {
		case 1: 
			return '1';
		case 2: 
			return '2';
		case 3: 
			return '3';
		case 4: 
			return '4';
		case 5: 
			return '5';
		case 6: 
			return '6';
		case 7: 
			return '7';
		case 8:
			return '8';
		case 9: 
			return '9';
		case 0: 
			return '0';
	}
	return -1;
}

// generate key;
string genOtp(int len) {

	string key = "";
	for (int i = 0;i < len ;i++) {
		key += intToChar(rand() % 2);
	}
	return key;

}
// encryption string by xor;
pair<string,string> encOtp(string key, string path) {

	int len = key.length();
	pair<string, string> ret;
	ofstream file;
	string p;
	file.open(path);
	cout << "Insert your message with length of " << len << endl;
	cin >> p;
	if (file.is_open())
	{
		for (int i = 0;i < p.length();i++) {
			p[i] = p[i] ^ key[i];
		}
	}

	file << p;
	file.close();
	ret = { key , path };
	return ret;

}
// decryption key by xor;
string decOtp(string key, string path) {
	int len = key.length();
	ifstream file;
	string p;
	file.open(path);
	if (file.is_open())
	{
		file >> p;
		cout << "The cipher text of your message is: " << p << endl;
		for (int i = 0;i < p.length();i++) {
			p[i] = p[i] ^ key[i];
		}
	}
	
	file.close();
	return p;

}
// encryption string by shift;
string encVigenere(string key, string path) {

	unordered_map<char, int> dict;
	unordered_map<int, char> mp;
	// get file
	ofstream file;
	string p;
	file.open(path);
	cout << "Insert your message" << endl;
	cin >> p;
	
	for (int i = 0;i < 26;i++) {
		dict['a' + i] = i;
		mp[i] = 'a' + i;
	}
	if (file.is_open())
	{
		
		int j = 0;
		for (int i = 0;i < p.length();i++) {
			int n = key.length();
			int numP = dict[p[i]];
			int numK = dict[key[j]];
			p[i] = mp[(numP + numK) % 26];
			j += 1;
			if (j == n) {
				j = 0;
			}
		}
	}
	file << p;
	file.close();
	return path;
}
// decryption string by reverse shift;
string decVigenere(string key, string &path) {

	// define hashMap for any char;
	unordered_map<char, int> dict;
	unordered_map<int, char> mp;
	// get file
	ifstream file;
	file.open(path);

	string p = "";
	for (int i = 0;i < 26;i++) {
		dict['a' + i] = i;
		mp[i] = 'a' + i;
	}
	if (file.is_open())
	{
		file >> p;
		cout << "The cipher text is :" <<  p << endl;
		int j = 0;
		for (int i = 0;i < p.length();i++) {
			int n = key.length();
			int numP = dict[p[i]];
			int numK = dict[key[j]];
			p[i] = mp[(numP - numK + 26) % 26];
			j += 1;
			if (j == n) {
				j = 0;
			}
		}
	}
	file.close();
	return p;

}
// examples :
int main() {
	 // vigenere :
	string path = "C:\\Users\\ahiga\\Documents\\ex1_vigenere_ciphertext.txt";
	string key = "crypto";
	//string enrcypred = encVigenere(key,path);
	cout << "The encrypted message was : " << decVigenere(key, path) << endl;

	// One Time Pad:
	int len = 0;
	cout << "Insert the length of your message " << endl;
	cin >> len;
	string key2 = genOtp(len);
	string path2 = "C:\\Users\\ahiga\\Documents\\ex_otp_ciohertext.txt";
	pair<string,string>  enc = encOtp(key2, path2);
	string dec = decOtp(enc.first, enc.second);
	cout << "your encrypted message was: " << dec << endl;
	return 0;
}
