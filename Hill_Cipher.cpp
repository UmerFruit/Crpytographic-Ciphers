#include "Matrix.h" //my own implementation of a matrix class
string encrypt(string, Matrix &, int);
string decrypt(string, Matrix &, int);
string delchar(string str, char c);
string prepare(string);
int main()
{
    Matrix key;
    int check;
    key.Setelement(7, 0, 0);
    key.Setelement(8, 0, 1);
    key.Setelement(19, 1, 0);
    key.Setelement(3, 1, 1);
    Matrix inverse = key.inverse(); // calculate in mod 26
    string plain_text = "INFORMATIONSECURTIY";

    islower(plain_text[0]) ? check = 97 : check = 65;
    string cipher_text = encrypt(plain_text, key, check);
    cout << "\nHill Cipher" << endl;
    cout << "Plaintext text is: " << plain_text << endl;
    cout << "Key Matrix is: " << endl;
    cout << key;
    cout << "Ciphertext text is: " << cipher_text << endl;
    cout << "Inverse of Key Matrix in mod 26 is: " << endl;
    cout << inverse;

    cout << "Decrypted text is: " << delchar(decrypt(cipher_text, inverse, check), check + 25) << endl<<endl;
    return 0;
}
string prepare(string str)
{
    char c;
    islower(str[0]) ? c = 'z' : c = 'Z';

    if (str.length() % 2 != 0)
    {
        str.push_back(c);
    }
    return str;
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
string encrypt(string str, Matrix &Key, int check)
{
    string result = "";
    str = prepare(str);
    Matrix encVector(2, 1);
    for (int i = 0; i < str.length(); i += 2)
    {
        encVector.Setelement(str[i] - check, 0, 0);
        encVector.Setelement(str[i + 1] - check, 1, 0);
        Matrix prod = Key * encVector;

        prod = prod % 26;
        result.push_back(static_cast<char>(prod.getElement(0, 0) + check));
        result.push_back(static_cast<char>(prod.getElement(1, 0)) + check);
    }
    return result;
}
string decrypt(string cipher, Matrix &inverse, int check)
{
    string result = "";
    Matrix encVector(2, 1);
    for (int i = 0; i < cipher.length(); i += 2)
    {
        encVector.Setelement(cipher[i] - check, 0, 0);
        encVector.Setelement(cipher[i + 1] - check, 1, 0);

        Matrix prod = inverse * encVector;

        prod = prod % 26;
        result.push_back(static_cast<char>(prod.getElement(0, 0) + check));
        result.push_back(static_cast<char>(prod.getElement(1, 0)) + check);
    }
    return result;
}