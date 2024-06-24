#include <iostream>
using namespace std;
int mod5(int a) { return (a % 5); }
string DecPFC(string, string *);
string EncPFC(string, string, string *);
string encrypt(string, string *);
void search(string *, char, char, int[]);
string removeSpaces(string);
string tolower(string);
string prepare(string);
string delchar(string, char);

int main()
{
    string keyT[5];

    string str = "BALLOON", key = "MONARCHY";

    string cipher = EncPFC(str, key, keyT);
    cout << "\nPlayfair Cipher with Keyword \"MONARCHY\"" << endl;
    cout << "Plain Text: " << str << endl;
    cout << "Cipher text: " << cipher << endl;
    string original = DecPFC(cipher, keyT);
    original = delchar(original, 'z');
    cout << "Decrypted text: " << original << endl<<endl;

    return 0;
}
string delchar(string str, char c)
{
    string result = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != c)
        {
            result += str[i];
        }
    }
    return result;
}
string prepare(string str)
{
    for (int i = 0; i < str.length(); i += 2)
    {
        if (str[i] == str[i + 1])
        {
            str.insert(i + 1, "z");
        }
    }
    if (str.length() % 2 != 0)
    {
        str.push_back('z');
    }

    return str;
}

string tolower(string plain)
{
    int size = plain.length();
    string lower = "";
    for (int i = 0; i < size; i++)
    {
        if (plain[i] >= 65 && plain[i] <= 92)
        {
            lower.push_back(plain[i] + 32);
        }
    }
    return lower;
}

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
void search(string *keyT, char a, char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {

            if (keyT[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

void generateKeyTable(string key, string *keyT)
{
    int check = 97;
    int i, j, k;
    int size = key.length();
    int table[26] = {0};
    for (i = 0; i < size; i++)
    {
        if (key[i] != 'j')
            table[key[i] - check] = 2;
    }

    table['j' - check] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < size; k++)
    {
        if (table[key[k] - check] == 2)
        {
            table[key[k] - check] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++)
    {
        if (table[k] == 0)
        {
            keyT[i][j] = (char)(k + check);
            j++;
            if (j == 5)
            {
                i++;
                j = 0;
            }
        }
    }
}
string encrypt(string str, string *keyT)
{
    int i, a[4];
    int size = str.length();
    string cipher = "";
    for (i = 0; i < size; i += 2)
    {

        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2])
        {
            cipher.push_back(keyT[a[0]][mod5(a[1] + 1)]);
            cipher.push_back(keyT[a[0]][mod5(a[3] + 1)]);
        }
        else if (a[1] == a[3])
        {
            cipher.push_back(keyT[mod5(a[0] + 1)][a[1]]);
            cipher.push_back(keyT[mod5(a[2] + 1)][a[1]]);
        }
        else
        {
            cipher.push_back(keyT[a[0]][a[3]]);
            cipher.push_back(keyT[a[2]][a[1]]);
        }
    }
    return cipher;
}
string EncPFC(string str, string key, string *keyT)
{

    key = removeSpaces(key);
    key = tolower(key);

    str = tolower(str);
    str = removeSpaces(str);

    str = prepare(str);
    generateKeyTable(key, keyT);
    return encrypt(str, keyT);
}
string DecPFC(string cipher, string *keyT)
{
    int i, a[4];
    int size = cipher.length();
    string original = "";
    for (i = 0; i < size; i += 2)
    {

        search(keyT, cipher[i], cipher[i + 1], a);

        if (a[0] == a[2])
        {
            original.push_back(keyT[a[0]][mod5(a[1] - 1)]);
            original.push_back(keyT[a[0]][mod5(a[3] - 1)]);
        }
        else if (a[1] == a[3])
        {
            original.push_back(keyT[mod5(a[0] - 1)][a[1]]);
            original.push_back(keyT[mod5(a[2] - 1)][a[1]]);
        }
        else
        {
            original.push_back(keyT[a[0]][a[3]]);
            original.push_back(keyT[a[2]][a[1]]);
        }
    }
    return original;
}
