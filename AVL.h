#pragma once
#include<iostream>
#include "String.h"
#include <fstream>
#include<filesystem>
using namespace std;

//NOTE: try to keep file accessing at a minimum as that will slow the algorithm down.
//if possible, open a required file not more than once

template <class T>
class AVL
{
private:

	//===================================== AVL Node ==========================================
	struct Node
	{
		T data;
		int height;
		int frequency;
		String hash;
		filesystem::path left;	 //left child path
		filesystem::path right;	 //right child path
		filesystem::path parent;	 //parent path

		Node(T data=T()): data(data), height(0), frequency(1), hash("InsertHashHere"), left("NULL"), right("NULL"), parent("NULL")
		{}

		void updateFile(const filesystem::path& path)
		{
			if (path == "NULL")
				throw runtime_error("Attempting to access empty path.");

			ofstream file;
			file.open(path);
			if (!file.is_open())
				throw runtime_error("Cannot open file for writing.");

			file << this->data << '\n';
			file << this->height << '\n';
			file << this->frequency << '\n';
			file << this->hash << '\n';
			file << this->left << '\n';
			file << this->right << '\n';
			file << this->parent << '\n';

			file.close();
		}

		static Node readFile(const filesystem::path& path)
		{
			if(path== "NULL")
				throw runtime_error("Attempting to access empty path.");
			
			ifstream file;
			file.open(path);
			if (!file.is_open())
				throw runtime_error("Cannot open file for reading.");

			Node node;
			if constexpr (is_same<T, String>::value) 
			{
				getline(file, node.data);
				file >>node.height;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				file >>node.frequency;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				file >> node.data;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				file >> node.height;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				file >> node.frequency;
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			getline(file, node.hash);
			file >> node.left;
			file >> node.right;
			file >> node.parent;
			
			file.close();
			return node;
		}
	};

// ===================================== AVL functions ==========================================
	filesystem::path rootPath;
	filesystem::path folderPath;

	//generate a filePath based on the value of a node
	filesystem::path generateFilePath(const T& value)
	{
		// Construct the file path
		filesystem::path filePath = folderPath;
		if constexpr (is_same<T, String>::value)
		{
			filePath /= value.getData();
		}
		else
		{
			filePath /= to_string(value);
		}
		filePath+=".txt";
		return filePath;
	}

	bool removeFile(filesystem::path& path)
	{
		if (filesystem::exists(path))
		{
			filesystem::remove(path);
			return true;
		}
		return false;
			
	}

	//get height of node
	int Height(const filesystem::path& path)
	{
		if (path.empty() || path== "NULL")
			return -1;
		else
		{
			return Node::readFile(path).height;
		}
	}

	//NOTE : updates height in file
	void updateNodeHeight(const filesystem::path& path)
	{
		if (path.empty() || path == "NULL")
			return;

		Node node = Node::readFile(path);
		int leftHeight = Height(node.left);
		int rightHeight = Height(node.right);

		node.height = max(leftHeight, rightHeight) + 1;
		node.updateFile(path);
		return;
	}

	//BF = Right - Left
	int balanceFactor(const filesystem::path& path)
	{
		Node node = Node::readFile(path);
		int leftHeight = Height(node.left);
		int rightHeight = Height(node.right);

		return rightHeight - leftHeight;
	}

	//========= rotations ===========

	//INPUT: PATH
	//automatically updates parent, old and new pivots
	void rotateRight(filesystem::path& path)
	{
		Node mainNode = Node::readFile(path);
		Node leftNode = Node::readFile(mainNode.left);
		filesystem::path leftNodePath = mainNode.left;
		filesystem::path leftNodeKaRightPath = leftNode.right;

		//attach old pivot with new pivot's left subtree
		mainNode.left = leftNodeKaRightPath;
		if (leftNodeKaRightPath!= "NULL")
		{
			Node leftNodesRight_NODE = Node::readFile(leftNodeKaRightPath);
			leftNodesRight_NODE.parent = path;
			leftNodesRight_NODE.updateFile(leftNodeKaRightPath);
		}

		//attach new pivot with old pivot's parent
		leftNode.parent = mainNode.parent;

		//put old pivot at new pivot's left child
		leftNode.right = path;
		mainNode.parent = leftNodePath;

		//update heights
		mainNode.updateFile(path);
		leftNode.updateFile(leftNodePath);
		updateNodeHeight(path);
		updateNodeHeight(leftNodePath);

		//update the parent if it exists
		if (leftNode.parent!= "NULL")
		{
			Node parentNode = Node::readFile(leftNode.parent);
			parentNode.left == path ? parentNode.left = leftNodePath : parentNode.right = leftNodePath;

			parentNode.updateFile(leftNode.parent);
			updateNodeHeight(leftNode.parent);
		}
		path = leftNodePath;
	}


