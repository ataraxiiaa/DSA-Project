/*
	Ali Abdullah
	23i-0842
	G
*/

#include <iostream>
using namespace std;

bool isAlphabet(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

class String {
	char* data;
	int length;

public:
	// provide definitions of following functions
	String(); // default constructor
	String(const char* str); // initializes the string with constant c-string
	String(const String&); // copy constructor to initialize the string from the existing
	//string
	String(int x); // initializes a string of predefined size
	char* getData() const; //returns the string inside the object
	// Binary Operators //
	//Sub - script Operators
	const char operator[](int i) const; // returns the character at index [x]
	//NOTE: in above [] operator functions if i=negative int value, print ith character
	//from end //of string e.g. in case of “LOOP” if i=-1 OR i=3, it should return ‘P’
		//similarly i = -4 OR i = 0, //return ‘L’
		// Arithmetic Operators
	String operator+=(const String& str); // appends a String at the end of the String
	String operator+=(const char& str); // appends a char at the end of the String
	String operator+=(const char* str); // appends a String at the end of the String

	String operator-=(const String& substr); //removes the substr from the String
	String operator-=(const char& str); //removes all occurrences of char from the String
	String operator-=(const char* str); //removes the str from the String
	
	// Assignment Operators
	String& operator=(const String&); // copies one String to another
	String& operator=(char*); // copies one c-string to another

	bool operator <(const String& other) const;
	bool operator >(const String& other) const;

	bool operator <=(const String& other) const;
	bool operator >=(const String& other) const;


	//Logical Operators
	bool operator==(const String&) const; // returns true if two Strings are equal
	bool operator==(const char*) const; // returns true if the c-string is equal to the
	//String
	// Unary Operators //
	//Boolean Not Operator
	bool operator!(); // returns true if the String is empty

	// Function-Call Operators
	////If something is not found then return -1

	int operator()(char) const; // returns the first index of the character being
	////searched
	int operator()(const String&) const; // returns the first index of the String
	////being searched
	int operator()(const char*) const; // returns the index of the c-string being
	//searched
	// Conversion Operator
	// 
	operator int() const; // returns the length of string
	~String() // destructor
	{
		delete[] data;
	}

	friend ostream& operator<<(ostream& output, const String& str);
	friend istream& operator>>(istream& input, String& str);

	int getSize()
	{
		return this->length;
	}
};

ostream& operator<<(ostream& output, const String& str) // outputs the string
{
	output << str.data;
	return output;
}
istream& operator>>(istream& input, String& str) // inputs the string
{
	char ch;
	while (input.get(ch) && (ch == ' ' || ch == '\n' || ch != '\0')) {}
	while (input.get(ch) && ch != '\0' && ch != '\n' && ch != ' ')
		str += ch;
	return input;
}

int Size(const char* str)
{
	int size = 0;
	while (str[size] != '\0')
		size++;
	return size;
}
int Size(String str)
{
	int size = 0;
	while (str[size] != '\0')
		size++;
	return size;
}
String::String()
{
	length = 0;
	data = new char[length+1];
	data[length] = '\0';
}
String::String(const char* str)
{
	int size = Size(str);
	this->length = size;
	data = new char[size + 1];
	for (int i = 0; str[i] != '\0'; ++i)
		data[i] = str[i];
	data[size] = '\0';
}
String::String(const String& copy)
{
	this->length = copy.length;
	data = new char[length + 1];
	for (int i = 0; copy.data[i] != '\0'; ++i)
		data[i] = copy.data[i];
	data[length] = '\0';
}
String::String(int x)
{
	this->length = x;
	data = new char[x + 1];
	for (int i = 0; i <= length; ++i)
	{
		data[i] = '\0';
	}
}
char* String::getData() const
{
	return data;
}
const char String :: operator[](int i)const
{
	if (i >= 0 && i < length)
	{
		return data[i];
	}
	else if (i < 0)
	{
		return data[length + i];
	}
	else
	{
		return '\0';
	}
}
String String::operator+=(const String& str)
{
	int strSize = Size(str);
	int TotalLength = length + strSize;
	char* newData = new char[TotalLength + 1];
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		newData[index++] = this->data[i];
	}
	for (int i = 0; i < strSize; i++)
	{
		newData[index++] = str.data[i];
	}
	newData[index] = '\0';
	delete[] data;
	data = newData;
	length = TotalLength;

	return *this;
}
String String :: operator+=(const char& str) // appends a char at the end of the String
{
	int combinedLength = length + 1;

	char* appendedData = new char[combinedLength + 1];

	int index = 0;
	for (int i = 0; i < length; i++) {
		appendedData[index++] = data[i];
	}
	appendedData[index++] = str;

	appendedData[index] = '\0';

	delete[] data;
	data = appendedData;
	length = combinedLength;

	return *this;
}
String String :: operator+=(const char* str)
{

	int strSize = Size(str);
	int TotalLength = length + strSize;
	char* newData = new char[TotalLength + 1];
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		newData[index++] = this->data[i];
	}
	for (int i = 0; i < strSize; i++)
	{
		newData[index++] = str[i];
	}
	newData[index] = '\0';
	delete[] data;
	data = newData;
	length = TotalLength;

	return *this;
}
String String :: operator-=(const String& substr)
{
	int strSize = Size(substr);
	int NewLength = length - strSize;

	char* AppendedData = new char[NewLength + 1];
	int index = 0;
	for (int i = 0; this->data[i] != '\0'; ++i)
	{
		bool Match = true;
		for (int j = 0; substr.data[j] != '\0'; ++j)
		{
			if (this->data[i + j] != substr.data[j])
			{
				Match = false;
				break;
			}
		}
		if (Match)
		{
			i += strSize - 1;
		}
		else
		{
			AppendedData[index++] = this->data[i];
		}
	}
	AppendedData[index] = '\0';
	delete[] data;
	this->data = AppendedData;
	this->length = NewLength;
	return *this;
}
String String::operator-=(const char& str)
{
	int NewLength = length - 1;
	String NewString;
	NewString.data = new char[NewLength + 1];
	int index = 0;
	for (int i = 0; data[i] != '\0'; ++i)
	{
		if (data[i] != str)
			NewString.data[index++] = data[i];
	}
	NewString.data[index] = '\0';

	delete[] data;
	data = NewString.data;
	this->length = NewLength;
	return *this;
}
String String ::operator-=(const char* str)
{
	int strSize = Size(str);
	int NewLength = length - strSize;

	char* AppendedData = new char[NewLength + 1];
	int index = 0;
	for (int i = 0; this->data[i] != '\0'; ++i)
	{
		bool Match = true;
		for (int j = 0; str[j] != '\0'; ++j)
		{
			if (this->data[i + j] != str[j])
			{
				Match = false;
				break;
			}
		}
		if (Match)
		{
			i += strSize - 1;
		}
		else
		{
			AppendedData[index++] = this->data[i];
		}
	}
	AppendedData[index] = '\0';
	delete[] data;
	this->data = AppendedData;
	this->length = NewLength;

	return *this;
}
int String :: operator()(char ch) const
{
	for (int i = 0; this->data[i] != '\0'; ++i)
	{
		if (this->data[i] == ch)
			return i;
	}
	return -1;
}
int String ::operator()(const String& str) const
{
	int strSize = Size(str);
	for (int i = 0; i < this->data[i] != '\0'; ++i)
	{
		bool Match = true;
		for (int j = 0; j < strSize; ++j)
		{
			if (this->data[i + j] != str.data[j])
			{
				Match = false;
				break;
			}
		}
		if (Match)
		{
			return i;
		}
	}
	return -1;
}
int String ::operator()(const char* str) const
{
	int strSize = Size(str);
	for (int i = 0; i < this->data[i] != '\0'; ++i)
	{
		bool Match = true;
		for (int j = 0; j < strSize; ++j)
		{
			if (this->data[i + j] != str[j])
			{
				Match = false;
				break;
			}
		}
		if (Match)
		{
			return i;
		}
	}
	return -1;
}
String :: operator int() const
{
	int i = 0;
	while (this->data[i] != '\0')
	{
		i++;
	}
	return i;
}
bool String :: operator!()
{
	if (this->length == 0 || this->data[0] == '\0')
		return true;
	return false;
}
bool String :: operator==(const String& str) const
{
	if (this->length != str.length)
		return false;
	for (int i = 0; data[i] != '\0'; ++i)
	{
		if (data[i] != str.data[i])
		{
			if (isAlphabet(data[i]) && isAlphabet(str.data[i]) && ((data[i] + 32 )== str.data[i] || (data[i] - 32 )== str.data[i]))
				continue;
			return false;
		}
	}
	return true;
}
bool String ::operator==(const char* str) const
{
	if (this->length != Size(str))
		return false;
	for (int i = 0; data[i] != '\0'; ++i)
	{
		if (data[i] != str[i])
		{
			if (isAlphabet(data[i]) && isAlphabet(str[i]) && ((data[i] + 32 )== str[i] || (data[i] - 32 )== str[i]))
				continue;
			return false;
		}
	}
	return true;
}
String& String :: operator=(const String& str)
{
	int strSize = Size(str);
	char* newData = new char[strSize + 1];
	for (int i = 0; str.data[i] != '\0'; ++i)
	{
		newData[i] = str.data[i];
	}
	newData[strSize] = '\0';
	delete[] data;
	this->data = newData;
	this->length = strSize;
	return *this;
}
String& String ::operator=(char* str)
{
	int strSize = Size(str);
	char* newData = new char[strSize + 1];
	for (int i = 0; str[i] != '\0'; ++i)
	{
		newData[i] = str[i];
	}
	newData[strSize] = '\0';
	delete[] data;
	this->data = newData;
	this->length = strSize;
	return *this;
}

