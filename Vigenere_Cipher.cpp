
#include <iostream>
#include <cstring>
using namespace std;
string removeSpaces(string plain)
{
	int size = plain.length();
	string result = "";
	for (int i = 0; i < size; i++)
	{
		if (plain[i] != ' ')
		{
			result += plain[i];
		}
	}
	return result;
}
string PrepareKey(string str, string key)
{
	int size = 0;
	while (size < str.length())
	{
		key.append(key);
		size = key.length();
	}

	int diff = size - str.length();
	for (int i = 0; i < diff; i++)
	{
		key.pop_back();
	}
	return key;
}
string EncVigenere(string str, string key)
{
	string cipher_text;
	int size = str.length();
	char check = 'A';
	for (int i = 0; i < size; i++)
	{
		if (islower(str[i]))
		{
			check = 'a';
		}
		else
		{
			check = 'A';
		}
		char x = (((str[i] - check) + (key[i] - check)) % 26) + check;

		cipher_text.push_back(x);
	}
	return cipher_text;
}
string DecVigenere(string cipher, string key)
{
	string original;
	char check = 'A';
	int size = cipher.length();
	for (int i = 0; i < size; i++)
	{
		if (islower(cipher[i]))
		{
			check = 'a';
		}
		else
		{
			check = 'A';
		}
		char x = (((cipher[i] - check) - (key[i] - check) + 26) % 26) + check;

		original.push_back(x);
	}
	return original;
}

int main()
{
	cout << "\nVigenere Cipher with Keyword \"UMER\"" << endl;
	string str = "PAKISTAN";
	string keyword = "UMER";
	str = removeSpaces(str);
	string key = PrepareKey(str, keyword);
	string cipher_text = EncVigenere(str, key);

	cout << "Ciphertext : "
		 << cipher_text << endl;

	cout << "Decrypted Text : "
		 << DecVigenere(cipher_text, key) << endl<<endl;
	return 0;
}
