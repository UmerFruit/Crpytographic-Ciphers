/*
 *      CY-A Umer Farooq
 *      22I-0518
 *      Networks and CyberSecurity-I
 *      Assignment-1
 */
#include <iostream>
#include <cstring>
using namespace std;
string ceaserCipherDec(string cipher, int key = 3);
void Cracker(string cipher, int key);
string ceaserCipherEnc(string input, int key = 3);
int main()
{
    string input = "INFORMATIONSECURITY";
    string cipher = ceaserCipherEnc(input);
    cout << "\nCeaser Cipher with Key = 3" << endl;
    cout << "Plain text: " << input << endl;
    cout << "Cipher text: " << cipher << endl;
    string decrypt = ceaserCipherDec(cipher);
    cout << "Decrypted text: " << decrypt << endl
         << endl;

    
}
void Cracker(string cipher, int key)
{
    // All possible Combinations Tester Code
    cout << "\nCeaser Cipher Cracker (solution at Key = 3)" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << i + 1;
        if(i<9)cout<<" ";
        cout<< ". " << ceaserCipherDec(cipher, i);
        if (i % 2)
            cout << endl;
        else
            cout << "\t";
    }
}
string ceaserCipherEnc(string input, int key)
{
    int len = input.length();
    string cipher = "";
    int minus;
    islower(input[0]) ? minus = 97 : minus = 65;
    for (int i = 0; i < len; i++)
    {
        char a = ((static_cast<int>(input[i] - minus) + key) % 26) + minus;
        cipher.push_back(a);
    }
    return cipher;
}
string ceaserCipherDec(string cipher, int key)
{
    int len = cipher.length();
    string original = "";
    int minus;
    islower(cipher[0]) ? minus = 97 : minus = 65;

    for (int i = 0; i < len; i++)
    {
        char a = ((static_cast<int>(cipher[i] - minus) - key + 26) % 26) + minus;
        original.push_back(a);
    }
    return original;
}
