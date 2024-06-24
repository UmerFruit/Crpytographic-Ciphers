#include <iostream>
#include <cstring>
using namespace std;
class Node
{
public:
	string str;
	int size;
	int value;
	Node(string text = "", int val = 0)
	{
		size = text.length();
		str = text;
		value = val;
	}
	void setval(int val)
	{
		value = val;
	}
	Node &operator=(Node &n)
	{
		str = n.str;
		size = n.size;
		value = n.value;
		return *this;
	}
	string prepare(string str, int keylength)
	{
		int strlen = str.length();
		if (strlen % keylength == 0)
		{
			return str;
		}
		else if (strlen > keylength * keylength)
		{
			cout << "cannot fit" << endl;
			return "";
		}
		else
		{
			char c;
			(islower(str[0])) ? c = 'z' : c = 'Z';
			int diff = (keylength * keylength) - strlen;
			for (int i = 0; i < diff; i++)
			{
				str.push_back(c);
			}
		}
		return str;
	}
	string setstr(string text, int keylength)
	{
		size = keylength;
		text = prepare(text, keylength);
		if (text == "")
		{
			cout << "Encryption not possible." << endl;
			return text;
		}
		int i;
		for (i = 0; text[i] != '\0' && i < size; i++)
		{
			str.push_back(text[i]);
		}
		for (; i > 0; i--)
		{
			text.erase(0, 1);
		}

		if (!text.empty())
			return text;
		else
			return "";
	}
	void print()
	{
		cout << "Str = " << str << endl;
		cout << "Value = " << value << endl;
	}
};
void sort(Node *arr, int keylength)
{
	int size = keylength;
	for (int i = 1; i < size; i++)
	{
		Node key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j].value > key.value)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
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
void showGrid(Node *arr, int keysize)
{
	for (int i = 0; i < keysize; i++)
		cout << arr[i].value - 97 << " ";
	cout << endl;
	for (int i = 0; i < keysize; i++)
	{
		for (int j = 0; j < keysize; j++)
		{
			cout << arr[i].str[j] << " ";
		}
		cout << endl;
	}
}
Node *transpose(Node *&arr, int size)
{
	Node *tarr = new Node[size];
	for (int i = 0; i < size; ++i)
	{
		tarr[i].value = arr[i].value;
		for (int j = 0; j < size; ++j)
		{
			tarr[j].str.push_back(arr[i].str[j]);
		}
	}
	return tarr;
}
string Encrpyt(Node *&arr, string Key, string plaintext)
{
	string result = "";
	int size = Key.length();
	arr = new Node[size];
	for (int i = 0; i < size; i++)
	{
		plaintext = arr[i].setstr(plaintext, size);
	}
	arr = transpose(arr, size);
	for (int i = 0; i < size; i++)
	{
		arr[i].value = Key[i];
	}
	Node *temp = new Node[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = arr[i];
	}

	sort(temp, size);
	for (int i = 0; i < size; i++)
	{
		result.append(temp[i].str);
	}
	return result;
}
string Decrpyt(Node *&arr, string Key, string cipher)
{
	string result = "";
	int size = Key.length();
	arr = transpose(arr, size);
	for (int i = 0; i < size; i++)
	{
		result.append(arr[i].str);
	}
	return result;
}
int main()
{
	string Key = "SPIDERMAN";
	string plaintext = "PETERPARKER";
	int Keysize = Key.length();
	Node *arr;
	int check;
	islower(plaintext[0]) ? check = 97 : check = 65;
	string cipher = Encrpyt(arr, Key, plaintext);
	string cipher2 = delchar(cipher, check + 25);
	string decr = Decrpyt(arr, Key, cipher);
	string decr2 = delchar(decr, check + 25);

	cout << "\nColumnar Transposition Cipher with Keyword \"SPIDERMAN\"" << endl;
	cout << "Plain text: " << plaintext << endl;
	cout << "Ciphertext: " << cipher2 << endl;
	cout << "Decrypted Text: " << decr2 << endl<<endl;

	return 0;
}