	//INPUT: PATH
	//automatically updates parent, old and new pivots
	void rotateLeft(filesystem::path& path)
	{
		Node mainNode = Node::readFile(path);
		Node rightNode = Node::readFile(mainNode.right);
		filesystem::path rightNodePath = mainNode.right;
		filesystem::path rightNodeKaLeftPath = rightNode.left;

		//attach old pivot with new pivot's left subtree
		mainNode.right = rightNodeKaLeftPath;
		if (rightNodeKaLeftPath!= "NULL")
		{
			Node rightNodesleft_NODE = Node::readFile(rightNodeKaLeftPath);
			rightNodesleft_NODE.parent = path;
			rightNodesleft_NODE.updateFile(rightNodeKaLeftPath);
		}

		//attach new pivot with old pivot's parent
		rightNode.parent = mainNode.parent;

		//put old pivot at new pivot's left child
		rightNode.left = path;
		mainNode.parent = rightNodePath;

		//update heights
		mainNode.updateFile(path);
		rightNode.updateFile(rightNodePath);
		updateNodeHeight(path);
		updateNodeHeight(rightNodePath);

		//update the parent if it exists
		if (rightNode.parent!= "NULL")
		{
			Node parentNode = Node::readFile(rightNode.parent);
			parentNode.left == path ? parentNode.left = rightNodePath : parentNode.right = rightNodePath;

			parentNode.updateFile(rightNode.parent);
			updateNodeHeight(rightNode.parent);
		}
		path = rightNodePath;

	}

	//returns 1 if rotations occured
	bool balanceNode(filesystem::path& path)
	{
		Node node = Node::readFile(path);
		int BF= balanceFactor(path);

		//right heavy
		if (BF == 2)
		{
			int rightBF = balanceFactor(node.right);

			if (rightBF == 1 || rightBF == 0)
			{
				rotateLeft(path);
			}
			else if (rightBF == -1)
			{
				rotateRight(node.right);
				rotateLeft(path);
			}
			return 1;
		}
		//left heavy
		else if (BF == -2)
		{
			int leftBF = balanceFactor(node.left);

			if (leftBF == -1 || leftBF == 0)
			{
				rotateRight(path);
			}
			else if (leftBF == 1)
			{
				rotateLeft(node.left);
				rotateRight(path);
			}
			return 1;
		}

		return 0;
	}

	//NOTE: updates path sent as parameter
	void helperInsert(filesystem::path& path, const filesystem::path& parentPath, const T& data)
	{
		if (path== "NULL")
		{
			filesystem::path newFilePath = generateFilePath(data);
			Node newNode(data);
			newNode.parent = parentPath;
			path = newFilePath;
			newNode.updateFile(newFilePath);
			return;
		}
		else
		{
			Node current = Node::readFile(path);
			if (data < current.data)
			{
				helperInsert(current.left, path, data);
			}
			else if (data > current.data)
			{
				helperInsert(current.right, path, data);
			}
			else if(data==current.data)
			{
				current.frequency++;
				current.updateFile(path);
				return;
			}
			current.updateFile(path);
			updateNodeHeight(path);

			int BF = balanceFactor(path);
			if (BF == 2 || BF == -2)
			{
				balanceNode(path);
			}
		}
	}

