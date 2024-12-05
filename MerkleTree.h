#pragma once
#include<iostream>
#include "String.h"
#include "RowEntry.h"
#include <fstream>
#include<filesystem>
using namespace std;

class MerkleTree
{
private:

	//===================================== Merkle Node ==========================================
	struct Node
	{
		long long index;
		int height;
		RowEntry rowData;
		String hash;
		filesystem::path left;	 //left child path
		filesystem::path right;	 //right child path
		filesystem::path parent;	 //parent path

		Node(int index=-1, RowEntry rowData=RowEntry()) : index(index), rowData(rowData), height(0), hash("InsertHashHere"), left("NULL"), right("NULL"), parent("NULL")
		{}

		void updateFile(const filesystem::path& path)
		{
			if (path == "NULL")
				throw runtime_error("Attempting to access empty path.");

			ofstream file;
			file.open(path);
			if (!file.is_open())
				throw runtime_error("Cannot open file for writing.");

			file << this->index << '\n';
			file << this->height << '\n';
			file << this->rowData << '\n';
			file << this->hash << '\n';
			file << this->left << '\n';
			file << this->right << '\n';
			file << this->parent << '\n';

			file.close();
		}

		static Node readFile(const filesystem::path& path)
		{
			if (path == "NULL")
				throw runtime_error("Attempting to access empty path.");

			ifstream file;
			file.open(path);
			if (!file.is_open())
				throw runtime_error("Cannot open file for reading.");

			Node node;
			file >> node.index;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			file >> node.height;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			file >> node.rowData;
			getline(file, node.hash);
			file >> node.left;
			file >> node.right;
			file >> node.parent;

			file.close();
			return node;
		}
	};

	// ===================================== AVL functions ==========================================
	
	//generate a filePath based on the value of a node
	template<class T>
	filesystem::path generateFilePath(const T& value)
	{
		// Construct the file path
		filesystem::path filePath = folderPath / "NODES";
		filePath /= to_string(value);
		filePath += ".txt";
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
		if (path.empty() || path == "NULL")
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
		if (leftNodeKaRightPath != "NULL")
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
		if (leftNode.parent != "NULL")
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
		if (rightNodeKaLeftPath != "NULL")
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
		if (rightNode.parent != "NULL")
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
		int BF = balanceFactor(path);

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
	void helperInsert(filesystem::path& path, const filesystem::path& parentPath, const long long& index, const RowEntry& row)
	{
		if (path == "NULL")
		{
			filesystem::path newFilePath = generateFilePath(index);
			Node newNode(index,row);
			newNode.parent = parentPath;
			path = newFilePath;
			newNode.updateFile(newFilePath);
			return;
		}
		else
		{
			Node current = Node::readFile(path);
			if (index < current.index)
			{
				helperInsert(current.left, path, index,row);
			}
			else if (index > current.index)
			{
				helperInsert(current.right, path, index,row);
			}
			else if (index == current.index)
			{
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
	void helperRemove(filesystem::path& path, const long long& index)
	{
		//didnt find element
		if (path.empty() || path == "NULL")
		{
			cout << "ERROR IN DELETION: Key \'" << index << "\' does not exist." << endl;
			return;
		}

		Node node = Node::readFile(path);

		//find the element
		if (index < node.index)
		{
			helperRemove(node.left, index);
		}
		else if (index > node.index)
		{
			helperRemove(node.right, index);
		}
		//element found
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
					node.index = successor.index;
					node.rowData = successor.rowData;
					node.hash = successor.hash;
					node.updateFile(path);
					filesystem::path updatedPath = generateFilePath(successor.index);

					helperRemove(node.right, successor.index);

					//rename the node that just got replaced and update the new path in all neighbors
					node = Node::readFile(path);
					filesystem::rename(path, updatedPath);
					if (node.parent != "NULL")
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
		//rolling back after deletion, balance any imbalanced nodes
		int BF = balanceFactor(path);
		if (BF >= 2 || BF <= -2)
		{
			balanceNode(path);
		}
	}

	void inorderPrint(const filesystem::path& path, int depth = 0)
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
		inorderPrint(node.right, depth + 1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << node.index << endl;
		inorderPrint(node.left, depth + 1);
	}
public:


	filesystem::path rootPath;
	filesystem::path folderPath;

	MerkleTree(filesystem::path folderPath, filesystem::path rootPath = "NULL") : folderPath(folderPath), rootPath(rootPath)
	{
		this->folderPath /= "MerkleTree" ;
		if (!filesystem::exists(this->folderPath))
		{
			filesystem::create_directories(this->folderPath);
			filesystem::path nodesPath = this->folderPath / "NODES";
			filesystem::create_directories(nodesPath);
		}
		if (rootPath != "NULL")
		{
			if (!filesystem::exists(this->rootPath))
				throw runtime_error("Root path does not exist.");
		}
	}

	void insert(const long long& index, const RowEntry& row)
	{
		helperInsert(rootPath, "NULL", index,row);
	}
	void remove(const long long& index)
	{
		helperRemove(rootPath, index);
	}

	void print() 
	{
		cout << "---------------------------------------------------- " << endl;
		inorderPrint(rootPath);
	}

	//saves path of root into a file
	void saveDataToFile()
	{
		ofstream file;
		filesystem::path path = folderPath;
		path += "\\MERKLE_DATA.txt";
		file.open(path);
		if (!file.is_open())
			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for writing.");
		file << rootPath << '\n';
		file << folderPath << '\n';
		file.close();
	}

};