void getline(istream& input, String& str, char delim='\n') {
	str = "";
	char ch;
	while (input.get(ch) && ch != delim)
	{
		str += ch;
	}
}

bool String::operator<(const String& other) const 
{
	int index = 0;
	while (this->data[index] != '\0' && other.data[index] != '\0') 
	{
		if (isAlphabet(data[index]) && isAlphabet(other.data[index]) && ((data[index] + 32 )== other.data[index] || (data[index] - 32 )== other.data[index]))
		{
			index++;
			continue;
		}
		if (this->data[index] < other.data[index]) 
		{
			return true;
		}
		else if (this->data[index] > other.data[index])
		{
			return false;
		}
		index++;
	}
	return this->length < other.length;
}

bool String::operator>(const String& other) const 
{
	int index = 0;
	while (this->data[index] != '\0' && other.data[index] != '\0')
	{
		if (isAlphabet(data[index]) && isAlphabet(other.data[index]) && ((data[index] + 32 )== other.data[index] || (data[index] - 32 )== other.data[index]))
		{
			index++;
			continue;
		}
		if (this->data[index] > other.data[index]) 
		{
			return true;
		}
		else if (this->data[index] < other.data[index])
		{
			return false;
		}
		index++;
	}
	return this->length > other.length;
}

inline bool String::operator<=(const String& other) const
{
	return ((*this < other) || (*this == other));
}

inline bool String::operator>=(const String& other) const
{
	return ((*this > other) || (*this == other));
}
