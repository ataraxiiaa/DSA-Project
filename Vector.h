#pragma once

#ifndef Vector_H
#define Vector_H

#include <iostream>
using namespace std;

template <typename Type>class Vector  // Vector Template that would take type 
{
	Type* ptr; // Pointer to store the type
	int currSize, maxSize; // to track if to expand the vector array or not

public:
	Vector() {
		ptr = new Type[5];
		currSize = 0;
		maxSize = 5;
	}
	//~Vector() { delete ptr; } // Destructor

	// Adding values to the array
	void push_back(Type value) {
		if (currSize == maxSize) {
			Type* temp = new Type[maxSize];
			for (int i = 0; i < maxSize; ++i)
				temp[i] = ptr[i];
			delete[] ptr;
			ptr = new Type[2 * maxSize];
			for (int i = 0; i < maxSize; ++i)
				ptr[i] = temp[i];
			delete[] temp;
			maxSize *= 2;
		}
		ptr[currSize] = value;
		++currSize;
	}
	int getCurr() { return currSize; }

	Type& operator[](int index) { return ptr[index]; } // Accessing address the pointer is pointing to 

	void Destroy(int index) {
		if (index == currSize - 1) {
			currSize--;
		}
		else {
			for (int i = index; i < currSize - 1; ++i) { // Discarding the vakue not required
				ptr[i] = ptr[i + 1]; // Move the values by 1
			}
			currSize--; // Adjust the current Size
		}
	}
	Type& back() {
		return ptr[currSize - 1];
	}
};

template <typename Type> class Vector<Type*>  // Template of vector created for pointer to pointer
{
	Type** ptr; // pointer to pointer to type
	int currSize, maxSize; // Used to track if to expand the array or ot
public:
	Vector() // Default constructor 
	{
		ptr = new Type * [5];
		currSize = 0;
		maxSize = 5;
	}
	/*~Vector() {
		for (int i = 0; i < currSize; ++i) {
			if (ptr[i] != nullptr)
				delete[] ptr[i];
		}
			delete[] ptr;
	}*/
	int GetSize()const { return this->currSize; }
	void push_back(Type* value) {
		if (currSize == maxSize) {
			Type** temp = new Type * [maxSize];
			for (int i = 0; i < maxSize; ++i)
				temp[i] = ptr[i];
			delete[] ptr;
			ptr = new Type * [2 * maxSize];
			for (int i = 0; i < maxSize; ++i)
				ptr[i] = temp[i];
			delete[] temp;
			maxSize *= 2;
		}
		ptr[currSize] = value;
		++currSize;
	}
	Type*& operator[](int index)
	{
		return ptr[index];
	}
	void Destroy(int index) {
		if (index == currSize - 1) {
			--currSize;
		}
		else {
			for (int i = index; i < currSize - 1; ++i) { // Discarding the vakue not required
				ptr[i] = ptr[i + 1]; // Move the values by 1
			}
			--currSize; // Adjust the current Size
		}
	}
	Type*& back() {
		return ptr[currSize - 1];
	}


};


#endif // Vector_H