///*
//	Fahad Bin Faisal, 23i-0614, Section G
//	Ali Abdullah, 23i-0842, Section G
//	Ahmar Ali, 23p-0686, Section G
//*/
//
//
//#include <iostream>
//#include<filesystem>
//#include<openssl/sha.h>
//#include <sstream>	//for hashing
//#include<fstream>
//#include<cmath>
//
//using namespace std;
//using namespace filesystem;
//
//
////class for templatized STACK
//template <class T>
//class Stack
//{
//
//	//linked list based STACK
//	class Node
//	{
//	public:
//		T& data;
//		Node* next;
//
//		Node(T& data) :data(data)
//		{
//			next = nullptr;
//		}
//		Node()
//		{
//			next = nullptr;
//		}
//	};
//
//	Node* top;//store top element
//
//public:
//
//	//pretty self explainatory functions
//	Stack()
//	{
//		top = nullptr;
//	}
//
//	//return true if empty stack
//	bool isEmpty()
//	{
//		return top == nullptr;
//	}
//
//	//peek top element
//	T& Top()
//	{
//		if (isEmpty())
//		{
//			std::cerr << "Error: Stack is empty" << endl;
//			return T();
//		}
//		return this->top->data;
//	}
//
//	//push new element onto stack
//	void push(T& val)
//	{
//		Node<T>* temp = new Node<T>(val);
//		temp->next = top;
//		top = temp;
//	}
//
//	//pop top elemetn
//	T& pop()
//	{
//		if (isEmpty())
//		{
//			std::cerr << "Error: Stack is empty" << endl;
//			return T();
//		}
//
//		T& temp = top->data;
//		Node<T>* deletingNode = top;
//		top = top->next;
//		delete deletingNode;
//		return temp;
//	}
//
//	//destructor
//	~Stack()
//	{
//		while (!isEmpty())
//		{
//			pop();
//		}
//	}
//};
//template <typename Type>class Vector  // Vector Template that would take type 
//{
//	Type* ptr; // Pointer to store the type
//	int currSize, maxSize; // to track if to expand the vector array or not
//
//public:
//	Vector() {
//		ptr = new Type[5];
//		currSize = 0;
//		maxSize = 5;
//	}
//
//	//copy constructor
//	Vector(const Vector& copy)
//	{
//		this->maxSize = copy.maxSize;
//		this->currSize = copy.currSize;
//		this->ptr = new Type[maxSize];
//		for (int a = 0; a < currSize; a++)
//		{
//			this->ptr[a] = copy.ptr[a];
//		}
//	}
//
//	//overload assignment
//	Vector& operator=(const Vector& copy)
//	{
//		if (this->ptr)
//			delete[] this->ptr;
//		this->maxSize = copy.maxSize;
//		this->currSize = copy.currSize;
//		this->ptr = new Type[maxSize];
//		for (int a = 0; a < currSize; a++)
//		{
//			this->ptr[a] = copy.ptr[a];
//		}
//		return *this;
//	}
//	~Vector() { delete[] ptr; } // Destructor
//
//	// Adding values to the array
//	void push_back(Type value) {
//		if (currSize == maxSize) {
//			Type* temp = new Type[2 * maxSize];
//			for (int i = 0; i < maxSize; ++i)
//				temp[i] = ptr[i];
//			delete[] ptr;
//			maxSize = maxSize << 1;
//			ptr = temp;
//		}
//		ptr[currSize] = value;
//		++currSize;
//	}
//
//	//return current size of array
//	int getCurr() { return currSize; }
//
//	// Accessing address the pointer is pointing to
//	Type& operator[](int index)
//	{
//		if (index < currSize && index >= 0)
//			return ptr[index];
//		else
//			throw runtime_error("Accessing invalid index.");
//	}  
//
//	//insert according to sorting of value
//	void insertSorted(Type val) {
//		bool inBetween = false;
//		int index = 0;
//		for (int i = 0; i < currSize; i++) {
//			if (ptr[i] > val) {
//				inBetween = true;
//				index = i;
//				break;
//			}
//		}
//		if (inBetween) inserAt(val, index);
//		else push_back(val);
//	}
//
//	//insert at specific index
//	void inserAt(const Type& data, int index) {
//		if ((index > (currSize + 1)) || (index < 0)) {
//			return;
//		}
//		if (currSize == maxSize - 1) {
//			Type* temp = new Type[2 * maxSize];
//			for (int i = 0; i < currSize; ++i) {
//				temp[i] = ptr[i];
//			}
//			delete[] ptr;
//			ptr = temp;
//			maxSize *= 2;
//		}
//		currSize++;
//		int i;
//		for (i = currSize; i > index; i--) {
//			ptr[i] = ptr[i - 1];
//		}
//		ptr[i] = data;
//	}
//
//	//returns index of value to search
//	int search(const Type& value) const {
//		for (int i = 0; i < currSize; ++i) {
//			if (this->ptr[i] == value) {
//				return i;
//			}
//		}
//		return -1;
//	}
//
//	//remove at specific index
//	void removeAt(int index) {
//		if (index < 0 || index >= currSize) {
//			return;
//		}
//		for (int i = index; i < currSize - 1; i++) {
//			ptr[i] = ptr[i + 1];
//		}
//		currSize--;
//	}
//
//	//destroy element at index and shift array
//	void Destroy(int index) {
//		if (index == currSize - 1) {
//			currSize--;
//		}
//		else {
//			for (int i = index; i < currSize - 1; ++i) { // Discarding the value not required
//				ptr[i] = ptr[i + 1]; // Move the values by 1
//			}
//			currSize--; // Adjust the current Size
//		}
//	}
//
//	//retunr last element
//	Type& back() {
//		return ptr[currSize - 1];
//	}
//
//	//clear whole array
//	void clear()
//	{
//		delete[] ptr;
//		currSize = 0;
//		maxSize = 5;
//		ptr = new Type[maxSize];
//	}
//};
//
//
////string manipulation functions
//bool isAlphabet(char c)
//{
//	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
//}
//char convertToUppercase(char ch)
//{
//	if (!(ch >= 'a' && ch <= 'z'))
//		return ch;
//	return ch - 32;
//}
//
//
////QUEUE CLASS
//template<class T>
//class qq {
//	//===================================== Queue Node ==========================================
//	struct Node {
//		T data;
//		Node* next;
//		Node(T data = T()) :data(data) {}
//	};
//	Node* frontPointer;
//	Node* rearPointer;
//
//public:
//	//===================================== Queue functions ==========================================
//	qq() {
//		frontPointer = rearPointer = nullptr;
//	}
//	bool isEmpty() { return frontPointer == nullptr; }
//	void enqueue(T data) {
//		Node* newNode = new Node(data);
//		if (isEmpty()) {
//			frontPointer = rearPointer = newNode;
//		}
//		else {
//			rear->next = newNode;
//			rear = rear->next;
//		}
//	}
//	T front() {
//		return frontPointer->data;
//	}
//	T rear() {
//		return rearPointer->data;
//	}
//	T dequeue() {
//		if (isEmpty()) {
//			throw runtime_error("Queue already empty");
//		}
//		else {
//			T data = frontPointer->data;
//			Node* temp = frontPointer;
//			frontPointer = frontPointer->next;
//			delete temp;
//			return data;
//		}
//	}
//	void clear() {
//		while (!this->isEmpty()) {
//			this->dequeue();
//		}
//	}
//	~qq() {
//		clear();
//	}
//};
//
////============================================= String class ==================================================
//class String {
//	char* data;
//	int length;
//
//public:
//	String(); // default constructor
//	String(const char* str); // initializes the string with constant c-string
//	String(const String&); // copy constructor to initialize the string from the existing
//	//string
//	String(int x); // initializes a string of predefined size
//	char* getData() const; //returns the string inside the object
//	// Binary Operators //
//	//Sub - script Operators
//	const char operator[](int i) const; // returns the character at index [x]
//	//NOTE: in above [] operator functions if i=negative int value, print ith character
//	//from end //of string e.g. in case of “LOOP” if i=-1 OR i=3, it should return ‘P’
//		//similarly i = -4 OR i = 0, //return ‘L’
//		// Arithmetic Operators
//	String operator+=(const String& str); // appends a String at the end of the String
//	String operator+=(const char& str); // appends a char at the end of the String
//	String operator+=(const char* str); // appends a String at the end of the String
//
//	String operator-=(const String& substr); //removes the substr from the String
//	String operator-=(const char& str); //removes all occurrences of char from the String
//	String operator-=(const char* str); //removes the str from the String
//
//	// Assignment Operators
//	String& operator=(const String&); // copies one String to another
//	String& operator=(char*); // copies one c-string to another
//
//	bool operator <(const String& other) const;
//	bool operator >(const String& other) const;
//
//	bool operator <=(const String& other) const;
//	bool operator >=(const String& other) const;
//
//
//	//Logical Operators
//	bool operator==(const String&) const; // returns true if two Strings are equal
//	bool operator==(const char*) const; // returns true if the c-string is equal to the
//	//String
//	// Unary Operators //
//	//Boolean Not Operator
//	bool operator!(); // returns true if the String is empty
//
//	// Function-Call Operators
//	////If something is not found then return -1
//
//	int operator()(char) const; // returns the first index of the character being
//	////searched
//	int operator()(const String&) const; // returns the first index of the String
//	////being searched
//	int operator()(const char*) const; // returns the index of the c-string being
//	//searched
//	// Conversion Operator
//	// 
//	operator int() const; // returns the length of string
//	~String() // destructor
//	{
//		delete[] data;
//	}
//
//	//operator overloading for insertion and extaction
//	friend ostream& operator<<(ostream& output, const String& str);
//	friend istream& operator>>(istream& input, String& str);
//
//	//return the size of the current string
//	int getSize()
//	{
//		return this->length;
//	}
//};
//#include<string>//ONLY FOR TO_STRING() SIR I SWEAR 
////ITS NOT USED ELSEWHERE WE NEED IT FOR PATH MANIPULATION ONLY
//
//ostream& operator<<(ostream& output, const String& str) // outputs the string
//{
//	output << str.data;
//	return output;
//}
//istream& operator>>(istream& input, String& str) // inputs the string
//{
//	char ch;
//	while (input.get(ch) && (ch == ' ' || ch == '\n')) {}
//	if (ch != ' ' && ch != '\n' || ch != '\0')
//		str += ch;
//	while (input.get(ch) && ch != '\0' && ch != '\n' && ch != ' ')
//		str += ch;
//	return input;
//}
//
//int Size(const char* str)
//{
//	int size = 0;
//	while (str[size] != '\0')
//		size++;
//	return size;
//}
//int Size(String str)
//{
//	int size = 0;
//	while (str[size] != '\0')
//		size++;
//	return size;
//}
//String::String()
//{
//	length = 0;
//	data = new char[length + 1];
//	data[length] = '\0';
//}
//String::String(const char* str)
//{
//	int size = Size(str);
//	this->length = size;
//	data = new char[size + 1];
//	for (int i = 0; str[i] != '\0'; ++i)
//		data[i] = str[i];
//	data[size] = '\0';
//}
//String::String(const String& copy)
//{
//	this->length = copy.length;
//	data = new char[length + 1];
//	for (int i = 0; copy.data[i] != '\0'; ++i)
//		data[i] = copy.data[i];
//	data[length] = '\0';
//}
//String::String(int x)
//{
//	this->length = x;
//	data = new char[x + 1];
//	for (int i = 0; i <= length; ++i)
//	{
//		data[i] = '\0';
//	}
//}
//char* String::getData() const
//{
//	return data;
//}
//const char String :: operator[](int i)const
//{
//	if (i >= 0 && i < length)
//	{
//		return data[i];
//	}
//	else if (i < 0)
//	{
//		return data[length + i];
//	}
//	else
//	{
//		return '\0';
//	}
//}
//String String::operator+=(const String& str)
//{
//	int strSize = Size(str);
//	int TotalLength = length + strSize;
//	char* newData = new char[TotalLength + 1];
//	int index = 0;
//	for (int i = 0; i < length; i++)
//	{
//		newData[index++] = this->data[i];
//	}
//	for (int i = 0; i < strSize; i++)
//	{
//		newData[index++] = str.data[i];
//	}
//	newData[index] = '\0';
//	delete[] data;
//	data = newData;
//	length = TotalLength;
//
//	return *this;
//}
//String String :: operator+=(const char& str) // appends a char at the end of the String
//{
//	int combinedLength = length + 1;
//
//	char* appendedData = new char[combinedLength + 1];
//
//	int index = 0;
//	for (int i = 0; i < length; i++) {
//		appendedData[index++] = data[i];
//	}
//	appendedData[index++] = str;
//
//	appendedData[index] = '\0';
//
//	delete[] data;
//	data = appendedData;
//	length = combinedLength;
//
//	return *this;
//}
//String String :: operator+=(const char* str)
//{
//
//	int strSize = Size(str);
//	int TotalLength = length + strSize;
//	char* newData = new char[TotalLength + 1];
//	int index = 0;
//	for (int i = 0; i < length; i++)
//	{
//		newData[index++] = this->data[i];
//	}
//	for (int i = 0; i < strSize; i++)
//	{
//		newData[index++] = str[i];
//	}
//	newData[index] = '\0';
//	delete[] data;
//	data = newData;
//	length = TotalLength;
//
//	return *this;
//}
//String String :: operator-=(const String& substr)
//{
//	int strSize = Size(substr);
//	int NewLength = length - strSize;
//
//	char* AppendedData = new char[NewLength + 1];
//	int index = 0;
//	for (int i = 0; this->data[i] != '\0'; ++i)
//	{
//		bool Match = true;
//		for (int j = 0; substr.data[j] != '\0'; ++j)
//		{
//			if (this->data[i + j] != substr.data[j])
//			{
//				Match = false;
//				break;
//			}
//		}
//		if (Match)
//		{
//			i += strSize - 1;
//		}
//		else
//		{
//			AppendedData[index++] = this->data[i];
//		}
//	}
//	AppendedData[index] = '\0';
//	delete[] data;
//	this->data = AppendedData;
//	this->length = NewLength;
//	return *this;
//}
//String String::operator-=(const char& str)
//{
//	int NewLength = length - 1;
//	String NewString;
//	NewString.data = new char[NewLength + 1];
//	int index = 0;
//	for (int i = 0; data[i] != '\0'; ++i)
//	{
//		if (data[i] != str)
//			NewString.data[index++] = data[i];
//	}
//	NewString.data[index] = '\0';
//
//	delete[] data;
//	data = NewString.data;
//	this->length = NewLength;
//	return *this;
//}
//String String ::operator-=(const char* str)
//{
//	int strSize = Size(str);
//	int NewLength = length - strSize;
//
//	char* AppendedData = new char[NewLength + 1];
//	int index = 0;
//	for (int i = 0; this->data[i] != '\0'; ++i)
//	{
//		bool Match = true;
//		for (int j = 0; str[j] != '\0'; ++j)
//		{
//			if (this->data[i + j] != str[j])
//			{
//				Match = false;
//				break;
//			}
//		}
//		if (Match)
//		{
//			i += strSize - 1;
//		}
//		else
//		{
//			AppendedData[index++] = this->data[i];
//		}
//	}
//	AppendedData[index] = '\0';
//	delete[] data;
//	this->data = AppendedData;
//	this->length = NewLength;
//
//	return *this;
//}
//int String :: operator()(char ch) const
//{
//	for (int i = 0; this->data[i] != '\0'; ++i)
//	{
//		if (this->data[i] == ch)
//			return i;
//	}
//	return -1;
//}
//int String ::operator()(const String& str) const
//{
//	int strSize = Size(str);
//	for (int i = 0; i < this->data[i] != '\0'; ++i)
//	{
//		bool Match = true;
//		for (int j = 0; j < strSize; ++j)
//		{
//			if (this->data[i + j] != str.data[j])
//			{
//				Match = false;
//				break;
//			}
//		}
//		if (Match)
//		{
//			return i;
//		}
//	}
//	return -1;
//}
//int String ::operator()(const char* str) const
//{
//	int strSize = Size(str);
//	for (int i = 0; i < this->data[i] != '\0'; ++i)
//	{
//		bool Match = true;
//		for (int j = 0; j < strSize; ++j)
//		{
//			if (this->data[i + j] != str[j])
//			{
//				Match = false;
//				break;
//			}
//		}
//		if (Match)
//		{
//			return i;
//		}
//	}
//	return -1;
//}
//String :: operator int() const
//{
//	int i = 0;
//	while (this->data[i] != '\0')
//	{
//		i++;
//	}
//	return i;
//}
//bool String :: operator!()
//{
//	if (this->length == 0 || this->data[0] == '\0')
//		return true;
//	return false;
//}
//bool String :: operator==(const String& str) const
//{
//	if (this->length != str.length)
//		return false;
//	for (int i = 0; data[i] != '\0'; ++i)
//	{
//		if (data[i] != str.data[i])
//		{
//			if (isAlphabet(data[i]) && isAlphabet(str.data[i]) && ((data[i] + 32) == str.data[i] || (data[i] - 32) == str.data[i]))
//				continue;
//			return false;
//		}
//	}
//	return true;
//}
//bool String ::operator==(const char* str) const
//{
//	if (this->length != Size(str))
//		return false;
//	for (int i = 0; data[i] != '\0'; ++i)
//	{
//		if (data[i] != str[i])
//		{
//			if (isAlphabet(data[i]) && isAlphabet(str[i]) && ((data[i] + 32) == str[i] || (data[i] - 32) == str[i]))
//				continue;
//			return false;
//		}
//	}
//	return true;
//}
//String& String :: operator=(const String& str)
//{
//	int strSize = Size(str);
//	char* newData = new char[strSize + 1];
//	for (int i = 0; str.data[i] != '\0'; ++i)
//	{
//		newData[i] = str.data[i];
//	}
//	newData[strSize] = '\0';
//	delete[] data;
//	this->data = newData;
//	this->length = strSize;
//	return *this;
//}
//String& String ::operator=(char* str)
//{
//	int strSize = Size(str);
//	char* newData = new char[strSize + 1];
//	for (int i = 0; str[i] != '\0'; ++i)
//	{
//		newData[i] = str[i];
//	}
//	newData[strSize] = '\0';
//	delete[] data;
//	this->data = newData;
//	this->length = strSize;
//	return *this;
//}
//
//inline bool getline(istream& input, String& str, char delim = '\n') {
//	str = "";
//	char ch;
//	while (input.get(ch) && ch != delim)
//	{
//		str += ch;
//	}
//
//	if (input.eof() || input.fail()) {
//		return !str;
//	}
//	return true;
//}
//
//bool String::operator<(const String& other) const
//{
//	int index = 0;
//	while (this->data[index] != '\0' && other.data[index] != '\0')
//	{
//		if (isAlphabet(data[index]) && isAlphabet(other.data[index]) && ((data[index] + 32) == other.data[index] || (data[index] - 32) == other.data[index]))
//		{
//			index++;
//			continue;
//		}
//		if (this->data[index] < other.data[index])
//		{
//			return true;
//		}
//		else if (this->data[index] > other.data[index])
//		{
//			return false;
//		}
//		index++;
//	}
//	return this->length < other.length;
//}
//
//bool String::operator>(const String& other) const
//{
//	int index = 0;
//	while (this->data[index] != '\0' && other.data[index] != '\0')
//	{
//		if (isAlphabet(data[index]) && isAlphabet(other.data[index]) && ((data[index] + 32) == other.data[index] || (data[index] - 32) == other.data[index]))
//		{
//			index++;
//			continue;
//		}
//		if (this->data[index] > other.data[index])
//		{
//			return true;
//		}
//		else if (this->data[index] < other.data[index])
//		{
//			return false;
//		}
//		index++;
//	}
//	return this->length > other.length;
//}
//
//inline bool String::operator<=(const String& other) const
//{
//	return ((*this < other) || (*this == other));
//}
//
//inline bool String::operator>=(const String& other) const
//{
//	return ((*this > other) || (*this == other));
//}
//
//struct RowEntry
//{
//	long long rowIndex;
//	Vector<String> cells;
//
//	friend ostream& operator<<(ostream& os, RowEntry& row)
//	{
//		for (int i = 0; i < row.cells.getCurr(); ++i)
//		{
//			if (i > 0) os << ',';
//			os << row.cells[i];
//		}
//		return os;
//	}
//
//	friend istream& operator>>(istream& is, RowEntry& row)
//	{
//		row.cells.clear();
//		String line;
//		getline(is, line);
//		if (!(!line))
//		{
//			int index = 0;
//			while (index < line.getSize())
//			{
//				row.cells.push_back(parseField(line, index));
//			}
//		}
//		return is;
//	}
//
//	static String parseField(String& row, int& index)
//	{
//		String field;
//		bool quoted = false;
//
//		if (row[index] == '"')
//		{
//			quoted = true;
//			++index;
//		}
//
//		while (index < row.getSize())
//		{
//			if (quoted)
//			{
//				if (row[index] == '"')
//				{
//					++index;
//					if (index < row.getSize() && row[index] == ',')
//					{
//						++index;
//					}
//					break;
//				}
//				else
//				{
//					if (isAlphabet(row[index]))
//						field += convertToUppercase(row[index++]);
//					else if (row[index] == '/')
//					{
//						field += '-';
//						index++;
//					}
//					else
//						field += row[index++];
//				}
//			}
//			else
//			{
//				if (row[index] == ',')
//				{
//					++index;
//					break;
//				}
//				else
//				{
//					if (isAlphabet(row[index]))
//						field += convertToUppercase(row[index++]);
//					else if (row[index] == '/')
//					{
//						field += '-';
//						index++;
//					}
//					else
//						field += row[index++];
//				}
//			}
//		}
//
//		return field;
//	}
//
//	void readRow(long long rowIndex, String& row)
//	{
//		this->rowIndex = rowIndex;
//		cells.clear();
//		int index = 0;
//		while (index < row.getSize())
//		{
//			cells.push_back(parseField(row, index));
//		}
//	}
//	String toString()
//	{
//		String row;
//		for (int a = 0; a < cells.getCurr(); a++)
//		{
//			if (a > 0)
//				row += ',';
//			row += cells[a];
//		}
//		return row;
//	}
//};
//
///*
//	parent class for btree,avl and rb tree
//	will use polymorphism to access whatever tree is used
//*/
//template <class T>
//class ParentTree
//{
//protected:
//	//convert absolute paths to relative
//	static filesystem::path makeRelative(const filesystem::path& fullPath)
//	{
//		filesystem::path result;
//		bool treeFound = false;
//
//		for (const auto& part : fullPath) {
//			if (part == "TREE") {
//				treeFound = true;
//			}
//			if (treeFound) {
//				result /= part;
//			}
//		}
//		return result;
//	}
//	class Node;
//public:
//
//	//update branch paths upon checkout
//	static void updateNewBranch(const path& targetFile, const path& oldBranch, const path& newBranch)
//	{
//		ifstream file(targetFile);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'TREE_DATA.txt\' for reading.");
//
//		path tempRootPath;
//		path tempFolderPath;
//		long long tempStaticCounter;
//		path tempBranchPath;
//
//		file >> tempRootPath;
//		file >> tempFolderPath;
//		file >> tempBranchPath;
//
//		file.close();
//
//		ofstream rewritefile(targetFile);
//		if (!rewritefile.is_open())
//			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for writing.");
//
//		path newPath;
//
//		newPath.clear();
//		for (const auto& part : tempRootPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//
//		newPath.clear();
//		for (const auto& part : tempFolderPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//
//		newPath.clear();
//		for (const auto& part : tempBranchPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//
//		rewritefile.close();
//	}
//
//	std::filesystem::path rootPath;
//	std::filesystem::path folderPath;
//	std::filesystem::path branchPath;
//
//	virtual void insert(const T& data, const long long& rowIndex) = 0;
//	virtual void remove(const T& data, const long long& rowIndex) = 0;
//	virtual Vector<long long> search(const T& data) = 0;
//	virtual void print() = 0;
//	virtual void saveDataToFile() = 0;
//};
//
//int hashTypeGlobal;
//class MerkleTree
//{
//private:
//
//	//===================================== Merkle Node ==========================================
//	struct Node
//	{
//		long long index;
//		int height;
//		RowEntry rowData;
//		String hash;
//		filesystem::path left;	 //left child path
//		filesystem::path right;	 //right child path
//		filesystem::path parent;	 //parent path
//
//		Node(int index = -1, RowEntry rowData = RowEntry()) : index(index), rowData(rowData), height(0), hash("InsertHashHere"), left("NULL"), right("NULL"), parent("NULL")
//		{}
//
//		//convert absolute paths to relative
//		filesystem::path makeRelative(const filesystem::path& fullPath)
//		{
//			filesystem::path result;
//			bool treeFound = false;
//
//			for (const auto& part : fullPath) {
//				if (part == "MERKLETREE") {
//					treeFound = true;
//				}
//				if (treeFound) {
//					result /= part;
//				}
//			}
//			return result;
//		}
//
//		//helper to calc hash
//		String calculateHash(String& input)
//		{
//			String resString;
//
//			//instructor %29 hash
//			if (::hashTypeGlobal == 1)
//			{
//				long long res = 1;
//				for (int a = 0; a < input.getSize(); a++)
//				{
//					res *= input[a];
//					res = res % 29;
//				}
//				int firstChar = res / 10;
//				resString += (firstChar + '0');
//				int secondChar = res % 10;
//				resString += (secondChar + '0');
//				return resString;
//			}
//			//sha-256
//			else if (::hashTypeGlobal == 2)
//			{
//				unsigned char hash[SHA256_DIGEST_LENGTH];
//				SHA256((unsigned char*)input.getData(), input.getSize(), hash);
//
//				// Convert hash to hexadecimal String
//				std::ostringstream oss;
//				for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//					oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//				}
//				resString = oss.str().c_str(); 
//				return resString;
//			}
//
//		}
//
//		void updateHash(const filesystem::path& leftPath, const filesystem::path& rightPath, const MerkleTree& merc)
//		{
//			String data = rowData.toString();
//
//			if (leftPath != "NULL") {
//				Node leftNode = readFile(leftPath, merc);
//				data += leftNode.hash;
//			}
//			if (rightPath != "NULL") {
//				Node rightNode = readFile(rightPath, merc);
//				data += rightNode.hash;
//			}
//
//			this->hash = calculateHash(data);
//		}
//
//
//		void updateFile(const filesystem::path& path)
//		{
//			if (path == "NULL")
//				throw runtime_error("Attempting to access empty path.");
//
//			ofstream file;
//			file.open(path);
//			if (!file.is_open())
//				throw runtime_error("Cannot open file for writing.");
//
//			file << this->index << '\n';
//			file << this->height << '\n';
//			file << this->rowData << '\n';
//			file << this->hash << '\n';
//			file << (this->left == "NULL" ? "NULL" : makeRelative(this->left)) << '\n';
//			file << (this->right == "NULL" ? "NULL" : makeRelative(this->right)) << '\n';
//			file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';
//
//			file.close();
//		}
//
//		static Node readFile(const filesystem::path& path, const MerkleTree& merc)
//		{
//			if (path == "NULL")
//				throw runtime_error("Attempting to access empty path.");
//
//			ifstream file;
//			file.open(path);
//			if (!file.is_open())
//				throw runtime_error("Cannot open file for reading.");
//
//			Node node;
//			file >> node.index;
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			file >> node.height;
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			file >> node.rowData;
//			node.rowData.rowIndex = node.index;
//			getline(file, node.hash);
//
//			filesystem::path temp;
//
//
//			file >> temp;
//			if (temp == "NULL")
//				node.left = "NULL";
//			else
//			{
//				node.left = merc.branchPath;
//				node.left /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.right = "NULL";
//			else
//			{
//				node.right = merc.branchPath;
//				node.right /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.parent = "NULL";
//			else
//			{
//				node.parent = merc.branchPath;
//				node.parent /= temp;
//			}
//
//			file.close();
//			return node;
//		}
//	};
//
//	// =====================================  functions ==========================================
//
//	//generate a filePath based on the value of a node
//	template<class T>
//	filesystem::path generateFilePath(const T& value)
//	{
//		// Construct the file path
//		filesystem::path filePath = folderPath / "NODES";
//		filePath /= to_string(value);
//		filePath += ".txt";
//		return filePath;
//	}
//
//	bool removeFile(filesystem::path& path)
//	{
//		if (filesystem::exists(path))
//		{
//			filesystem::remove(path);
//			return true;
//		}
//		return false;
//
//	}
//
//	//get height of node
//	int Height(const filesystem::path& path)
//	{
//		if (path.empty() || path == "NULL")
//			return -1;
//		else
//		{
//			return Node::readFile(path, *this).height;
//		}
//	}
//
//	//NOTE : updates height in file
//	void updateNodeHeight(const filesystem::path& path)
//	{
//		if (path.empty() || path == "NULL")
//			return;
//
//		Node node = Node::readFile(path, *this);
//		int leftHeight = Height(node.left);
//		int rightHeight = Height(node.right);
//
//		node.height = max(leftHeight, rightHeight) + 1;
//		node.updateHash(node.left, node.right, *this);
//		node.updateFile(path);
//		return;
//	}
//
//	//BF = Right - Left
//	int balanceFactor(const filesystem::path& path)
//	{
//		Node node = Node::readFile(path, *this);
//		int leftHeight = Height(node.left);
//		int rightHeight = Height(node.right);
//
//		return rightHeight - leftHeight;
//	}
//
//	//========= rotations ===========
//
//	//INPUT: PATH
//	//automatically updates parent, old and new pivots
//	void rotateRight(filesystem::path& path)
//	{
//		Node mainNode = Node::readFile(path, *this);
//		Node leftNode = Node::readFile(mainNode.left, *this);
//		filesystem::path leftNodePath = mainNode.left;
//		filesystem::path leftNodeKaRightPath = leftNode.right;
//
//		//attach old pivot with new pivot's left subtree
//		mainNode.left = leftNodeKaRightPath;
//		if (leftNodeKaRightPath != "NULL")
//		{
//			Node leftNodesRight_NODE = Node::readFile(leftNodeKaRightPath, *this);
//			leftNodesRight_NODE.parent = path;
//			leftNodesRight_NODE.updateFile(leftNodeKaRightPath);
//		}
//
//		//attach new pivot with old pivot's parent
//		leftNode.parent = mainNode.parent;
//
//		//put old pivot at new pivot's left child
//		leftNode.right = path;
//		mainNode.parent = leftNodePath;
//
//		//update heights
//		mainNode.updateFile(path);
//		leftNode.updateFile(leftNodePath);
//		updateNodeHeight(path);
//		updateNodeHeight(leftNodePath);
//
//		//update the parent if it exists
//		if (leftNode.parent != "NULL")
//		{
//			Node parentNode = Node::readFile(leftNode.parent, *this);
//			parentNode.left == path ? parentNode.left = leftNodePath : parentNode.right = leftNodePath;
//
//			parentNode.updateFile(leftNode.parent);
//			updateNodeHeight(leftNode.parent);
//		}
//		path = leftNodePath;
//	}
//
//
//	//INPUT: PATH
//	//automatically updates parent, old and new pivots
//	void rotateLeft(filesystem::path& path)
//	{
//		Node mainNode = Node::readFile(path, *this);
//		Node rightNode = Node::readFile(mainNode.right, *this);
//		filesystem::path rightNodePath = mainNode.right;
//		filesystem::path rightNodeKaLeftPath = rightNode.left;
//
//		//attach old pivot with new pivot's left subtree
//		mainNode.right = rightNodeKaLeftPath;
//		if (rightNodeKaLeftPath != "NULL")
//		{
//			Node rightNodesleft_NODE = Node::readFile(rightNodeKaLeftPath, *this);
//			rightNodesleft_NODE.parent = path;
//			rightNodesleft_NODE.updateFile(rightNodeKaLeftPath);
//		}
//
//		//attach new pivot with old pivot's parent
//		rightNode.parent = mainNode.parent;
//
//		//put old pivot at new pivot's left child
//		rightNode.left = path;
//		mainNode.parent = rightNodePath;
//
//		//update heights
//		mainNode.updateFile(path);
//		rightNode.updateFile(rightNodePath);
//		updateNodeHeight(path);
//		updateNodeHeight(rightNodePath);
//
//		//update the parent if it exists
//		if (rightNode.parent != "NULL")
//		{
//			Node parentNode = Node::readFile(rightNode.parent, *this);
//			parentNode.left == path ? parentNode.left = rightNodePath : parentNode.right = rightNodePath;
//
//			parentNode.updateFile(rightNode.parent);
//			updateNodeHeight(rightNode.parent);
//		}
//		path = rightNodePath;
//
//	}
//
//	//returns 1 if rotations occured
//	bool balanceNode(filesystem::path& path)
//	{
//		Node node = Node::readFile(path, *this);
//		int BF = balanceFactor(path);
//
//		//right heavy
//		if (BF == 2)
//		{
//			int rightBF = balanceFactor(node.right);
//
//			if (rightBF == 1 || rightBF == 0)
//			{
//				rotateLeft(path);
//			}
//			else if (rightBF == -1)
//			{
//				rotateRight(node.right);
//				rotateLeft(path);
//			}
//			return 1;
//		}
//		//left heavy
//		else if (BF == -2)
//		{
//			int leftBF = balanceFactor(node.left);
//
//			if (leftBF == -1 || leftBF == 0)
//			{
//				rotateRight(path);
//			}
//			else if (leftBF == 1)
//			{
//				rotateLeft(node.left);
//				rotateRight(path);
//			}
//			return 1;
//		}
//
//		return 0;
//	}
//
//	//NOTE: updates path sent as parameter
//	//returns the currently inserted index
//	long long helperInsert(filesystem::path& path, const filesystem::path& parentPath, const RowEntry& row)
//	{
//		if (path == "NULL")
//		{
//			filesystem::path newFilePath = generateFilePath(staticCounter);
//			Node newNode(staticCounter, row);
//			newNode.parent = parentPath;
//			path = newFilePath;
//			newNode.updateHash(newNode.left, newNode.right, *this);
//			newNode.updateFile(newFilePath);
//			long long temp = staticCounter;
//			staticCounter++;
//			return temp;
//		}
//		else
//		{
//			long long temp;
//			Node current = Node::readFile(path, *this);
//			if (staticCounter < current.index)
//			{
//				temp = helperInsert(current.left, path, row);
//			}
//			else if (staticCounter > current.index)
//			{
//				temp = helperInsert(current.right, path, row);
//			}
//			else if (staticCounter == current.index)
//			{
//				return staticCounter;
//			}
//			current.updateHash(current.left, current.right, *this);
//			current.updateFile(path);
//			updateNodeHeight(path);
//
//			int BF = balanceFactor(path);
//			if (BF == 2 || BF == -2)
//			{
//				balanceNode(path);
//			}
//			return temp;
//		}
//	}
//
//	//Updates path sent as para
//	void helperRemove(filesystem::path& path, const long long& index)
//	{
//		//didnt find element
//		if (path.empty() || path == "NULL")
//		{
//			return;
//		}
//
//		Node node = Node::readFile(path, *this);
//
//		//find the element
//		if (index < node.index)
//		{
//			helperRemove(node.left, index);
//		}
//		else if (index > node.index)
//		{
//			helperRemove(node.right, index);
//		}
//		//element found
//		else
//		{
//			//have to completely remove file
//
//			//Case 1: No left child
//			if (node.left == "NULL")
//			{
//				if (node.right != "NULL")
//				{
//					Node right = Node::readFile(node.right, *this);
//					right.parent = node.parent;
//					right.updateFile(node.right);
//				}
//				if (node.parent != "NULL")
//				{
//					Node parent = Node::readFile(node.parent, *this);
//					parent.left == path ? parent.left = node.right : parent.right = node.right;
//					parent.updateFile(node.parent);
//					updateNodeHeight(node.parent);
//				}
//				removeFile(path);
//				path = "NULL";
//				return;
//			}
//
//			//Case 2: No right child
//			else if (node.right == "NULL")
//			{
//				if (node.left != "NULL")
//				{
//					Node left = Node::readFile(node.left, *this);
//					left.parent = node.parent;
//					left.updateFile(node.left);
//				}
//				if (node.parent != "NULL")
//				{
//					Node parent = Node::readFile(node.parent, *this);
//					parent.left == path ? parent.left = node.left : parent.right = node.left;
//					parent.updateFile(node.parent);
//					updateNodeHeight(node.parent);
//				}
//				removeFile(path);
//				path = "NULL";
//				return;
//			}
//
//			//Case 3: Both childs exist
//			else if (node.right != "NULL" && node.left != "NULL")
//			{
//				//find inorder successor
//				Node successor = Node::readFile(node.right, *this);
//				filesystem::path successorPath = node.right;
//
//				while (successor.left != "NULL")
//				{
//					successorPath = successor.left;
//					successor = Node::readFile(successor.left, *this);
//				}
//
//				//replace nodes data with successor data
//				node.index = successor.index;
//				node.rowData = successor.rowData;
//				node.hash = successor.hash;
//				node.updateFile(path);
//				filesystem::path updatedPath = generateFilePath(successor.index);
//
//				helperRemove(node.right, successor.index);
//
//				//rename the node that just got replaced and update the new path in all neighbors
//				node = Node::readFile(path, *this);
//				filesystem::rename(path, updatedPath);
//				if (node.parent != "NULL")
//				{
//					Node parent = Node::readFile(node.parent, *this);
//					parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
//					parent.updateFile(node.parent);
//				}
//				if (node.left != "NULL")
//				{
//					Node left = Node::readFile(node.left, *this);
//					left.parent = updatedPath;
//					left.updateFile(node.left);
//				}
//				if (node.right != "NULL")
//				{
//					Node right = Node::readFile(node.right, *this);
//					right.parent = updatedPath;
//					right.updateFile(node.right);
//				}
//				path = updatedPath;
//			}
//		}
//		node.updateHash(node.left, node.right, *this);
//		node.updateFile(path);
//		//rolling back after deletion, balance any imbalanced nodes
//		int BF = balanceFactor(path);
//		if (BF >= 2 || BF <= -2)
//		{
//			balanceNode(path);
//		}
//	}
//
//	void inorderPrint(const filesystem::path& path, int depth = 0)
//	{
//		if (path.empty() || path == "NULL")
//		{
//			for (int a = 0; a < depth; a++)
//			{
//				cout << '\t';
//			}
//			cout << "-" << endl;
//			return;
//		}
//		Node node = Node::readFile(path, *this);
//		inorderPrint(node.right, depth + 1);
//		for (int a = 0; a < depth; a++)
//		{
//			cout << '\t';
//		}
//		cout << node.index << "(" << node.hash << ")" << endl;
//		inorderPrint(node.left, depth + 1);
//	}
//
//	Node helperSearch(const filesystem::path& root, const long long& value) {
//		if (root == "NULL") {
//			return Node();
//		}
//
//		Node currentNode = Node::readFile(root, *this);
//
//		if (value < currentNode.index) {
//			return helperSearch(currentNode.left, value);
//		}
//		else if (value > currentNode.index) {
//			return helperSearch(currentNode.right, value);
//		}
//		else {
//			return currentNode;
//		}
//	}
//	void helperUpdate(const filesystem::path& root, const long long& index, const int& fieldIndex, const String& newValue)
//	{
//		if (root == "NULL")
//			return;
//		Node currentNode = Node::readFile(root, *this);
//
//		if (index < currentNode.index) {
//			helperUpdate(currentNode.left, index, fieldIndex, newValue);
//		}
//		else if (index > currentNode.index) {
//			helperUpdate(currentNode.right, index, fieldIndex, newValue);
//		}
//		else
//		{
//			currentNode.rowData.cells[fieldIndex] = newValue;
//			currentNode.updateHash(currentNode.left, currentNode.right, *this);
//			currentNode.updateFile(root);
//			return;
//		}
//		currentNode.updateHash(currentNode.left, currentNode.right, *this);
//		currentNode.updateFile(root);
//	}
//	static long long staticCounter;
//public:
//
//
//	filesystem::path rootPath;
//	filesystem::path folderPath;
//	filesystem::path branchPath;
//
//	////////////////////////////////// CONSTRUCTORS /////////////////////////////////////////
//	MerkleTree()
//	{}
//	MerkleTree(filesystem::path branchPath) : folderPath(branchPath), rootPath("NULL"), branchPath(branchPath)
//	{
//		this->folderPath /= "MERKLETREE";
//		if (!filesystem::exists(this->folderPath))
//		{
//			filesystem::create_directories(this->folderPath);
//			filesystem::path nodesPath = this->folderPath / "NODES";
//			filesystem::create_directories(nodesPath);
//		}
//	}
//	MerkleTree(bool loadTreeFromBranch, path branchPath)
//	{
//		if (loadTreeFromBranch)
//		{
//			loadFromBranch(branchPath);
//		}
//	}
//
//	//////////////////////////////////UI/////////////////////////////////////////
//	long long getCounter()
//	{
//		return this->staticCounter;
//	}
//	long long insert(const RowEntry& row)
//	{
//		return helperInsert(rootPath, "NULL", row);
//	}
//	void remove(const long long& index)
//	{
//		helperRemove(rootPath, index);
//	}
//
//	void print()
//	{
//		cout << "---------------------------------------------------- " << endl;
//		inorderPrint(rootPath);
//	}
//
//	//saves path of root into a file
//	void saveDataToFile()
//	{
//		ofstream file;
//		filesystem::path path = folderPath;
//		path += "\\MERKLE_DATA.txt";
//		file.open(path);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for writing.");
//		file << rootPath << '\n';
//		file << folderPath << '\n';
//		file << staticCounter << '\n';
//		file << this->branchPath << '\n';
//		file.close();
//	}
//	void loadFromBranch(path branchPath)
//	{
//		branchPath /= "MERKLETREE";
//		branchPath /= "MERKLE_DATA.txt";
//		if (!exists(branchPath))
//			throw runtime_error("File to load tree from doesnt exist.");
//		ifstream file(branchPath);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for reading.");
//		file >> rootPath;
//		file >> folderPath;
//		file >> staticCounter;
//		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//		file >> this->branchPath;
//		file.close();
//	}
//
//	static void updateNewBranch(const path& targetFile, const path& oldBranch, const path& newBranch)
//	{
//		ifstream file(targetFile);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for reading.");
//
//		path tempRootPath;
//		path tempFolderPath;
//		long long tempStaticCounter;
//		path tempBranchPath;
//
//		file >> tempRootPath;
//		file >> tempFolderPath;
//		file >> tempStaticCounter;
//		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//		file >> tempBranchPath;
//
//		file.close();
//
//		ofstream rewritefile(targetFile);
//		if (!rewritefile.is_open())
//			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for writing.");
//
//		path newPath;
//
//		newPath.clear();
//		for (const auto& part : tempRootPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//
//		newPath.clear();
//		for (const auto& part : tempFolderPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//		rewritefile << tempStaticCounter << '\n';
//
//		newPath.clear();
//		for (const auto& part : tempBranchPath) {
//			if (part == oldBranch) {
//				newPath /= newBranch;
//			}
//			else {
//				newPath /= part;
//			}
//		}
//		rewritefile << newPath << '\n';
//
//		rewritefile.close();
//	}
//	String search(const long long& data)
//	{
//		Node node = this->helperSearch(this->rootPath, data);
//		String curr;
//		for (int a = 0; a < node.rowData.cells.getCurr(); a++)
//		{
//			if (a > 0)
//				curr += ',';
//			curr += node.rowData.cells[a];
//		}
//		return curr;
//	}
//	RowEntry searchRowEntry(long long& data)
//	{
//		Node node = this->helperSearch(this->rootPath, data);
//		return node.rowData;
//	}
//	void update(const long long& index, const int& fieldIndex, const String& newValue)
//	{
//		helperUpdate(this->rootPath, index, fieldIndex, newValue);
//	}
//
//};
//long long MerkleTree::staticCounter = 0;
//
//
//
//enum NodeColor {
//	RED, // 0
//	BLACK // 1
//};
//
//
//template<class T>
//class RedBlackTree : public ParentTree<T> {
//	//===================================== RedBlackNode Node ==========================================
//	struct Node {
//		T data;
//		String hash;
//		filesystem::path left;
//		filesystem::path right;
//		filesystem::path parent;
//		NodeColor color;
//		bool debt;
//		int frequency;
//		Vector<long long> rowIndexes;
//		Node(T data = T()) {
//			this->data = data;
//			color = RED;
//			debt = false;
//			frequency = 1;
//			hash = "HASH";
//			left = "NULL";
//			right = "NULL";
//			parent = "NULL";
//		}
//		void updateFile(const filesystem::path& path) {
//			if (path == "NULL") {
//				throw runtime_error("Unable to find path");
//			}
//			ofstream file;
//			file.open(path);
//			if (!file.is_open()) {
//				throw runtime_error("Error..Unable to open file for Writing");
//			}
//
//			file << this->data << '\n';
//			file << this->frequency << '\n';
//			for (int a = 0; a < this->frequency; a++)
//			{
//				if (a > 0)
//					file << ' ';
//				file << this->rowIndexes[a];
//			}
//			file << '\n';
//			file << this->color << '\n';
//			file << this->hash << '\n';
//			file << (this->left == "NULL" ? "NULL" : makeRelative(this->left)) << '\n';
//			file << (this->right == "NULL" ? "NULL" : makeRelative(this->right)) << '\n';
//			file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';
//			file << this->debt << '\n';
//			file.close();
//		}
//		static Node readFile(const filesystem::path& path, const RedBlackTree& merc) {
//			if (path == "NULL") {
//				throw runtime_error("Accessing NULL path");
//			}
//			ifstream file;
//			file.open(path);
//			if (!file.is_open()) {
//				throw runtime_error("Unable to open file for reading..");
//			}
//
//			Node node;
//			if constexpr (is_same<T, String>::value) {
//				getline(file, node.data);
//			}
//			else {
//				file >> node.data;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			}
//			file >> node.frequency;
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			char delim;
//			long long index;
//			for (int a = 0; a < node.frequency; a++)
//			{
//				file >> index;
//				node.rowIndexes.push_back(index);
//			}
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			int color;
//			file >> color;
//			node.color = static_cast<NodeColor>(color);
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//			getline(file, node.hash);
//			filesystem::path temp;
//
//			file >> temp;
//			if (temp == "NULL")
//				node.left = "NULL";
//			else
//			{
//				node.left = merc.branchPath;
//				node.left /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.right = "NULL";
//			else
//			{
//				node.right = merc.branchPath;
//				node.right /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.parent = "NULL";
//			else
//			{
//				node.parent = merc.branchPath;
//				node.parent /= temp;
//			}
//
//			file >> node.debt;
//
//			file.close();
//			return node;
//		}
//	};
//	//===================================== File Functions ==========================================
//	filesystem::path createPath(const T& value) {
//
//		// Construct the file path
//		filesystem::path filePath = folderPath / "NODES";
//		if constexpr (is_same<T, String>::value)
//		{
//			filePath /= value.getData();
//		}
//		else
//		{
//			filePath /= value;
//		}
//		filePath += ".txt";
//		return filePath;
//	}
//	bool removeFile(filesystem::path& path) {
//		if (filesystem::exists(path)) {
//			filesystem::remove(path);
//			return true;
//		}
//		return false;
//
//	}
//	//===================================== Node Functions ==========================================
//	//===================================== Encapsulated Functions ==========================================
//	void rotateRight(filesystem::path& path) {
//		Node node = Node::readFile(path, *this);
//
//		if (node.left == "NULL") {
//			throw runtime_error("Cannot perform right rotation on a node with no left child.");
//		}
//		Node leftNode = Node::readFile(node.left, *this);
//		filesystem::path leftPath = node.left;
//		filesystem::path grandRightPath = leftNode.right;
//
//		node.left = grandRightPath;
//		if (grandRightPath != "NULL") {
//			Node grandRightNode = Node::readFile(grandRightPath, *this);
//			grandRightNode.parent = path;
//			grandRightNode.updateFile(grandRightPath);
//		}
//
//		leftNode.parent = node.parent;
//
//		if (node.parent != "NULL") {
//			Node parentNode = Node::readFile(node.parent, *this);
//			if (parentNode.left == path) {
//				parentNode.left = leftPath;
//			}
//			else {
//				parentNode.right = leftPath;
//			}
//			parentNode.updateFile(node.parent);
//		}
//		else {
//			rootPath = leftPath;
//		}
//
//		leftNode.right = path;
//		node.parent = leftPath;
//		node.color = RED;
//		leftNode.color = BLACK;
//		node.updateFile(path);
//		leftNode.updateFile(leftPath);
//		// path = leftPath;
//	}
//	void rotateLeft(filesystem::path& path) {
//		Node node = Node::readFile(path, *this);
//		Node rightNode = Node::readFile(node.right, *this);
//
//		filesystem::path rightPath = node.right;
//		filesystem::path grandLeftChildPath = rightNode.left;
//		node.right = grandLeftChildPath;
//
//		if (grandLeftChildPath != "NULL") {
//			Node grandLeftChildNode = Node::readFile(grandLeftChildPath, *this);
//			grandLeftChildNode.parent = path;
//			grandLeftChildNode.updateFile(grandLeftChildPath);
//		}
//		rightNode.parent = node.parent;
//
//		if (node.parent != "NULL") {
//			Node parentNode = Node::readFile(node.parent, *this);
//			if (parentNode.left == path) {
//				parentNode.left = rightPath;
//			}
//			else {
//				parentNode.right = rightPath;
//			}
//			parentNode.updateFile(node.parent);
//		}
//		else {
//			rootPath = rightPath;
//		}
//
//		rightNode.left = path;
//		node.parent = rightPath;
//		node.color = RED;
//		rightNode.color = BLACK;
//		node.updateFile(path);
//		rightNode.updateFile(rightPath);
//		// path = rightPath;
//	}
//
//	void fixOrientation_Insertion(filesystem::path& path) {
//		if (path == "NULL") return;
//		if (path == rootPath) {
//			Node node = Node::readFile(path, *this);
//			node.color = BLACK;
//			node.updateFile(path);
//			return;
//		}
//		Node node = Node::readFile(path, *this);
//		filesystem::path Parentpath = node.parent;
//		Node parent = Node::readFile(Parentpath, *this);
//
//		if (parent.color == RED) {
//			filesystem::path grandParentPath = parent.parent;
//			Node grandParent = Node::readFile(grandParentPath, *this);
//			filesystem::path unclePath = grandParent.left == Parentpath ? grandParent.right : grandParent.left;
//			Node uncle;
//			if (unclePath != "NULL") {
//				uncle = Node::readFile(unclePath, *this);
//			}
//
//			if (unclePath != "NULL" && uncle.color == RED) {
//				uncle.color = BLACK;
//				parent.color = BLACK;
//				if (grandParentPath != rootPath) {
//					grandParent.color = RED;
//					grandParent.updateFile(grandParentPath);
//				}
//				uncle.updateFile(unclePath);
//				parent.updateFile(Parentpath);
//				fixOrientation_Insertion(grandParentPath);
//			}
//			else {
//				bool isleftChild = (grandParent.left == Parentpath);
//				bool isNodeLeftChild = (parent.left == path);
//
//				if (isleftChild && isNodeLeftChild) { // LL
//					rotateRight(grandParentPath);
//				}
//				else if (!isleftChild && !isNodeLeftChild) { // RR
//					rotateLeft(grandParentPath);
//				}
//				else if (isleftChild && !isNodeLeftChild) { // LR
//					rotateLeft(Parentpath);
//					rotateRight(grandParentPath);
//				}
//				else if (!isleftChild && isNodeLeftChild) { // Rl
//					rotateRight(Parentpath);
//					rotateLeft(grandParentPath);
//				}
//			}
//		}
//	}
//	void insertNode(filesystem::path& path, const T& data, const long long& rowIndex) {
//		if (path == "NULL") {
//			filesystem::path newPath = createPath(data);
//			Node newNode(data);
//			newNode.parent = "NULL";
//			newNode.rowIndexes.push_back(rowIndex);
//			path = newPath;
//			newNode.color = BLACK;
//			newNode.updateFile(newPath);
//			return;
//		}
//		else {
//			Node curr = Node::readFile(path, *this);
//			if (data == curr.data) {
//				curr.frequency++;
//				curr.rowIndexes.push_back(rowIndex);
//				curr.updateFile(path);
//				return;
//			}
//			else if (data < curr.data) {
//				if (curr.left == "NULL") {
//					filesystem::path newPath = createPath(data);
//					Node newNode(data);
//					newNode.parent = path;
//					newNode.rowIndexes.push_back(rowIndex);
//					curr.left = newPath;
//					newNode.updateFile(newPath);
//					curr.updateFile(path);
//					fixOrientation_Insertion(newPath);
//					return;
//				}
//				else {
//					insertNode(curr.left, data, rowIndex);
//				}
//			}
//			else if (data > curr.data) {
//				if (curr.right == "NULL") {
//					filesystem::path newPath = createPath(data);
//					Node newNode(data);
//					newNode.parent = path;
//					newNode.rowIndexes.push_back(rowIndex);
//					curr.right = newPath;
//					newNode.updateFile(newPath);
//					curr.updateFile(path);
//					fixOrientation_Insertion(newPath);
//					return;
//				}
//				else {
//					insertNode(curr.right, data, rowIndex);
//				}
//			}
//		}
//	}
//	void fixDebt(filesystem::path& path) {
//		if (path == "NULL") return;
//		Node parent;
//		Node sibling;
//		Node node = Node::readFile(path, *this);
//
//		if (node.color == RED) {
//			node.color = BLACK;
//			node.updateFile(path);
//			return;
//		}
//		else if (path != rootPath) {
//			filesystem::path parentPath = node.parent;
//			parent = Node::readFile(parentPath, *this);
//
//			filesystem::path siblingPath = (parent.left == path) ? parent.right : parent.left;
//			sibling = Node::readFile(siblingPath, *this);
//
//			// Case 1: Sibling is RED
//			if (siblingPath != "NULL" && sibling.color == RED) {
//				parent.color = RED;
//				sibling.color = BLACK;
//
//				parent.updateFile(parentPath);
//				sibling.updateFile(siblingPath);
//
//				if (sibling.data > parent.data) {
//					rotateLeft(parentPath);
//				}
//				else {
//					rotateRight(parentPath);
//				}
//
//				fixDebt(path);
//			}
//
//			// Case 2: Sibling is BLACK
//			else if (sibling.color == BLACK) {
//				filesystem::path leftNephewPath = sibling.left;
//				cout << leftNephewPath << endl;
//				filesystem::path rightNephewPath = sibling.right;
//				cout << rightNephewPath << endl;
//				Node leftNephew = (leftNephewPath != "NULL") ? Node::readFile(leftNephewPath, *this) : Node();
//				Node rightNephew = (rightNephewPath != "NULL") ? Node::readFile(rightNephewPath, *this) : Node();
//
//				// Case 2a: One of the sibling's children is RED
//				if ((leftNephewPath != "NULL" && leftNephew.color == RED) ||
//					(rightNephewPath != "NULL" && rightNephew.color == RED)) {
//
//					// LL Case
//					if (sibling.data < parent.data && leftNephewPath != "NULL" && leftNephew.color == RED) {
//						leftNephew.color = BLACK;
//						sibling.color = parent.color;
//						parent.color = BLACK;
//
//						leftNephew.updateFile(leftNephewPath);
//						sibling.updateFile(siblingPath);
//						parent.updateFile(parentPath);
//
//						rotateRight(parentPath);
//					}
//					// RR Case
//					else if (sibling.data > parent.data && rightNephewPath != "NULL" && rightNephew.color == RED) {
//						rightNephew.color = BLACK;
//						sibling.color = parent.color;
//						parent.color = BLACK;
//
//						rightNephew.updateFile(rightNephewPath);
//						sibling.updateFile(siblingPath);
//						parent.updateFile(parentPath);
//
//						rotateLeft(parentPath);
//					}
//					// LR Case
//					else if (sibling.data < parent.data && rightNephewPath != "NULL" && rightNephew.color == RED) {
//						rightNephew.color = BLACK;
//						sibling.color = RED;
//
//						rightNephew.updateFile(rightNephewPath);
//						sibling.updateFile(siblingPath);
//
//						rotateLeft(siblingPath);
//
//						leftNephew = Node::readFile(sibling.left, *this);
//						leftNephew.color = BLACK;
//						sibling.color = parent.color;
//						parent.color = BLACK;
//
//						leftNephew.updateFile(sibling.left);
//						sibling.updateFile(siblingPath);
//						parent.updateFile(parentPath);
//
//						rotateRight(parentPath);
//					}
//					// RL Case
//					else if (sibling.data > parent.data && leftNephewPath != "NULL" && leftNephew.color == RED) {
//						leftNephew.color = BLACK;
//						sibling.color = RED;
//
//						leftNephew.updateFile(leftNephewPath);
//						sibling.updateFile(siblingPath);
//
//						rotateRight(siblingPath);
//
//						rightNephew = Node::readFile(sibling.right, *this);
//						rightNephew.color = BLACK;
//						sibling.color = parent.color;
//						parent.color = BLACK;
//
//						rightNephew.updateFile(sibling.right);
//						sibling.updateFile(siblingPath);
//						parent.updateFile(parentPath);
//
//						rotateLeft(parentPath);
//					}
//				}
//				// Case 2b: Both of sibling's children are BLACK
//				else {
//					sibling.color = RED;
//					sibling.updateFile(siblingPath);
//
//					if (parent.color == RED) {
//						parent.color = BLACK;
//						parent.updateFile(parentPath);
//					}
//					else if (parent.color == BLACK && parentPath != rootPath)
//					{
//						fixDebt(parentPath);
//					}
//				}
//			}
//		}
//		if (path == rootPath) {
//			node.color = BLACK;
//			node.updateFile(path);
//			return;
//		}
//		if (path != "NULL" && node.debt) {
//			if (parent.left == path)
//				parent.left = "NULL";
//			else
//				parent.right = "NULL";
//			parent.updateFile(node.parent);
//			removeFile(path);
//			path = "NULL";
//			return;
//		}
//	}
//
//	void fixOrientation_Deletion(filesystem::path& path, bool hasDebt) {
//		if (path == "NULL") return;
//		Node node = Node::readFile(path, *this);
//		if (node.color == RED) {
//			node.color = BLACK;
//			node.updateFile(path);
//			return;
//		}
//		else if (path != rootPath && hasDebt)
//		{
//			fixDebt(path);
//		}
//	}
//	void removeNode(filesystem::path& path, const T& data, const long long& rowIndex) {
//		if (path.empty() || path == "NULL")
//		{
//			return;
//		}
//		Node node = Node::readFile(path, *this);
//		if (data < node.data) {
//			removeNode(node.left, data, rowIndex);
//		}
//		else if (data > node.data) {
//			removeNode(node.right, data, rowIndex);
//		}
//		// found Node
//		else {
//			if (node.frequency > 1) {
//				bool found = 0;
//				for (int a = 0; a < node.rowIndexes.getCurr(); a++)
//				{
//					if (node.rowIndexes[a] == rowIndex)
//					{
//						node.rowIndexes.Destroy(a);
//						found = 1;
//						break;
//					}
//				}
//				if (found)
//				{
//					node.frequency--;
//					node.updateFile(path);
//				}
//				return;
//			}
//			int numofChildren = 0;
//			if (node.left != "NULL") numofChildren++;
//			if (node.right != "NULL") numofChildren++;
//			if (numofChildren <= 1) {
//				// double debt case
//				if ((node.left != "NULL" && node.right == "NULL") ||
//					(node.right != "NULL" && node.left == "NULL") ||
//					node.right == "NULL" && node.left == "NULL") {
//					if (node.color == BLACK) {
//						if (node.left == "NULL" && node.right == "NULL") {
//							node.debt = true;
//							node.updateFile(path);
//						}
//						else if (node.left != "NULL") {
//							Node temp = Node::readFile(node.left, *this);
//							if (temp.color == BLACK) {
//								node.debt = true;
//								node.updateFile(path);
//							}
//						}
//						else if (node.right != "NULL") {
//							Node temp = Node::readFile(node.right, *this);
//							if (temp.color == BLACK) {
//								node.debt = true;
//								node.updateFile(path);
//							}
//						}
//					}
//				}
//				// No children
//				if (node.left == "NULL" && node.right == "NULL") {
//					if (path == rootPath) {
//						path = "NULL";
//						return;
//					}
//					else if (node.color == RED)
//					{
//						filesystem::path parentPath = node.parent;
//						Node parent = Node::readFile(parentPath, *this);
//						if (rootPath != "NULL") {
//							if (parent.left == path) {
//								parent.left = "NULL";
//							}
//							else {
//								parent.right = "NULL";
//							}
//							parent.updateFile(parentPath);
//						}
//						removeFile(path);
//						path = "NULL";
//						return;
//					}
//					fixOrientation_Deletion(path, node.debt);
//					cout << path << endl;
//					return;
//					/*removeFile(path);
//					return;*/
//				}
//				// 1 children
//				else if (node.left == "NULL") {
//					if (node.right != "NULL")
//					{
//						Node right = Node::readFile(node.right, *this);
//						right.parent = node.parent;
//						right.updateFile(node.right);
//					}
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.left == path ? parent.left = node.right : parent.right = node.right;
//						parent.updateFile(node.parent);
//					}
//
//					fixOrientation_Deletion(node.right, node.debt);
//					removeFile(path);
//					path = "NULL";
//
//				}
//				else if (node.right == "NULL") {
//					if (node.left != "NULL")
//					{
//						Node left = Node::readFile(node.left, *this);
//						left.parent = node.parent;
//						left.updateFile(node.left);
//					}
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.right == path ? parent.right = node.left : parent.left = node.left;
//						parent.updateFile(node.parent);
//					}
//					fixOrientation_Deletion(node.left, node.debt);
//					removeFile(path);
//					path = "NULL";
//				}
//			}
//			else {
//				// both child exist
//				if (node.left != "NULL" && node.right != "NULL") {
//					Node successor = Node::readFile(node.left, *this);
//					filesystem::path successorPath = node.left;
//					while (successor.right != "NULL") {
//						successorPath = successor.right;
//						successor = Node::readFile(successor.right, *this);
//					}
//					node.data = successor.data;
//					node.frequency = successor.frequency;
//					node.rowIndexes = successor.rowIndexes;
//					node.hash = successor.hash;
//					node.updateFile(path);
//					filesystem::path updatedPath = createPath(successor.data);
//					successor.frequency = 1;
//					successor.updateFile(successorPath);
//					removeNode(node.left, successor.data, rowIndex);
//
//					node = Node::readFile(path, *this);
//					filesystem::rename(path, updatedPath);
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
//						parent.updateFile(node.parent);
//					}
//					if (node.left != "NULL")
//					{
//						Node left = Node::readFile(node.left, *this);
//						left.parent = updatedPath;
//						left.updateFile(node.left);
//					}
//					if (node.right != "NULL")
//					{
//						Node right = Node::readFile(node.right, *this);
//						right.parent = updatedPath;
//						right.updateFile(node.right);
//					}
//					path = updatedPath;
//				}
//			}
//		}
//	}
//	void inorderPrint(const filesystem::path& path, int depth = 0)
//	{
//		if (path.empty() || path == "NULL")
//		{
//			for (int a = 0; a < depth; a++)
//			{
//				cout << '\t';
//			}
//			cout << "-" << endl;
//			return;
//		}
//		Node node = Node::readFile(path, *this);
//		inorderPrint(node.right, depth + 1);
//		for (int a = 0; a < depth; a++)
//		{
//			cout << '\t';
//		}
//		cout << node.data << "(" << node.color << " , " << node.frequency << ")" << endl;
//		inorderPrint(node.left, depth + 1);
//	}
//
//	Node helperSearch(const filesystem::path& root, const T& value) {
//		if (root == "NULL") {
//			return Node();
//		}
//
//		Node currentNode = Node::readFile(root, *this);
//
//		if (value < currentNode.data) {
//			return helperSearch(currentNode.left, value);
//		}
//		else if (value > currentNode.data) {
//			return helperSearch(currentNode.right, value);
//		}
//		else {
//			return currentNode;
//		}
//	}
//public:
//	filesystem::path Root()const { return rootPath; }
//	RedBlackTree()
//	{}
//	RedBlackTree(filesystem::path branchPath)
//	{
//		this->branchPath = branchPath;
//		this->folderPath = branchPath;
//		this->rootPath = "NULL";
//		this->folderPath /= "TREE";
//		if (!filesystem::exists(this->folderPath))
//		{
//			filesystem::create_directories(this->folderPath);
//			filesystem::path nodesPath = this->folderPath / "NODES";
//			filesystem::create_directories(nodesPath);
//		}
//	}
//
//	RedBlackTree(bool loadTreeFromBranch, filesystem::path branchPath)
//	{
//		if (loadTreeFromBranch)
//		{
//			loadFromBranch(branchPath);
//		}
//	}
//	//===================================== UI Functions ==========================================
//	void insert(const T& value, const long long& rowIndex) {
//		insertNode(this->rootPath, value, rowIndex);
//	}
//
//	void remove(const T& value, const long long& rowIndex) {
//		if (rootPath == "NULL") {
//			throw runtime_error("Tree is Empty.");
//		}
//		removeNode(this->rootPath, value, rowIndex);
//	}
//	void print() {
//		inorderPrint(rootPath);
//	}
//	Vector<long long>search(const T& data)
//	{
//		Node node = this->helperSearch(this->rootPath, data);
//		if (node.rowIndexes.getCurr() == 0)
//		{
//			cout << "No instances of key: " << data << " exist." << endl;
//			return Vector<long long>();
//		}
//		else
//		{
//			return node.rowIndexes;
//		}
//	}
//
//	void saveDataToFile()
//	{
//		ofstream file;
//		filesystem::path path = folderPath;
//		path += "\\TREE_DATA.txt";
//		file.open(path);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'RB_DATA.txt\' for writing.");
//		file << rootPath << '\n';
//		file << folderPath << '\n';
//		file << branchPath << '\n';
//		file.close();
//	}
//	void loadFromBranch(path branchPath)
//	{
//		branchPath /= "TREE";
//		branchPath /= "TREE_DATA.txt";
//		if (!exists(branchPath))
//			throw runtime_error("File to load tree from doesnt exist.");
//		ifstream file(branchPath);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'RB_DATA.txt\' for reading.");
//		file >> rootPath;
//		file >> folderPath;
//		file >> this->branchPath;
//		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//		file.close();
//	}
//
//
//};
//
//template <class T>
//class AVL : public ParentTree<T>
//{
//private:
//
//	//===================================== AVL Node ==========================================
//	struct Node
//	{
//		T data;
//		int height;
//		int frequency;
//		Vector<long long> rowIndexes;
//		String hash;
//		filesystem::path left;	 //left child path
//		filesystem::path right;	 //right child path
//		filesystem::path parent; //parent path
//
//		Node(T data = T()) : data(data), height(0), frequency(1), hash("InsertHashHere"), left("NULL"), right("NULL"), parent("NULL")
//		{}
//
//		void updateFile(const filesystem::path& path)
//		{
//			if (path == "NULL")
//				throw runtime_error("Attempting to access empty path.");
//
//			ofstream file;
//			file.open(path);
//			if (!file.is_open())
//				throw runtime_error("Cannot open file for writing.");
//
//			file << this->data << '\n';
//			file << this->height << '\n';
//			file << this->frequency << '\n';
//			for (int a = 0; a < this->frequency; a++)
//			{
//				if (a > 0)
//					file << ' ';
//				file << this->rowIndexes[a];
//			}
//			file << '\n';
//			file << this->hash << '\n';
//			file << (this->left == "NULL" ? "NULL" : makeRelative(this->left)) << '\n';
//			file << (this->right == "NULL" ? "NULL" : makeRelative(this->right)) << '\n';
//			file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';
//
//			file.close();
//		}
//
//		static Node readFile(const filesystem::path& path, const AVL& merc)
//		{
//			if (path == "NULL")
//				throw runtime_error("Attempting to access empty path.");
//
//			ifstream file;
//			file.open(path);
//			if (!file.is_open())
//				throw runtime_error("Cannot open file for reading.");
//
//			Node node;
//			if constexpr (is_same<T, String>::value)
//			{
//				getline(file, node.data);
//				file >> node.height;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//				file >> node.frequency;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			}
//			else
//			{
//				file >> node.data;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//				file >> node.height;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//				file >> node.frequency;
//				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			}
//			char delim;
//			long long index;
//			for (int a = 0; a < node.frequency; a++)
//			{
//				file >> index;
//				node.rowIndexes.push_back(index);
//			}
//			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			getline(file, node.hash);
//			filesystem::path temp;
//
//			file >> temp;
//			if (temp == "NULL")
//				node.left = "NULL";
//			else
//			{
//				node.left = merc.branchPath;
//				node.left /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.right = "NULL";
//			else
//			{
//				node.right = merc.branchPath;
//				node.right /= temp;
//			}
//
//			file >> temp;
//			if (temp == "NULL")
//				node.parent = "NULL";
//			else
//			{
//				node.parent = merc.branchPath;
//				node.parent /= temp;
//			}
//
//			file.close();
//			return node;
//		}
//	};
//
//	// ===================================== AVL functions ==========================================
//
//		//generate a filePath based on the value of a node
//	filesystem::path generateFilePath(const T& value)
//	{
//		// Construct the file path
//		filesystem::path filePath = folderPath / "NODES";
//		if constexpr (is_same<T, String>::value)
//		{
//			filePath /= value.getData();
//		}
//		else
//		{
//			filePath /= value;
//		}
//		filePath += ".txt";
//		return filePath;
//	}
//
//	bool removeFile(filesystem::path& path)
//	{
//		if (filesystem::exists(path))
//		{
//			filesystem::remove(path);
//			return true;
//		}
//		return false;
//
//	}
//
//	//get height of node
//	int Height(const filesystem::path& path)
//	{
//		if (path.empty() || path == "NULL")
//			return -1;
//		else
//		{
//			return Node::readFile(path, *this).height;
//		}
//	}
//
//	//NOTE : updates height in file
//	void updateNodeHeight(const filesystem::path& path)
//	{
//		if (path.empty() || path == "NULL")
//			return;
//
//		Node node = Node::readFile(path, *this);
//		int leftHeight = Height(node.left);
//		int rightHeight = Height(node.right);
//
//		node.height = max(leftHeight, rightHeight) + 1;
//		node.updateFile(path);
//		return;
//	}
//
//	//BF = Right - Left
//	int balanceFactor(const filesystem::path& path)
//	{
//		Node node = Node::readFile(path, *this);
//		int leftHeight = Height(node.left);
//		int rightHeight = Height(node.right);
//
//		return rightHeight - leftHeight;
//	}
//
//	//========= rotations ===========
//
//	//INPUT: PATH
//	//automatically updates parent, old and new pivots
//	void rotateRight(filesystem::path& path)
//	{
//		Node mainNode = Node::readFile(path, *this);
//		Node leftNode = Node::readFile(mainNode.left, *this);
//		filesystem::path leftNodePath = mainNode.left;
//		filesystem::path leftNodeKaRightPath = leftNode.right;
//
//		//attach old pivot with new pivot's left subtree
//		mainNode.left = leftNodeKaRightPath;
//		if (leftNodeKaRightPath != "NULL")
//		{
//			Node leftNodesRight_NODE = Node::readFile(leftNodeKaRightPath, *this);
//			leftNodesRight_NODE.parent = path;
//			leftNodesRight_NODE.updateFile(leftNodeKaRightPath);
//		}
//
//		//attach new pivot with old pivot's parent
//		leftNode.parent = mainNode.parent;
//
//		//put old pivot at new pivot's left child
//		leftNode.right = path;
//		mainNode.parent = leftNodePath;
//
//		//update heights
//		mainNode.updateFile(path);
//		leftNode.updateFile(leftNodePath);
//		updateNodeHeight(path);
//		updateNodeHeight(leftNodePath);
//
//		//update the parent if it exists
//		if (leftNode.parent != "NULL")
//		{
//			Node parentNode = Node::readFile(leftNode.parent, *this);
//			parentNode.left == path ? parentNode.left = leftNodePath : parentNode.right = leftNodePath;
//
//			parentNode.updateFile(leftNode.parent);
//			updateNodeHeight(leftNode.parent);
//		}
//		path = leftNodePath;
//	}
//
//
//	//INPUT: PATH
//	//automatically updates parent, old and new pivots
//	void rotateLeft(filesystem::path& path)
//	{
//		Node mainNode = Node::readFile(path, *this);
//		Node rightNode = Node::readFile(mainNode.right, *this);
//		filesystem::path rightNodePath = mainNode.right;
//		filesystem::path rightNodeKaLeftPath = rightNode.left;
//
//		//attach old pivot with new pivot's left subtree
//		mainNode.right = rightNodeKaLeftPath;
//		if (rightNodeKaLeftPath != "NULL")
//		{
//			Node rightNodesleft_NODE = Node::readFile(rightNodeKaLeftPath, *this);
//			rightNodesleft_NODE.parent = path;
//			rightNodesleft_NODE.updateFile(rightNodeKaLeftPath);
//		}
//
//		//attach new pivot with old pivot's parent
//		rightNode.parent = mainNode.parent;
//
//		//put old pivot at new pivot's left child
//		rightNode.left = path;
//		mainNode.parent = rightNodePath;
//
//		//update heights
//		mainNode.updateFile(path);
//		rightNode.updateFile(rightNodePath);
//		updateNodeHeight(path);
//		updateNodeHeight(rightNodePath);
//
//		//update the parent if it exists
//		if (rightNode.parent != "NULL")
//		{
//			Node parentNode = Node::readFile(rightNode.parent, *this);
//			parentNode.left == path ? parentNode.left = rightNodePath : parentNode.right = rightNodePath;
//
//			parentNode.updateFile(rightNode.parent);
//			updateNodeHeight(rightNode.parent);
//		}
//		path = rightNodePath;
//
//	}
//
//	//returns 1 if rotations occured
//	bool balanceNode(filesystem::path& path)
//	{
//		Node node = Node::readFile(path, *this);
//		int BF = balanceFactor(path);
//
//		//right heavy
//		if (BF == 2)
//		{
//			int rightBF = balanceFactor(node.right);
//
//			if (rightBF == 1 || rightBF == 0)
//			{
//				rotateLeft(path);
//			}
//			else if (rightBF == -1)
//			{
//				rotateRight(node.right);
//				rotateLeft(path);
//			}
//			return 1;
//		}
//		//left heavy
//		else if (BF == -2)
//		{
//			int leftBF = balanceFactor(node.left);
//
//			if (leftBF == -1 || leftBF == 0)
//			{
//				rotateRight(path);
//			}
//			else if (leftBF == 1)
//			{
//				rotateLeft(node.left);
//				rotateRight(path);
//			}
//			return 1;
//		}
//
//		return 0;
//	}
//
//	//NOTE: updates path sent as parameter
//	void helperInsert(filesystem::path& path, const filesystem::path& parentPath, const T& data, const long long& rowIndex)
//	{
//		if (path == "NULL")
//		{
//			filesystem::path newFilePath = generateFilePath(data);
//			Node newNode(data);
//			newNode.parent = parentPath;
//			newNode.rowIndexes.push_back(rowIndex);
//			path = newFilePath;
//			newNode.updateFile(newFilePath);
//			return;
//		}
//		else
//		{
//			Node current = Node::readFile(path, *this);
//			if (data < current.data)
//			{
//				helperInsert(current.left, path, data, rowIndex);
//			}
//			else if (data > current.data)
//			{
//				helperInsert(current.right, path, data, rowIndex);
//			}
//			else if (data == current.data)
//			{
//				current.frequency++;
//				current.rowIndexes.push_back(rowIndex);
//				current.updateFile(path);
//				return;
//			}
//			current.updateFile(path);
//			updateNodeHeight(path);
//
//			int BF = balanceFactor(path);
//			if (BF == 2 || BF == -2)
//			{
//				balanceNode(path);
//			}
//		}
//	}
//
//	//Updates path sent as para
//	void helperRemove(filesystem::path& path, const T& data, const long long& rowIndex)
//	{
//		//didnt find element
//		if (path.empty() || path == "NULL")
//		{
//			return;
//		}
//
//		Node node = Node::readFile(path, *this);
//
//		//find the element
//		if (data < node.data)
//		{
//			helperRemove(node.left, data, rowIndex);
//		}
//		else if (data > node.data)
//		{
//			helperRemove(node.right, data, rowIndex);
//		}
//		//element found
//		else
//		{
//			//only decrement frequency if it is >1
//			if (node.frequency > 1)
//			{
//				bool found = 0;
//				for (int a = 0; a < node.rowIndexes.getCurr(); a++)
//				{
//					if (node.rowIndexes[a] == rowIndex)
//					{
//						node.rowIndexes.Destroy(a);
//						found = 1;
//						break;
//					}
//				}
//				if (found)
//				{
//					node.frequency--;
//					node.updateFile(path);
//				}
//				return;
//			}
//			else
//			{
//				//have to completely remove file
//
//				//Case 1: No left child
//				if (node.left == "NULL")
//				{
//					if (node.right != "NULL")
//					{
//						Node right = Node::readFile(node.right, *this);
//						right.parent = node.parent;
//						right.updateFile(node.right);
//					}
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.left == path ? parent.left = node.right : parent.right = node.right;
//						parent.updateFile(node.parent);
//						updateNodeHeight(node.parent);
//					}
//					removeFile(path);
//					path = node.right;
//					return;
//				}
//
//				//Case 2: No right child
//				else if (node.right == "NULL")
//				{
//					if (node.left != "NULL")
//					{
//						Node left = Node::readFile(node.left, *this);
//						left.parent = node.parent;
//						left.updateFile(node.left);
//					}
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.left == path ? parent.left = node.left : parent.right = node.left;
//						parent.updateFile(node.parent);
//						updateNodeHeight(node.parent);
//					}
//					removeFile(path);
//					path = node.left;
//					return;
//				}
//
//				//Case 3: Both childs exist
//				else if (node.right != "NULL" && node.left != "NULL")
//				{
//					//find inorder successor
//					Node successor = Node::readFile(node.right, *this);
//					filesystem::path successorPath = node.right;
//
//					while (successor.left != "NULL")
//					{
//						successorPath = successor.left;
//						successor = Node::readFile(successor.left, *this);
//					}
//
//					//replace nodes data with successor data
//					node.data = successor.data;
//					node.frequency = successor.frequency;
//					node.rowIndexes = successor.rowIndexes;
//					node.hash = successor.hash;
//					node.updateFile(path);
//					filesystem::path updatedPath = generateFilePath(successor.data);
//
//					//delete successor from right subtree
//					successor.frequency = 1;
//					successor.updateFile(successorPath);
//					helperRemove(node.right, successor.data, rowIndex);
//
//					//rename the node that just got replaced and update the new path in all neighbors
//					node = Node::readFile(path, *this);
//					filesystem::rename(path, updatedPath);
//					if (node.parent != "NULL")
//					{
//						Node parent = Node::readFile(node.parent, *this);
//						parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
//						parent.updateFile(node.parent);
//					}
//					if (node.left != "NULL")
//					{
//						Node left = Node::readFile(node.left, *this);
//						left.parent = updatedPath;
//						left.updateFile(node.left);
//					}
//					if (node.right != "NULL")
//					{
//						Node right = Node::readFile(node.right, *this);
//						right.parent = updatedPath;
//						right.updateFile(node.right);
//					}
//					path = updatedPath;
//				}
//			}
//		}
//		//rolling back after deletion, balance any imbalanced nodes
//		int BF = balanceFactor(path);
//		if (BF >= 2 || BF <= -2)
//		{
//			balanceNode(path);
//		}
//	}
//
//	void inorderPrint(const filesystem::path& path, int depth = 0)
//	{
//		if (path.empty() || path == "NULL")
//		{
//			for (int a = 0; a < depth; a++)
//			{
//				cout << '\t';
//			}
//			cout << "-" << endl;
//			return;
//		}
//		Node node = Node::readFile(path, *this);
//		inorderPrint(node.right, depth + 1);
//		for (int a = 0; a < depth; a++)
//		{
//			cout << '\t';
//		}
//		cout << node.data << '(' << node.height << ',' << node.frequency << ')' << endl;
//		inorderPrint(node.left, depth + 1);
//	}
//
//	void helperF(filesystem::path path, int& f)
//	{
//		if (path == "NULL")
//			return;
//		Node node = Node::readFile(path, *this);
//		helperF(node.left, f);
//		f += node.frequency;
//		helperF(node.right, f);
//	}
//
//	Node helperSearch(const filesystem::path& root, const T& value) {
//		if (root == "NULL") {
//			return Node();
//		}
//
//		Node currentNode = Node::readFile(root, *this);
//
//		if (value < currentNode.data) {
//			return helperSearch(currentNode.left, value);
//		}
//		else if (value > currentNode.data) {
//			return helperSearch(currentNode.right, value);
//		}
//		else {
//			return currentNode;
//		}
//	}
//public:
//
//	AVL()
//	{}
//	AVL(filesystem::path branchPath)
//	{
//		this->branchPath = branchPath;
//		this->folderPath = branchPath;
//		this->rootPath = "NULL";
//		this->folderPath /= "TREE";
//		if (!filesystem::exists(this->folderPath))
//		{
//			filesystem::create_directories(this->folderPath);
//			filesystem::path nodesPath = this->folderPath / "NODES";
//			filesystem::create_directories(nodesPath);
//		}
//	}
//	AVL(bool loadTreeFromBranch, filesystem::path branchPath)
//	{
//		if (loadTreeFromBranch)
//		{
//			loadFromBranch(branchPath);
//		}
//	}
//
//	void insert(const T& data, const long long& rowIndex) override
//	{
//		helperInsert(rootPath, "NULL", data, rowIndex);
//	}
//	void remove(const T& data, const long long& rowIndex) override
//	{
//		helperRemove(rootPath, data, rowIndex);
//	}
//
//	void print() override
//	{
//		cout << "---------------------------------------------------- " << endl;
//		inorderPrint(rootPath);
//	}
//
//	//saves path of root into a file
//	void saveDataToFile()
//	{
//		ofstream file;
//		filesystem::path path = folderPath;
//		path += "\\TREE_DATA.txt";
//		file.open(path);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'AVL_DATA.txt\' for writing.");
//		file << rootPath << '\n';
//		file << folderPath << '\n';
//		file << branchPath << '\n';
//		file.close();
//	}
//	void loadFromBranch(filesystem::path branchPath)
//	{
//		branchPath /= "TREE";
//		branchPath /= "TREE_DATA.txt";
//		if (!exists(branchPath))
//			throw runtime_error("File to load tree from doesnt exist.");
//		ifstream file(branchPath);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'AVL_DATA.txt\' for reading.");
//		file >> rootPath;
//		file >> folderPath;
//		file >> this->branchPath;
//		file.close();
//	}
//	Vector<long long>search(const T& data)
//	{
//		Node node = this->helperSearch(this->rootPath, data);
//		if (node.rowIndexes.getCurr() == 0)
//		{
//			cout << "No instances of key: " << data << " exist." << endl;
//			return Vector<long long>();
//		}
//		else
//		{
//			return node.rowIndexes;
//		}
//	}
//
//
//};
//
///*
//		B-Tree Class that inherits from the ParentTree class
//		The class holds search insertion and deletion in B-Tree
//		It composes of struct Key and struct Node that contain all the necassary parts and functions
//*/
//
//// pair struct allowing for 3 values
//template <class T, class U, class V>
//struct Pair {
//	T first;
//	U second;
//	V third;
//	Pair(T first = T(), U second = U(), V third = V()) : first(first), second(second), third(third) {}
//};
//
//template <class T>
//class Btree : public ParentTree<T>
//{
//	//===================================== Key ==========================================
//
//	struct Key {
//		T key;
//		Vector<long long> indexes;
//		// to compare keys
//		bool operator >(const Key& other) {
//			if (this->key > other.key)
//				return true;
//			return false;
//		}
//		bool operator<(const Key& other) {
//			if (this->key < other.key)
//				return true;
//			return false;
//		}
//	};
//
//	//===================================== B-Tree Node ==========================================
//
//	struct Node {
//		// parent path
//		filesystem::path parent;
//		Vector<path> keyPaths; // paths to the keys
//		Vector<Key> keys; // keys in the node
//		Vector<path> childrenPaths;
//		bool isLeaf; // is the node a leaf node
//
//		Node(bool isLeaf = true) : isLeaf(isLeaf), parent("NULL") {} // constructor
//		// function to save the node to a file
//		void saveToFile(const path& path) {
//			// if the path is empty or NULL throw an exception
//			if (path.empty() || path == "NULL") {
//				throw runtime_error("File path not valid");
//			}
//			ofstream file(path);
//			if (!file.is_open()) {
//				// unable to open file
//				cout << path << endl;
//				throw runtime_error("Unable to open file for saving node.");
//			}
//			// save key count
//			file << keys.getCurr() << '\n';
//			// save keys
//			for (int i = 0; i < keys.getCurr(); ++i) {
//				file << keys[i].key << '\n';
//				file << keys[i].indexes.getCurr() << '\n';
//				for (int j = 0; j < keys[i].indexes.getCurr(); ++j) {
//					file << keys[i].indexes[j];
//					if (j < keys[i].indexes.getCurr() - 1) {
//						file << ',';
//					}
//				}
//				if (keys[i].indexes.getCurr() > 0)
//					file << '\n';
//			}
//
//			// save parent
//			// MakeRelative function allows the code to be independent of the file path
//			file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';
//
//			// save children count and paths
//			file << childrenPaths.getCurr() << '\n';
//			for (int i = 0; i < childrenPaths.getCurr(); ++i) {
//				file << makeRelative(childrenPaths[i]) << '\n';
//			}
//			file.close();
//		}
//		// function to load the node from a file
//		static Node LoadFromFile(const path& nodePath, const Btree& merc) {
//			if (!exists(nodePath)) {
//				cout << nodePath << endl;
//				throw runtime_error("Node file does not exist.");
//			}
//			ifstream file(nodePath);
//			if (!file.is_open()) {
//				throw runtime_error("Unable to open file for writing.");
//			}
//			Node loadedNode;
//			int keyCount;
//			file >> keyCount;
//			file.ignore(numeric_limits<streamsize>::max(), '\n');
//
//			for (int i = 0; i < keyCount; ++i) {
//				Key key;
//				file >> key.key; // key
//
//				int numIndexes;
//				file >> numIndexes;
//				file.ignore(numeric_limits<streamsize>::max(), '\n');
//
//				for (int j = 0; j < numIndexes; ++j) {
//					int index;
//					file >> index;
//					if (file.peek() == ',') {
//						file.ignore(); // ignore comma
//					}
//					key.indexes.push_back(index);
//				}
//				file.ignore(numeric_limits<streamsize>::max(), '\n');
//				loadedNode.keys.push_back(key);
//			}
//			filesystem::path temp;
//			file >> temp;
//			if (temp != "NULL") {
//				// this allows our relative branching to work properly
//				loadedNode.parent = merc.branchPath;
//				loadedNode.parent /= temp;
//			}
//			else {
//				loadedNode.parent = "NULL";
//			}
//
//			int numChildren;
//			file >> numChildren;
//			file.ignore(numeric_limits<streamsize>::max(), '\n');
//
//			for (int i = 0; i < numChildren; ++i) {
//				file >> temp;
//				filesystem::path childPath = merc.branchPath;
//				childPath /= temp;
//				loadedNode.childrenPaths.push_back(childPath);
//			}
//
//			loadedNode.isLeaf = (numChildren == 0);
//
//			file.close();
//			return loadedNode;
//
//		}
//	};
//
//	//===================================== B-Tree Functions ==========================================
//
//	// function to search for a key in the tree
//	Pair<filesystem::path, int, int> searchNode(const T& value) {
//		if (rootPath == "NULL") {
//			return Pair<filesystem::path, int, int>();
//		}
//
//		filesystem::path currPath = rootPath;
//		int currIndex = 0;
//		int currKeyIndex = -1;
//		Node currNode = Node::LoadFromFile(currPath, *this);
//
//		while (!currNode.isLeaf) {
//			currIndex = currNode.keys.getCurr();
//
//			for (int a = 0; a < currNode.keys.getCurr(); a++) {
//				if (value == currNode.keys[a].key) {
//					currIndex = a;
//					currKeyIndex = a;
//					return Pair<filesystem::path, int, int>(currPath, -1, currKeyIndex);
//				}
//				if (value < currNode.keys[a].key) {
//					currIndex = a;
//					currKeyIndex = a;
//					break;
//				}
//			}
//			currPath = currNode.childrenPaths[currIndex];
//			currNode = Node::LoadFromFile(currPath, *this);
//		}
//
//		for (int a = 0; a < currNode.keys.getCurr(); a++) {
//			if (value == currNode.keys[a].key) {
//				currKeyIndex = a;
//				break;
//			}
//		}
//		return Pair<filesystem::path, int, int>(currPath, currIndex, currKeyIndex);
//	}
//	// split nodes when the node is full
//	void splitNodes(Node& node, filesystem::path& currPath) {
//
//		int mid = node.keys.getCurr() / 2;
//		Key shiftedKey = node.keys[mid];
//		Node leftNode, rightNode;
//		// paths for the new nodes
//		filesystem::path leftNodePath = folderPath / "NODES" / ("DISK_" + to_string(nodeCount) + ".txt");
//		nodeCount++;
//		filesystem::path rightNodePath = folderPath / "NODES" / ("DISK_" + to_string(nodeCount) + ".txt");
//		nodeCount++;
//		// seperating keys
//		for (int i = 0; i < mid; ++i) {
//			leftNode.keys.push_back(node.keys[i]);
//		}
//
//		for (int i = mid + 1; i < node.keys.getCurr(); ++i) {
//			rightNode.keys.push_back(node.keys[i]);
//		}
//
//		node.keys.clear();
//		// if node is not leaf seperate the children too
//		if (!node.isLeaf) {
//			// for left child
//			for (int i = 0; i <= mid; ++i) {
//				path oldChildPath = node.childrenPaths[i];
//				Node leftChild = Node::LoadFromFile(oldChildPath, *this);
//				leftChild.parent = leftNodePath;
//				leftChild.saveToFile(oldChildPath);
//				leftNode.childrenPaths.push_back(node.childrenPaths[i]);
//			}
//			// for right child
//			for (int i = mid + 1; i < node.childrenPaths.getCurr(); ++i) {
//				path oldChildPath = node.childrenPaths[i];
//				Node rightChild = Node::LoadFromFile(oldChildPath, *this);
//				rightChild.parent = rightNodePath;
//				rightChild.saveToFile(oldChildPath);
//				rightNode.childrenPaths.push_back(node.childrenPaths[i]);
//			}
//
//			node.childrenPaths.clear();
//		}
//		// if the node is root
//		if (currPath == rootPath || (!node.isLeaf && node.parent == "NULL")) {
//			// create a new root
//			Node newRoot;
//			newRoot.isLeaf = false;
//			filesystem::path newRootPath = folderPath / "NODES" / "ROOT.txt";
//
//			// update children
//			if (exists(newRootPath)) {
//				filesystem::remove(newRootPath);
//			}
//			// save the left and right nodes
//			leftNode.parent = currPath;
//			leftNode.saveToFile(leftNodePath);
//
//			rightNode.parent = currPath;
//			rightNode.saveToFile(rightNodePath);
//
//			// saving the key
//			newRoot.keys.push_back(shiftedKey);
//
//			// saving children
//			newRoot.childrenPaths.push_back(leftNodePath);
//			newRoot.childrenPaths.push_back(rightNodePath);
//			// save the new root
//			newRoot.saveToFile(newRootPath);
//
//			// update the root path
//			rootPath = newRootPath;
//		}
//		// if the node is not root
//		else {
//			// update the parent node
//			Node parentNode = Node::LoadFromFile(node.parent, *this);
//			filesystem::path parentPath = node.parent;
//
//			// takes the inserted key to the parent
//			parentNode.keys.insertSorted(shiftedKey);
//
//			int index = 0;
//			for (int i = 0; i < parentNode.childrenPaths.getCurr(); ++i) {
//				if (parentNode.childrenPaths[i] == currPath) {
//					index = i;
//					break;
//				}
//			}
//			// update the children
//			parentNode.childrenPaths[index] = leftNodePath;
//			parentNode.childrenPaths.inserAt(rightNodePath, index + 1); // updates children paths
//
//			// save the nodes
//			leftNode.parent = node.parent;
//			leftNode.saveToFile(leftNodePath);
//
//			rightNode.parent = node.parent;
//			rightNode.saveToFile(rightNodePath);
//
//			parentNode.saveToFile(node.parent);
//			// split the parent node if it exceeds the degree
//			if (parentNode.keys.getCurr() >= degree) {
//				splitNodes(parentNode, node.parent);
//			}
//			filesystem::remove(currPath);
//		}
//	}
//	// function for insertion
//	void insertNode(filesystem::path& root, const T& value, const long long& rowIndex) {
//		if (root == "NULL") {
//			//initialize the  folder
//			path rootPath = folderPath / "NODES" / "ROOT.txt";
//
//			Node newNode;
//			Key newKey;
//			newKey.key = value;
//			newKey.indexes.push_back(rowIndex);
//			newNode.isLeaf = true;
//			newNode.keys.push_back(newKey);
//
//			//save the root node
//			newNode.saveToFile(rootPath);
//			//update the root path
//			root = rootPath;
//		}
//		else {
//			// Locate the appropriate node for insertion
//			Pair<filesystem::path, int, int> toBeInserted = searchNode(value);
//			Pair<filesystem::path, int, int> exists = searchNode_Deletion(value);
//			filesystem::path currPath = toBeInserted.first;
//			Node node = Node::LoadFromFile(currPath, *this);
//
//			if (exists.second != -1) {
//				node.keys[exists.second].indexes.push_back(rowIndex);
//				node.saveToFile(currPath);
//				return;
//			}
//			// Insert the new key
//			Key newKey;
//			newKey.key = value;
//			newKey.indexes.push_back(rowIndex);
//			node.keys.insertSorted(newKey);
//			node.saveToFile(currPath);
//
//			// Split the node if it exceeds the degree
//			if (node.keys.getCurr() >= degree) {
//				splitNodes(node, currPath);
//			}
//		}
//	}
//	// helper function to remove leaf node
//	void removeLeaf(filesystem::path& path, Node& node, int index) {
//		int minKeys = ceil(degree / 2.0) - 1; // Minimum keys required in a node
//
//		// base case : enough keys can remove without it being less than minKeys
//		if (node.keys.getCurr() > minKeys) {
//			node.keys.Destroy(index);
//			node.saveToFile(path);
//			return;
//		}
//		Node parentNode = Node::LoadFromFile(node.parent, *this);
//		// case 2: borrow from left sibling
//		if (index > 0) {
//			Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1], *this);
//			if (leftSibling.keys.getCurr() > minKeys) {
//				Key borrowedKey = leftSibling.keys[leftSibling.keys.getCurr() - 1];
//				leftSibling.keys.Destroy(leftSibling.keys.getCurr() - 1);
//				node.keys.Destroy(index);
//				node.keys.insertSorted(parentNode.keys[index - 1]);
//
//				// Update parent key
//				parentNode.keys[index - 1] = borrowedKey;
//
//				leftSibling.saveToFile(parentNode.childrenPaths[index - 1]);
//				parentNode.saveToFile(leftSibling.parent);
//				node.saveToFile(path);
//				return;
//			}
//		}
//
//		// case 3: borrow from right sibling
//		if (index < parentNode.childrenPaths.getCurr() - 1) {
//			// borrow from right sibling
//			Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1], *this);
//			if (rightSibling.keys.getCurr() > minKeys) {
//				// borrow from right sibling
//				Key borrowedKey = rightSibling.keys[0];
//				rightSibling.keys.Destroy(0);
//				node.keys.Destroy(index);
//				node.keys.insertSorted(parentNode.keys[index]);
//
//				parentNode.keys[index] = borrowedKey;
//				// save the nodes
//				rightSibling.saveToFile(parentNode.childrenPaths[index + 1]);
//				parentNode.saveToFile(rightSibling.parent);
//				node.saveToFile(path);
//				return;
//			}
//		}
//
//		// case 4: merge with a sibling
//		if (index > 0) {
//			// merge with left sibling
//			Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1], *this);
//			// parentNode.keys.push_back(leftSibling.keys[index - 1]);
//			Key newKey = parentNode.keys[index - 1];
//			leftSibling.keys.push_back(newKey);
//			for (int i = 0; i < node.keys.getCurr(); ++i) {
//				leftSibling.keys.insertSorted(node.keys[i]);
//			}
//			if (!node.isLeaf) {
//				for (int i = 0; i < node.childrenPaths.getCurr(); ++i) {
//					leftSibling.childrenPaths.push_back(node.childrenPaths[i]);
//				}
//			}
//			parentNode.keys.Destroy(index - 1);
//			filesystem::path deletePath = parentNode.childrenPaths[index - 1];
//			parentNode.childrenPaths.Destroy(index - 1);
//			leftSibling.keys.Destroy(index);
//			// save the nodes
//			leftSibling.saveToFile(parentNode.childrenPaths[index - 1]);
//			parentNode.saveToFile(node.parent);
//
//			filesystem::remove(deletePath);
//
//		}
//		else {
//			// merge with right sibling
//			Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1], *this);
//			// parentNode.keys.push_back(rightSibling.keys[0]);
//			Key newKey = parentNode.keys[index];
//			node.keys.push_back(newKey);
//			for (int i = 1; i < rightSibling.keys.getCurr(); ++i) {
//				node.keys.insertSorted(rightSibling.keys[i]);
//			}
//			// If not leaf, also transfer child pointers
//			if (!rightSibling.isLeaf) {
//				for (int i = 0; i < rightSibling.childrenPaths.getCurr(); ++i) {
//					node.childrenPaths.push_back(rightSibling.childrenPaths[i]);
//				}
//			}
//
//			parentNode.childrenPaths.Destroy(index + 1);
//			parentNode.keys.Destroy(index);
//
//			node.saveToFile(parentNode.childrenPaths[index]);
//			parentNode.saveToFile(node.parent);
//
//			filesystem::remove(parentNode.childrenPaths[index + 1]);
//		}
//		// checking if parent node gets messed up
//		if (parentNode.keys.getCurr() < minKeys) {
//			if (parentNode.parent == "NULL") {
//				// If parent is root and has no keys left change root
//				if (parentNode.childrenPaths.getCurr() == 1) {
//					// filesystem::remove(root);
//					Node newRoot = Node::LoadFromFile(parentNode.childrenPaths[0], *this);
//					this->rootPath = folderPath / "ROOT.txt";
//					newRoot.saveToFile(rootPath);
//					filesystem::remove(parentNode.childrenPaths[0]);
//				}
//			}
//			else {
//				// Recursive call to fix the parent node
//				removeLeaf(parentNode.parent, parentNode, index);
//			}
//		}
//	}
//	// helper function to remove internal node
//	void removeInternal(filesystem::path& path, Node& node, int index, T value = T()) {
//		// Minimum keys required in a node
//		int minKeys = ceil(degree / 2.0) - 1;
//
//
//		Node leftSibling = Node::LoadFromFile(node.childrenPaths[index], *this);
//		Node rightSibling = Node::LoadFromFile(node.childrenPaths[index + 1], *this);
//
//		// Case 1: Borrow from left sibling
//		if (leftSibling.keys.getCurr() > minKeys) {
//			Node pre = leftSibling;
//			filesystem::path prePath = node.childrenPaths[index];
//			while (!pre.isLeaf) {
//				pre = Node::LoadFromFile(prePath, *this);
//				prePath = pre.childrenPaths[pre.childrenPaths.getCurr() - 1];
//			}
//			Key newKey = pre.keys.back();
//			node.keys[index] = newKey;
//			node.saveToFile(path);
//
//			removeLeaf(prePath, pre, pre.keys.getCurr() - 1);
//		}
//		// Case 2: Borrow from right sibling
//		else if (rightSibling.keys.getCurr() > minKeys) {
//			Node suc = rightSibling;
//			filesystem::path suckPath = node.childrenPaths[index + 1];
//			while (!suc.isLeaf) {
//				suc = Node::LoadFromFile(suckPath, *this);
//				suckPath = suc.childrenPaths[0];
//			}
//			Key newKey = suc.keys[0];
//			node.keys[index] = newKey;
//			node.saveToFile(path);
//			removeLeaf(suckPath, suc, 0);
//		}
//		// Case 3: Merge with left sibling
//		else {
//			// Key from parent to be merged into left sibling
//			Key mergeKey = node.keys[index];
//			if (mergeKey.key != value)
//				leftSibling.keys.push_back(mergeKey);
//
//			// Move all keys and children from the right sibling to the left sibling
//			for (int i = 0; i < rightSibling.keys.getCurr(); ++i) {
//				leftSibling.keys.push_back(rightSibling.keys[i]);
//			}
//			if (!rightSibling.isLeaf) {
//				for (int i = 0; i < rightSibling.childrenPaths.getCurr(); ++i) {
//					leftSibling.childrenPaths.push_back(rightSibling.childrenPaths[i]);
//
//					// Update the parent reference for the child being moved
//					Node childNode = Node::LoadFromFile(rightSibling.childrenPaths[i], *this);
//					childNode.parent = node.childrenPaths[index]; // Update to leftSibling's file
//					childNode.saveToFile(rightSibling.childrenPaths[i]);
//				}
//			}
//
//			// Remove the merged key and right child path from the parent node
//			node.keys.Destroy(index);
//			filesystem::path rightSiblingPath = node.childrenPaths[index];
//			node.childrenPaths.Destroy(index);
//
//			// Save updated left sibling and parent node
//			leftSibling.saveToFile(node.childrenPaths[index]);
//			node.saveToFile(path);
//
//			// Remove the right sibling file
//			filesystem::remove(rightSiblingPath);
//
//			// Check if the parent node violates the minimum keys condition
//			if (node.keys.getCurr() < minKeys) {
//				if (node.parent != "NULL") {
//					Node parentNode = Node::LoadFromFile(node.parent, *this);
//					int parentIndex = parentNode.childrenPaths.search(path);
//
//					// Recursive call to fix the parent node
//					removeInternal(node.parent, parentNode, parentIndex);
//				}
//				else if (node.keys.getCurr() == 0) {
//					rootPath = node.childrenPaths[index - 1];
//					leftSibling.parent = "NULL";
//					leftSibling.saveToFile(rootPath);
//					filesystem::remove(path);
//				}
//			}
//		}
//	}
//	// helper function to search Node for deletion
//	Pair<filesystem::path, int, int> searchNode_Deletion(const T& value) {
//		// if the tree is empty
//		if (rootPath == "NULL") {
//			return Pair<filesystem::path, int, int>("NULL", -1, -1);
//		}
//		// search for the node that contains the key
//		filesystem::path currPath = rootPath;
//		int childIndexInParent = -1;
//		int keyIndexInNode = -1;
//		// loop until the leaf node is reached
//		while (true) {
//			// load the node
//			Node currNode = Node::LoadFromFile(currPath, *this);
//
//			int i = 0;
//			// find the index of the key in the node
//			while (i < currNode.keys.getCurr() && value > currNode.keys[i].key) {
//				i++;
//			}
//			// if the key is found
//			if (i < currNode.keys.getCurr() && value == currNode.keys[i].key) {
//				keyIndexInNode = i;
//				break;
//			}
//			// if the key is not found
//			if (currNode.isLeaf) {
//				return Pair<filesystem::path, int, int>("NULL", -1, -1);
//			}
//			// update the path and the index of the child in the parent
//			childIndexInParent = i;
//			currPath = currNode.childrenPaths[i];
//		}
//		// return the path of the node, the index of the key in the node and the index of the child in the parent
//		return Pair<filesystem::path, int, int>(currPath, keyIndexInNode, childIndexInParent);
//	}
//	// function to remove Node from the tree
//	void removeNode(filesystem::path& root, const T& value) {
//		if (root == "NULL") {
//			// if treep empty throws an exception
//			throw runtime_error("B-tree is empty.");
//		}
//		// search the node that we have to delete
//		Pair<path, int, int> toBeRemoved = searchNode_Deletion(value);
//
//		if (toBeRemoved.second == -1) {
//			// if no instance of the key is found
//			return;
//		}
//		// load the node to be removed
//		Node node = Node::LoadFromFile(toBeRemoved.first, *this);
//		if (node.keys.getCurr() > 1) {
//			// if the node has more than 1 key
//			node.keys.Destroy(toBeRemoved.second);
//			node.saveToFile(toBeRemoved.first);
//			return;
//		}
//		// removing just leaf key from the tree
//		if (node.parent == "NULL" && node.isLeaf) {
//			// if the node is the root and is a leaf
//			node.keys.removeAt(toBeRemoved.second);
//			if (node.keys.getCurr() == 0) {
//				// if the root has no keys left
//				filesystem::remove(this->rootPath);
//				this->rootPath = "NULL";
//			}
//			else {
//				// update the root node
//				node.saveToFile(toBeRemoved.first);
//			}
//		}
//		// remove leaf key from the tree
//		else if (node.isLeaf) {
//			// sends file path the node is stored in, the node itself and the index of the key to be removed
//			removeLeaf(toBeRemoved.first, node, toBeRemoved.third);
//		}
//		// remove internal key from the tree
//		else {
//			// sends file path the node is stored in, the node itself and the index of the key to be removed
//			removeInternal(toBeRemoved.first, node, toBeRemoved.second, value);
//		}
//
//	}
//	int degree; // Degree of the B-tree
//	int nodeCount; // Used to name the text files
//public:
//	// constructor
//	Btree(filesystem::path folderPath, int degree = 3) {
//		this->rootPath = "NULL"; // initally kept as NULL
//		this->folderPath = folderPath;
//		this->branchPath = folderPath; // make the branch
//		this->folderPath /= "TREE"; // make the folder
//		this->degree = degree;
//		if (!exists(this->folderPath)) {
//			create_directories(this->folderPath);
//			filesystem::path nodesPath = this->folderPath / "NODES"; // to hold all the nodes
//			filesystem::create_directories(nodesPath);
//		}
//		nodeCount = 0; // used to name the text files
//	}
//	// load constructor
//	Btree(bool loadTreeFromBranch, filesystem::path branchPath) {
//		if (loadTreeFromBranch) {
//			loadFromBranch(branchPath);
//		}
//	}
//	filesystem::path getRoot() {
//		return rootPath;
//	}
//	// insert declared in parent tree class but implemented here
//	// insert a key into the tree
//	void insert(const T& data, const long long& rowIndex) override
//	{
//		insertNode(rootPath, data, rowIndex);
//	}
//	// remove declared in parent tree class but implemented here
//	// remove a key from the tree
//	void remove(const T& data, const long long& rowIndex) override
//	{
//		removeNode(rootPath, data);
//	}
//	// function to print the tree
//	void print() override
//	{
//		printTree(rootPath);
//	}
//	// helper function to print the tree
//	void printTree(filesystem::path root, int depth = 0)
//	{
//		cout << "depth " << depth << ": ";
//		Node x = Node::LoadFromFile(root, *this);
//		for (int i = 0; i < x.keys.getCurr(); i++)
//		{
//			cout << x.keys[i].key << " ";
//		}
//		cout << endl;
//
//		depth++;
//		if (x.childrenPaths.getCurr() != 0)
//		{
//			for (int i = 0; i < x.childrenPaths.getCurr(); i++)
//			{
//				printTree(x.childrenPaths[i], depth);
//			}
//		}
//	}
//	// Save the tree to a file
//	void saveDataToFile()
//	{
//		ofstream file;
//		filesystem::path path = folderPath;
//		path += "\\TREE_DATA.txt";
//		file.open(path);
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'B-TREE_DATA.txt\' for writing.");
//		file << rootPath << '\n'; // save root path
//		file << folderPath << '\n'; // save folder path
//		file << branchPath << '\n'; // save branch path
//		file << this->degree << '\n'; // save degree
//		file.close();
//	}
//
//	// Load the tree from a file
//	void loadFromBranch(filesystem::path branchPath)
//	{
//		// all the data is stored in a file
//		branchPath /= "TREE";
//		branchPath /= "TREE_DATA.txt";
//		// handling the case where the file doesnt exist
//		if (!exists(branchPath))
//			throw runtime_error("File to load tree from doesnt exist.");
//		ifstream file(branchPath);
//		// handling the case where the file cannot be opened
//		if (!file.is_open())
//			throw runtime_error("Cannot open file: \'AVL_DATA.txt\' for reading.");
//		// file pathing and reading the data
//		file >> rootPath;
//		file >> folderPath;
//		file >> this->branchPath;
//		file >> this->degree;
//		file.close();
//	}
//
//	// function to search for a key in the tree
//	// declared in parent class
//	Vector<long long> search(const T& data) override
//	{
//		// search for the key in the tree
//		Pair<filesystem::path, int, int> searchNode = this->searchNode_Deletion(data);
//		if (searchNode.second == -1) {
//			// key not found
//			cout << "No instances of key: " << data << " exist." << endl;
//			return Vector<long long>(); // return an empty vector
//		}
//		else {
//			// key found
//			Node node = Node::LoadFromFile(searchNode.first, *this);
//			return node.keys[searchNode.second].indexes; // return the indexes of the key
//		}
//	}
//};
//
//class GitLite
//{
//private:
//	filesystem::path repoPath;
//	filesystem::path CSVPath;
//	int colNumber;
//	int treeType;					//1=AVL, 2=RB, 3=BTree
//	int hashType;					//1= instructor, 2=SHA
//	filesystem::path currentBranch;
//	Vector<filesystem::path> branches;
//	MerkleTree* currentMerkle;
//	ParentTree<String>* currentTree;
//
//	//applies changes from changesFile to current trees
//	void applyChanges(path changesFile)
//	{
//		ifstream ifile(changesFile);
//		if (!ifile.is_open())
//			throw runtime_error("Failed to open CHANGES.txt file.");
//
//		String operation;
//		String row;
//		int fieldIndex;
//		long long rowIndex;
//		char delim;
//		while (getline(ifile, operation))
//		{
//			if (operation == "INSERT")
//			{
//				//read row
//				ifile >> rowIndex >> delim;
//				getline(ifile, row);
//				rowIndex = currentMerkle->getCounter();
//				RowEntry rowData;
//				rowData.readRow(rowIndex, row);
//
//				currentMerkle->insert(rowData);								//insert with index in merkle
//				currentTree->insert(rowData.cells[colNumber], rowIndex);	//insert data and index in tree
//				currentMerkle->saveDataToFile();
//				currentTree->saveDataToFile();
//			}
//			else if (operation == "REMOVE")
//			{
//				//read row
//				ifile >> rowIndex >> delim;
//				getline(ifile, row);
//				RowEntry rowData;
//				rowData.readRow(rowIndex, row);
//
//				//remove from both trees
//				currentMerkle->remove(rowIndex);
//				currentTree->remove(rowData.cells[colNumber], rowIndex);
//				currentMerkle->saveDataToFile();
//				currentTree->saveDataToFile();
//			}
//			else if (operation == "UPDATE")
//			{
//				//read the updated field's index
//				ifile >> fieldIndex;
//				ifile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//				//read row
//				ifile >> rowIndex >> delim;
//				getline(ifile, row);
//				RowEntry rowData;
//				rowData.readRow(rowIndex, row);
//
//				//update AVL/RB/Btree if updated field is chosen column number
//				if (fieldIndex == this->colNumber)
//				{
//					this->currentTree->remove(this->currentMerkle->searchRowEntry(rowIndex).cells[fieldIndex], rowIndex);
//					this->currentTree->insert(rowData.cells[fieldIndex], rowIndex);
//				}
//				//update merkle
//				this->currentMerkle->update(rowIndex, fieldIndex, rowData.cells[fieldIndex]);
//				currentTree->saveDataToFile();
//			}
//			else if (operation == "")
//				break;
//
//		}
//	}
//public:
//	GitLite() : colNumber(-1), currentMerkle(nullptr), currentTree(nullptr), treeType(-1)
//	{}
//	~GitLite()
//	{
//		if (currentMerkle)
//			delete currentMerkle;
//		if (currentTree)
//			delete currentTree;
//	}
//	void initRepo()
//	{
//		currentMerkle = nullptr;
//		currentTree = nullptr;
//		colNumber = -1;
//		treeType = -1;
//		branches.clear();
//		currentBranch = "";
//
//		//create repo folder
//		cout << "Enter Repository name: ";
//		cin >> repoPath;
//
//		//create new repo if doesn't exist
//		if (!exists(repoPath))
//		{
//			create_directory(repoPath);
//			//store CSV path
//			cout << "Enter CSV file path: ";
//			cin >> CSVPath;
//			while (!exists(CSVPath))
//			{
//				cout << "Invalid CSV path. Enter again: ";
//				cin >> CSVPath;
//			}
//
//			//create master branch
//			currentBranch = repoPath;
//			currentBranch /= "master";
//			branches.push_back(currentBranch);
//
//			//choose tree
//			cout << "1. AVL\n";
//			cout << "2. Red Black tree\n";
//			cout << "3. BTree\n";
//			cout << "Choose tree type: ";
//			cin >> treeType;
//			while (treeType < 1 || treeType>3)
//			{
//				cout << "Invalid option. Choose again: ";
//				cin >> treeType;
//			}
//
//			cout << "1: Instructor hash\n";
//			cout << "2: SHA-256\n";
//			cout << "Enter hash choice: ";
//			cin >> hashType;
//			while (hashType != 1 && hashType != 2)
//			{
//				cout << "Choose within range: ";
//				cin >> hashType;
//			}
//			::hashTypeGlobal = hashType;
//
//
//			//read file
//			fstream CSV(CSVPath);
//			if (!CSV.is_open()) {
//				std::cerr << "Error: Could not open file." << std::endl;
//				return;
//			}
//
//			//read header of CSV
//			String header;
//			getline(CSV, header);
//			Vector<String> colNames;
//			String currentColumn;
//			for (int a = 0; a < header.getSize(); a++)
//			{
//				if (header[a] != ',')
//				{
//					currentColumn += header[a];
//				}
//				else
//				{
//					colNames.push_back(currentColumn);
//					currentColumn = "";
//				}
//			}
//			if (!(currentColumn == ""))
//				colNames.push_back(currentColumn);
//
//			//display and select column;
//			cout << "==== columns ====\n";
//			for (int a = 0; a < colNames.getCurr(); a++)
//			{
//				cout << a << ": " << colNames[a] << endl;
//			}
//			cout << "Choose column to build tree on: ";
//			cin >> colNumber;
//			while (colNumber < 0 || colNumber >= colNames.getCurr())
//			{
//				cout << "Invalid index, enter again: ";
//				cin >> colNumber;
//			}
//
//
//			//create MerkleTree and AVL/RB/BTree
//			currentMerkle = new MerkleTree(currentBranch);
//			if (treeType == 1)//AVL
//			{
//				currentTree = new AVL<String>(currentBranch);
//			}
//			else if (treeType == 2)//RedBlack
//			{
//				currentTree = new RedBlackTree<String>(currentBranch);
//			}
//			else if (treeType == 3)//BTree
//			{
//				cout << "Choose Degree for B-Tree: ";
//				int degree;
//				cin >> degree;
//				while (degree <= 1)
//				{
//					cout << "Enter degree >=2: ";
//					cin >> degree;
//				}
//				this->currentTree = new Btree<String>(currentBranch, degree);
//			}
//			String rowString;
//			long long rowIndex;
//			while (true)
//			{
//				getline(CSV, rowString);
//				if (rowString[0] == ',' || !rowString)
//					break;
//
//				rowIndex = currentMerkle->getCounter();
//				RowEntry rowData;
//				rowData.readRow(rowIndex, rowString);
//				currentMerkle->insert(rowData);					//insert with index in merkle
//				currentTree->insert(rowData.cells[colNumber], rowIndex);	//insert data and index in tree
//			}
//			CSV.close();
//			currentMerkle->saveDataToFile();
//			currentTree->saveDataToFile();
//			saveRepoToFile();
//			cout << "Created new repository: " << repoPath << endl;
//		}
//		//if repo does exist, load the repo from the repo_data.txt
//		else
//		{
//			loadRepoFromFile();
//			cout << "Loaded existing repository: " << repoPath << endl;
//		}
//	}
//	void printCurrentTree()
//	{
//		if (currentTree)
//			this->currentTree->print();
//		else
//			cout << "Error: No tree loaded." << endl;
//	}
//	void printCurrentBranch()
//	{
//		if (currentBranch == "")
//			cout << "Error: No branch loaded." << endl;
//		else
//			cout << "Current branch: " << currentBranch << endl;
//	}
//	void printAllBranches()
//	{
//		if (branches.getCurr() == 0)
//		{
//			cout << "Error: No branch exists." << endl;
//			return;
//		}
//		for (int a = 0; a < branches.getCurr(); a++)
//		{
//			cout << "- " << branches[a] << endl;
//		}
//	}
//	void createBranch()
//	{
//		path branchName;
//		cout << "Enter branch name: ";
//		cin >> branchName;
//		path branchPath = repoPath / branchName;
//		for (int a = 0; a < branches.getCurr(); a++)
//		{
//			if (branches[a] == branchPath)
//			{
//				cout << "Error: Branch " << branchName << " already exists." << endl;
//				return;
//			}
//		}
//		branches.push_back(branchPath);
//		filesystem::copy(currentBranch, branchPath, filesystem::copy_options::recursive);
//
//		//update branch names in new trees' data files
//		path newMerkleFilePath = branchPath / "MERKLETREE" / "MERKLE_DATA.txt";
//		MerkleTree::updateNewBranch(newMerkleFilePath, currentBranch.filename(), branchPath.filename());
//
//		path newTreePath = branchPath / "TREE" / "TREE_DATA.txt";
//		ParentTree<String>::updateNewBranch(newTreePath, currentBranch.filename(), branchPath.filename());
//
//		saveRepoToFile();
//		cout << "Branch: " << branchName << " created." << endl;
//	}
//
//	void checkout()
//	{
//		path branchName;
//		cout << "Enter branch name: ";
//		cin >> branchName;
//		path branchPath = repoPath / branchName;
//		for (int a = 0; a < branches.getCurr(); a++)
//		{
//			if (branches[a] == branchPath)
//			{
//				currentBranch = branches[a];
//				cout << "Switched to branch: " << branchName << endl;
//
//				//switch to target branch's trees
//				if (currentMerkle)
//					delete currentMerkle;
//				if (currentTree)
//					delete currentTree;
//
//				currentMerkle = new MerkleTree(true, currentBranch);
//				if (treeType == 1)//AVL
//				{
//					currentTree = new AVL<String>(true, currentBranch);
//				}
//				else if (treeType == 2)//RB
//				{
//					currentTree = new RedBlackTree<String>(true, currentBranch);
//				}
//				else if (treeType == 3)//BTree
//				{
//					currentTree = new Btree<String>(true, currentBranch);
//				}
//				saveRepoToFile();
//				return;
//			}
//		}
//		cout << "Error: branch does not exist." << endl;
//	}
//
//	void deleteBranch()
//	{
//		path branchName;
//		cout << "Enter branch name: ";
//		cin >> branchName;
//		path branchPath = repoPath / branchName;
//		if (currentBranch == branchPath)
//		{
//			cout << "Error: Attempting to delete current branch. Checkout to another branch first." << endl;
//			return;
//		}
//		else
//		{
//			for (int a = 0; a < branches.getCurr(); a++)
//			{
//				if (branches[a] == branchPath)
//				{
//					branches.Destroy(a);
//					filesystem::remove_all(branchPath);
//					cout << "Branch: " << branchPath << " removed." << endl;
//					saveRepoToFile();
//					return;
//				}
//			}
//			cout << "Error: branch not found." << endl;
//		}
//	}
//	void merge()
//	{
//		//input the other branch
//		cout << "Enter name of branch to merge into current branch: ";
//		path otherBranch;
//		cin >> otherBranch;
//		otherBranch = repoPath / otherBranch;
//		if (!exists(otherBranch))
//		{
//			cout << "Branch does not exist." << endl;
//			return;
//		}
//		if (otherBranch == currentBranch)
//		{
//			cout << "Cannot merge a branch into itself." << endl;
//			return;
//		}
//
//		//store current branch commits in vector
//		path currentBranchCommitFile = currentBranch / "COMMITS" / "COMMIT_DATA.txt";
//		Vector<path> currentBranchCommits;
//		if (exists(currentBranchCommitFile))
//		{
//			ifstream file(currentBranchCommitFile);
//			if (!file.is_open())
//				throw runtime_error("Cannot open current branch commit file.");
//			path temp;
//			while (true)
//			{
//				file >> temp;
//				if (file.eof() || temp.empty())
//					break;
//				currentBranchCommits.push_back(temp);
//			}
//		}
//
//		//store other branch's commits in vector
//		path otherBranchCommitFile = otherBranch / "COMMITS" / "COMMIT_DATA.txt";
//		Vector<path> otherBranchCommits;
//		if (exists(otherBranchCommitFile))
//		{
//			ifstream file(otherBranchCommitFile);
//			if (!file.is_open())
//				throw runtime_error("Cannot open other branch commit file.");
//			path temp;
//			while (true)
//			{
//				file >> temp;
//				if (file.eof() || temp.empty())
//					break;
//				otherBranchCommits.push_back(temp);
//			}
//		}
//
//		//simply delete other branch if there are no commits in it
//		if (otherBranchCommits.getCurr() == 0)
//		{
//			for (int a = 0; a < branches.getCurr(); a++)
//			{
//				if (branches[a] == otherBranch)
//				{
//					branches.Destroy(a);
//					filesystem::remove_all(otherBranch);
//					saveRepoToFile();
//					cout << "Branches merged." << endl;
//					return;
//				}
//			}
//		}
//
//		//if current commits are 0, apply all commits in other branch to current branch
//		if (currentBranchCommits.getCurr() == 0)
//		{
//			//apply changes
//			for (int a = 0; a < otherBranchCommits.getCurr(); a++)
//			{
//				path changesFile = otherBranchCommits[a] / "CHANGES.txt";
//				applyChanges(changesFile);
//			}
//
//			//delete other branch
//			for (int a = 0; a < branches.getCurr(); a++)
//			{
//				if (branches[a] == otherBranch)
//				{
//					branches.Destroy(a);
//					filesystem::remove_all(otherBranch);
//					saveRepoToFile();
//					cout << "Branches merged." << endl;
//					return;
//				}
//			}
//		}
//
//		//find the commit where both branches diverge, then apply other branch's commits from there on
//		int firstUncommonCommitIndex = -1;
//		for (int a = 0; a < otherBranchCommits.getCurr() && a < currentBranchCommits.getCurr(); a++)
//		{
//			if (otherBranchCommits[a] != currentBranchCommits[a])
//			{
//				firstUncommonCommitIndex = a;
//				break;
//			}
//		}
//
//		//if no uncommon commit found till min(currBranchCommits, otherBranchCommits)
//		if (firstUncommonCommitIndex == -1)
//		{
//			//if current branch is ahead of /equal to other branch
//			if (currentBranchCommits.getCurr() >= otherBranchCommits.getCurr())
//			{
//				//delete other branch
//				for (int a = 0; a < branches.getCurr(); a++)
//				{
//					if (branches[a] == otherBranch)
//					{
//						branches.Destroy(a);
//						filesystem::remove_all(otherBranch);
//						saveRepoToFile();
//						cout << "Branches merged." << endl;
//						return;
//					}
//				}
//			}
//			//if current branch is behind other branch
//			else
//			{
//				//apply other branch changes from new commits onwards
//				for (int a = currentBranchCommits.getCurr(); a < otherBranchCommits.getCurr(); a++)
//				{
//					path changesFile = otherBranchCommits[a] / "CHANGES.txt";
//					applyChanges(changesFile);
//				}
//				//delete other branch
//				for (int a = 0; a < branches.getCurr(); a++)
//				{
//					if (branches[a] == otherBranch)
//					{
//						branches.Destroy(a);
//						filesystem::remove_all(otherBranch);
//						saveRepoToFile();
//						cout << "Branches merged." << endl;
//						return;
//					}
//				}
//			}
//		}
//		//found uncommon commit
//		else
//		{
//			//apply changes from uncommon commit onwards
//			for (int a = firstUncommonCommitIndex; a < otherBranchCommits.getCurr(); a++)
//			{
//				path changesFile = otherBranchCommits[a] / "CHANGES.txt";
//				applyChanges(changesFile);
//			}
//			//delete other branch
//			for (int a = 0; a < branches.getCurr(); a++)
//			{
//				if (branches[a] == otherBranch)
//				{
//					branches.Destroy(a);
//					filesystem::remove_all(otherBranch);
//					saveRepoToFile();
//					cout << "Branches merged." << endl;
//					return;
//				}
//			}
//		}
//
//
//	}
//
//	void saveRepoToFile()
//	{
//		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
//		ofstream file(repoFilePath);
//		if (!file.is_open())
//			throw runtime_error("Cannot open repo data file for writing.");
//
//		file << repoPath << '\n';
//		file << CSVPath << '\n';
//		file << colNumber << '\n';
//		file << treeType << '\n';
//		file << hashType << '\n';
//		file << currentBranch << '\n';
//		file << branches.getCurr() << '\n';
//		for (int a = 0; a < branches.getCurr(); a++)
//		{
//			file << branches[a] << '\n';
//		}
//	}
//	void loadRepoFromFile(path filePath = "NULL")
//	{
//		filesystem::path repoFilePath;
//		if (filePath == "NULL")
//		{
//			repoFilePath = repoPath / "REPO_DATA.txt";
//		}
//		else
//		{
//			repoFilePath = filePath;
//		}
//		ifstream file(repoFilePath);
//		if (!file.is_open()) {
//			throw runtime_error("Cannot open repo data file for reading.");
//		}
//
//		String line;
//
//		file >> repoPath;
//		file >> CSVPath;
//
//		file >> colNumber;
//		file.ignore(numeric_limits<streamsize>::max(), '\n');
//		file >> treeType;
//		file.ignore(numeric_limits<streamsize>::max(), '\n');
//		file >> hashType;
//		::hashTypeGlobal = hashType;
//		file.ignore(numeric_limits<streamsize>::max(), '\n');
//		file >> currentBranch;
//		int branchCount;
//		file >> branchCount;
//		file.ignore(numeric_limits<streamsize>::max(), '\n');
//
//		branches.clear();
//		for (int i = 0; i < branchCount; i++)
//		{
//			filesystem::path currBranch;
//			file >> currBranch;
//			branches.push_back(currBranch);
//		}
//
//		//load trees from branch
//		if (currentMerkle)
//			delete currentMerkle;
//		currentMerkle = new MerkleTree(true, currentBranch);
//
//		if (currentTree)
//			delete currentTree;
//		if (treeType == 1)//AVL
//		{
//			currentTree = new AVL<String>(true, currentBranch);
//		}
//		else if (treeType == 2)//RB
//		{
//			currentTree = new RedBlackTree<String>(true, currentBranch);
//		}
//		else if (treeType == 3)//BTree
//		{
//			currentTree = new Btree<String>(true, currentBranch);
//		}
//
//
//		file.close();
//	}
//	path getRepoDataFile()
//	{
//		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
//		return repoFilePath;
//	}
//	void insert()
//	{
//		fstream CSV(CSVPath);
//		if (!CSV.is_open()) {
//			std::cerr << "Error: Could not open file." << std::endl;
//			return;
//		}
//		//read header of CSV
//		String header;
//		getline(CSV, header);
//		Vector<String> colNames;
//		String currentColumn;
//		for (int a = 0; a < header.getSize(); a++)
//		{
//			if (header[a] != ',')
//			{
//				currentColumn += header[a];
//			}
//			else
//			{
//				colNames.push_back(currentColumn);
//				currentColumn = "";
//			}
//		}
//		if (!(currentColumn == ""))
//			colNames.push_back(currentColumn);
//		RowEntry newRow;
//		for (int a = 0; a < colNames.getCurr(); a++)
//		{
//			currentColumn = "";
//			cout << colNames[a] << ": ";
//			getline(cin, currentColumn);
//			for (int a = 0; a < currentColumn.getSize(); a++)
//			{
//				if (isAlphabet(currentColumn[a]))
//					currentColumn.getData()[a] = convertToUppercase(currentColumn[a]);
//			}
//			newRow.cells.push_back(currentColumn);
//		}
//		newRow.rowIndex = -1;
//		storeChange("INSERT", newRow);
//
//		cout << "Entry inserted." << endl;
//	}
//	void search()
//	{
//		cout << "Enter key to search: ";
//		String input;
//		getline(cin, input);
//		for (int a = 0; a < input.getSize(); a++)
//		{
//			if (isAlphabet(input[a]))
//				input.getData()[a] = convertToUppercase(input[a]);
//		}
//		Vector<long long> indexes = this->currentTree->search(input);
//		if (indexes.getCurr() == 0)
//			return;
//		for (int a = 0; a < indexes.getCurr(); a++)
//		{
//			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a]) << endl;
//		}
//	}
//	void remove()
//	{
//		cout << "Enter key to remove: ";
//		String input;
//		getline(cin, input);
//		for (int a = 0; a < input.getSize(); a++)
//		{
//			if (isAlphabet(input[a]))
//				input.getData()[a] = convertToUppercase(input[a]);
//		}
//		Vector<long long> indexes = this->currentTree->search(input);
//		if (indexes.getCurr() == 0)
//			return;
//		for (int a = 0; a < indexes.getCurr(); a++)
//		{
//			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a]) << endl;
//		}
//
//		cout << "\n1: remove all instances" << endl;
//		cout << "2: remove a specific instance" << endl;
//		cout << "Enter choice: ";
//		int choice = 0;
//		cin >> choice;
//		while (choice != 1 && choice != 2)
//		{
//			cout << "Invalid choice. Enter again: ";
//			cin >> choice;
//		}
//		if (choice == 1)
//		{
//			for (int a = 0; a < indexes.getCurr(); a++)
//			{
//				RowEntry deletedRow = this->currentMerkle->searchRowEntry(indexes[a]);
//				storeChange("REMOVE", deletedRow);
//				cout << "Entry: " << a << " removed" << endl;
//			}
//		}
//		else if (choice == 2)
//		{
//			cout << "Enter index of entry to remove: ";
//			cin >> choice;
//			while (choice < 0 || choice >= indexes.getCurr())
//			{
//				cout << "Invalid index. Choose within range: ";
//				cin >> choice;
//			}
//			RowEntry deletedRow = this->currentMerkle->searchRowEntry(indexes[choice]);
//			storeChange("REMOVE", deletedRow);
//			cout << "Entry: " << choice << " removed" << endl;
//		}
//	}
//	void update()
//	{
//		//read key and display all instances of that key
//		cout << "Enter key to update: ";
//		String input;
//		getline(cin, input);
//		for (int a = 0; a < input.getSize(); a++)
//		{
//			if (isAlphabet(input[a]))
//				input.getData()[a] = convertToUppercase(input[a]);
//		}
//		Vector<long long> indexes = this->currentTree->search(input);
//		if (indexes.getCurr() == 0)
//			return;
//		for (int a = 0; a < indexes.getCurr(); a++)
//		{
//			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a]) << endl;
//		}
//
//		//ask if update all instances or only 1
//		cout << "\n1: update all instances" << endl;
//		cout << "2: update a specific instance" << endl;
//		cout << "Enter choice: ";
//		int choice = 0;
//		cin >> choice;
//		while (choice != 1 && choice != 2)
//		{
//			cout << "Invalid choice. Enter again: ";
//			cin >> choice;
//		}
//
//
//		//read header of CSV
//		fstream CSV(CSVPath);
//		if (!CSV.is_open()) {
//			std::cerr << "Error: Could not open file." << std::endl;
//			return;
//		}
//		String header;
//		getline(CSV, header);
//		Vector<String> colNames;
//		String currentColumn;
//		for (int a = 0; a < header.getSize(); a++)
//		{
//			if (header[a] != ',')
//			{
//				currentColumn += header[a];
//			}
//			else
//			{
//				colNames.push_back(currentColumn);
//				currentColumn = "";
//			}
//		}
//		if (!(currentColumn == ""))
//			colNames.push_back(currentColumn);
//
//
//		//ask for field that has to be updated
//		cout << endl;
//		for (int a = 0; a < colNames.getCurr(); a++)
//		{
//			cout << a << ": " << colNames[a] << endl;
//		}
//		int field = -1;
//		cout << "Enter field to update: ";
//		cin >> field;
//		while (field < 0 || field >= colNames.getCurr())
//		{
//			cout << "Invalid index. Enter within range: ";
//			cin >> field;
//		}
//
//		//enter the new value of the replacement
//		String newField;
//		cout << "Enter new value of field: ";
//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//		getline(cin, newField);
//		for (int a = 0; a < newField.getSize(); a++)
//		{
//			if (isAlphabet(newField[a]))
//				newField.getData()[a] = convertToUppercase(newField[a]);
//		}
//
//		if (choice == 1)
//		{
//			for (int a = 0; a < indexes.getCurr(); a++)
//			{
//				RowEntry updatedRow = this->currentMerkle->searchRowEntry(indexes[a]);
//				updatedRow.cells[field] = newField;
//				storeChange("UPDATE", updatedRow, field);
//				cout << "Entry: " << a << " updated" << endl;
//			}
//		}
//		else if (choice == 2)
//		{
//			cout << "Enter index of entry to update: ";
//			cin >> choice;
//			while (choice < 0 || choice >= indexes.getCurr())
//			{
//				cout << "Invalid index. Choose within range: ";
//				cin >> choice;
//			}
//			RowEntry updatedRow = this->currentMerkle->searchRowEntry(indexes[choice]);
//			updatedRow.cells[field] = newField;
//			storeChange("UPDATE", updatedRow, field);
//			cout << "Entry: " << choice << " updated" << endl;
//		}
//	}
//	void storeChange(const String& operation, RowEntry& op, int fieldIndex = -1)
//	{
//		path tempFolder = this->currentBranch / "temp";
//		if (!exists(tempFolder))
//		{
//			filesystem::create_directories(tempFolder);
//		}
//		path changesFile = tempFolder / "CHANGES.txt";
//		ofstream file(changesFile, ios::app);
//		if (!file.is_open())
//			throw runtime_error("Failed to open CHANGES.txt file.");
//
//
//		if (operation == "UPDATE")
//		{
//			file << operation << '\n';
//			file << fieldIndex << '\n';
//			file << op.rowIndex << ',' << op << '\n';
//		}
//		else
//		{
//			file << operation << '\n';
//			file << op.rowIndex << ',' << op << '\n';
//		}
//	}
//	void commit()
//	{
//		if (!exists(currentBranch / "temp"))
//		{
//			cout << "No changes to commit." << endl;
//			return;
//		}
//		cout << "Enter message: ";
//		path message;
//		String messagestr;
//		getline(cin, messagestr);
//		message = messagestr.getData();
//
//		while (exists(currentBranch / message))
//		{
//			cout << "This commit exists, enter new message: ";
//			message.clear();
//			cin >> message;
//		}
//
//		//create commits folder
//		if (!exists(currentBranch / "COMMITS"))
//		{
//			create_directories(currentBranch / "COMMITS");
//		}
//		//create the current commit message folder
//		create_directories(currentBranch / "COMMITS" / message);
//
//		//store commit history in file
//		ofstream file(currentBranch / "COMMITS" / "COMMIT_DATA.txt", ios::app);
//		if (!file.is_open())
//			throw runtime_error("Failed to open COMMIT_DATA.txt file.");
//		file << (currentBranch / "COMMITS" / message) << '\n';
//		file.close();
//
//		//paste temp folder's changes file to current commit folder
//		path changesFile = currentBranch / "temp" / "CHANGES.txt";
//		filesystem::copy(changesFile, currentBranch / "COMMITS" / message / changesFile.filename(), filesystem::copy_options::overwrite_existing);
//		filesystem::remove_all(currentBranch / "temp");
//
//
//		//apply changes
//		changesFile = currentBranch / "COMMITS" / message / "CHANGES.txt";
//		applyChanges(changesFile);
//		cout << "Changes commited." << endl;
//	}
//
//	void log()
//	{
//		if (!exists(currentBranch / "COMMITS" / "COMMIT_DATA.txt"))
//		{
//			cout << "No commits saved." << endl;
//			return;
//		}
//		ifstream file(currentBranch / "COMMITS" / "COMMIT_DATA.txt");
//		if (!file.is_open())
//			throw runtime_error("Failed to open COMMIT_DATA.txt file.");
//		path currCommit;
//		int counter = 1;
//		while (true)
//		{
//			file >> currCommit;
//			if (file.eof() || currCommit.empty())
//				break;
//			cout << "Commit # " << counter++ << ": " << currCommit.filename() << endl;
//		}
//	}
//	void printMerc()
//	{
//		this->currentMerkle->print();
//	}
//};
//
//
//int main()
//{
//	GitLite git;
//	String input;
//	while (true)
//	{
//		cout << "> ";
//		input = "";
//		cin >> input;
//
//		if (input == "init")
//		{
//			git.initRepo();
//		}
//		else if (input == "print")
//		{
//			git.printCurrentTree();
//		}
//		else if (input == "print-merc")
//		{
//			git.printMerc();
//		}
//		else if (input == "current-branch")
//		{
//			git.printCurrentBranch();
//		}
//		else if (input == "branches")
//		{
//			git.printAllBranches();
//		}
//		else if (input == "create-branch")
//		{
//			git.createBranch();
//		}
//		else if (input == "checkout")
//		{
//			git.checkout();
//		}
//		else if (input == "delete-branch")
//		{
//			git.deleteBranch();
//		}
//		else if (input == "save")
//		{
//			git.saveRepoToFile();
//			cout << "Repository data saved to file: "<< git.getRepoDataFile() << endl;
//		}
//		else if (input == "load")
//		{
//			filesystem::path temp;
//			cout << "Enter REPO_DATA.txt file path: ";
//			cin >> temp;
//			if (filesystem::exists(temp))
//			{
//				git.loadRepoFromFile(temp);
//				cout << "Repository loaded from: " << git.getRepoDataFile() << endl;
//			}
//			else
//				cout << "Error: Invalid file path." << endl;
//		}
//		else if (input == "insert")
//		{
//			git.insert();
//		}
//		else if (input == "search")
//		{
//			git.search();
//		}
//		else if (input == "remove")
//		{
//			git.remove();
//		}
//		else if (input == "update")
//		{
//			git.update();
//		}
//		else if (input == "commit")
//		{
//			git.commit();
//		}
//		else if (input == "log")
//		{
//			git.log();
//		}
//		else if (input == "merge")
//		{
//			git.merge();
//		}
//		else if (input == "exit")
//		{
//			break;
//		}
//		else
//		{
//			cout << "Invalid command.\n";
//		}
//
//	}
//	return 0;
//}