#pragma once
#include<iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

template <class T>
class AVL
{
	struct Node
	{
		T data;
		int height;
		string hash;
		string left;	 //left child path
		string right;	 //right child path
		string parent;	 //parent path

		Node(T data): data(data), height(0),hash(""), left(""), right(""), parent("")
		{}

		void updateFile(const string& fileName)
		{
			ofstream file(fileName);
			if (!file.is_open())
				throw runtime_error("Cannot open file: \'" + fileName + "\' for writing.");

			file << this->data << endl;
			file << this->height << endl;
			file << this->hash << endl;
			file << this->left << endl;
			file << this->right << endl;
			file << this->parent << endl;

			file.close();
		}

		static Node readFile(const string& fileName)
		{
			ifstream file(fileName);
			if (!file.is_open())
				throw runtime_error("Cannot open file: \'" + fileName + "\' for reading.");

			Node node;
			file >> node.data;
			file >> node.height;
			file >> node.hash;
			file >> node.left;
			file >> node.right;
			file >> node.parent;

			file.close();
			return node;
		}
	};
};
