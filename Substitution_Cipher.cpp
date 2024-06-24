/*
 *      CY-A Umer Farooq
 *      22I-0518
 *      Networks and CyberSecurity-I
 *      Assignment-1
 */
#include <iostream>
#include <cstring>
using namespace std;
string subCipherDec(string cipher, int *key);
string subCipherEnc(string input, int *key);
int main()
{
    srand(time(0));
    string input = "balloon";
    int len = input.length();
    int *key = new int[26];

    for (int i = 0; i < 26; i++)
        key[i] = i;

    for (int i = 0; i < 26; i++) // bogosort zindabad
        swap(key[i], key[rand() % 26]);

    cout << "\nSubtitution Cipher with Randomized Dictionary" << endl;
    cout << "Input: " << input << endl;
    string cipher = subCipherEnc(input, key);
    cout << "Cipher: " << cipher << endl;
    string decrypt = subCipherDec(cipher, key);
    cout << "Decrypt: " << decrypt << endl
         << endl;
}
string subCipherEnc(string input, int *key)
{
    int len = input.length();
    int minus;
    islower(input[0]) ? minus = 97 : minus = 65;
    string cipher = "";

    for (int i = 0; i < len; i++)
    {
        char a = key[input[i] - minus] + minus;
        cipher.push_back(a);
    }
    return cipher;
}
string subCipherDec(string cipher, int *key)
{
    int len = cipher.length();
    string original = "";
    int minus;
    islower(cipher[0]) ? minus = 97 : minus = 65;

    for (int i = 0; i < len; i++)
    {
        int idx = cipher[i] - minus;
        int j;
        for (j = 0; j < 26; j++)
        {
            if (key[j] == idx)
                break;
        }
        char a = j + minus;
        original.push_back(a);
    }
    return original;
}