	//Updates path sent as para
	void helperRemove(filesystem::path& path, const T& data)
	{
		//didnt find element
		if (path.empty() || path == "NULL")
		{
			cout << "ERROR IN DELETION: Key \'" << data << "\' does not exist." << endl;
			return;
		}

		Node node = Node::readFile(path);

		//find the element
		if (data < node.data)
		{
			helperRemove(node.left, data);
		}
		else if (data > node.data)
		{
			helperRemove(node.right, data);
		}
		//element found
		else
		{
			//only decrement frequency if it is >1
			if (node.frequency > 1)
			{
				node.frequency--;
				node.updateFile(path);
				return;
			}
			else
			{
				//have to completely remove file

				//Case 1: No left child
				if (node.left == "NULL")
				{
					if (node.right != "NULL")
					{
						Node right = Node::readFile(node.right);
						right.parent = node.parent;
						right.updateFile(node.right);
					}
					if (node.parent != "NULL")
					{
						Node parent = Node::readFile(node.parent);
						parent.left == path ? parent.left = node.right : parent.right = node.right;
						parent.updateFile(node.parent);
						updateNodeHeight(node.parent);
					}
					removeFile(path);
					path = "NULL";
					return;
				}

				//Case 2: No right child
				else if (node.right == "NULL")
				{
					if (node.left != "NULL")
					{
						Node left = Node::readFile(node.left);
						left.parent = node.parent;
						left.updateFile(node.left);
					}
					if (node.parent != "NULL")
					{
						Node parent = Node::readFile(node.parent);
						parent.left == path ? parent.left = node.left : parent.right = node.left;
						parent.updateFile(node.parent);
						updateNodeHeight(node.parent);
					}
					removeFile(path);
					path = "NULL";
					return;
				}

				//Case 3: Both childs exist
				else if (node.right != "NULL" && node.left != "NULL")
				{
					//find inorder successor
					Node successor = Node::readFile(node.right);
					filesystem::path successorPath = node.right;

					while (successor.left != "NULL")
					{
						successorPath = successor.left;
						successor = Node::readFile(successor.left);
					}

					//replace nodes data with successor data
					node.data = successor.data;
					node.frequency = successor.frequency;
					node.hash = successor.hash;
					node.updateFile(path);
					filesystem::path updatedPath = generateFilePath(successor.data);

					//delete successor from right subtree
					successor.frequency = 1;
					successor.updateFile(successorPath);
					helperRemove(node.right, successor.data);
					
					//rename the node that just got replaced and update the new path in all neighbors
					node = Node::readFile(path);
					filesystem::rename(path,updatedPath);
					if (node.parent!= "NULL")
					{
						Node parent = Node::readFile(node.parent);
						parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
						parent.updateFile(node.parent);
					}
					if (node.left != "NULL")
					{
						Node left = Node::readFile(node.left);
						left.parent = updatedPath;
						left.updateFile(node.left);
					}
					if (node.right != "NULL")
					{
						Node right = Node::readFile(node.right);
						right.parent = updatedPath;
						right.updateFile(node.right);
					}
					path = updatedPath;
				}
			}
		}
		//rolling back after deletion, balance any imbalanced nodes
		int BF = balanceFactor(path);
		if (BF >= 2 || BF <= -2)
		{
			balanceNode(path);
		}
	}

	void inorderPrint(const filesystem::path& path, int depth=0)
	{
		if (path.empty() || path == "NULL")
		{
			for (int a = 0; a < depth; a++)
			{
				cout << '\t';
			}
			cout << "-" << endl;
			return;
		}
		Node node = Node::readFile(path);
		inorderPrint(node.right, depth+1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << node.data << endl;
		inorderPrint(node.left, depth+1);
	}

	void helperF(filesystem::path path, int& f)
	{
		if (path == "NULL")
			return;
		Node node = Node::readFile(path);
		helperF(node.left, f);
		f += node.frequency;
		helperF(node.right, f);
	}

public:
	AVL(filesystem::path folderPath, filesystem::path rootPath="NULL") : folderPath(folderPath), rootPath(rootPath)
	{
		if (!filesystem::exists(folderPath))
		{
			filesystem::create_directories(folderPath);
		}
		if (rootPath != "NULL")
		{
			if (!filesystem::exists(rootPath))
				throw runtime_error("Root path does not exist.");
		}
	}

	void insert(const T& data)
	{
		helperInsert(rootPath,"NULL", data);
	}
	void remove(const T& data)
	{
		helperRemove(rootPath, data);
	}

	void print()
	{
		cout << "---------------------------------------------------- "<<endl;
		inorderPrint(rootPath);
	}

	//saves path of root into a file
	void saveRootToFile()
	{
		ofstream file;
		filesystem::path path = folderPath;
		path += "\\ROOT.txt";
		file.open(path);
		if (!file.is_open())
			throw runtime_error("Cannot open file: \'AVL_Root.txt\' for writing.");
		file << rootPath << endl;
		file.close();
	}

	void displayFrequency()
	{
		int f = 0;
		helperF(rootPath, f);
		cout << "Total Frequency:" << f << endl;
	}
};


