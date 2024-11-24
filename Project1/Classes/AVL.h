#pragma once
#include<iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

template <class T>
class AVL
{
private:

	//===================================== AVL Node ==========================================
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

		void updateFile(const string& path)
		{
			if (path.empty())
				throw runtime_error("Attempting to access empty path.");

			ofstream file(path);
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

		static Node readFile(const string& path)
		{
			if(path.empty())
				throw runtime_error("Attempting to access empty path.");
			
			ifstream file(path);
			if (!file.is_open())
				throw runtime_error("Cannot open file: \'" + path + "\' for reading.");

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

// ===================================== AVL functions ==========================================
	string rootPath;

	//get height of node
	int Height(const string& path)
	{
		if (path.empty())
			return -1;
		else
		{
			return Node::readFile(path).height;
		}
	}

	//NOTE: does not update height in file 
	void updateNodeHeight(Node& node)
	{
		int leftHeight = Height(node.left);
		int rightHeight = Height(node.right);

		node.height = max(leftHeight, rightHeight) + 1;
		return;
	}

	//BF = Right - Left
	int balanceFactor(const Node& node)
	{
		int leftHeight = Height(node.left);
		int rightHeight = Height(node.right);

		return rightHeight - leftHeight;
	}

	//========= rotations ===========

	//returns path of the node that replaces the main node
	string rotateRight(const string& path)
	{
		Node mainNode = Node::readFile(path);
		Node leftNode = Node::readFile(mainNode.left);
		string leftNodePath = mainNode.left;
		string leftNodeKaRightPath = leftNode.right;

		//perform rotation
		mainNode.left = leftNodeKaRightPath;
		if (!leftNodeKaRightPath.empty())
		{
			Node leftNodesRight_NODE = Node::readFile(leftNodeKaRightPath);
			leftNodesRight_NODE.parent = path;
			leftNodesRight_NODE.updateFile(leftNodeKaRightPath);
		}
		leftNode.parent = mainNode.parent;
		leftNode.right = path;
		mainNode.parent = leftNodePath;

		//update heights
		updateNodeHeight(mainNode);
		updateNodeHeight(leftNode);

		//update files
		mainNode.updateFile(path);
		leftNode.updateFile(leftNodePath);

		//return path of new parent
		return leftNodePath;

	}

	//returns path of the node that replaces the main node
	string rotateLeft(const string& path)
	{
		Node mainNode = Node::readFile(path);
		Node rightNode = Node::readFile(mainNode.right);
		string rightNodePath = mainNode.right;
		string rightNodeKaLeftPath = rightNode.left;

		//perform rotation
		mainNode.right = rightNodeKaLeftPath;
		if (!rightNodeKaLeftPath.empty())
		{
			Node rightNodesleft_NODE = Node::readFile(rightNodeKaLeftPath);
			rightNodesleft_NODE.parent = path;
			rightNodesleft_NODE.updateFile(rightNodeKaLeftPath);
		}
		rightNode.parent = mainNode.parent;
		rightNode.left = path;
		mainNode.parent = rightNodePath;

		//update heights
		updateNodeHeight(mainNode);
		updateNodeHeight(rightNode);

		//update files
		mainNode.updateFile(path);
		leftNode.updateFile(rightNodePath);

		//return path of new parent
		return rightNodePath;
	}

	

public:
	AVL(): rootPath("")
	{}


};
