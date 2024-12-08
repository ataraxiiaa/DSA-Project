#pragma once
#include"ParentTree.h"
#include "Vector.h"
#include "String.h"
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

/*
		RED-BLACK TREE
		The class follows the basic principles for redblack tree
		the class contains a node struct and all the functions required to perform operations on the tree
		All the functions are encapsulated and are private
		The class is a template class and can be used with any data type
		The approach follows the double black node approach for deletion

*/
enum NodeColor {
	RED, // 0
	BLACK // 1
};


template<class T>
class RedBlackTree: public ParentTree<T> {
	//===================================== RedBlackNode Node ==========================================
	struct Node {
		T data;
		String hash;
		filesystem::path left; // Left child
		filesystem::path right; // Right child
		filesystem::path parent; // Parent
		NodeColor color; // Color of the node
		bool debt; // Debt of the node if a double black node occurs
		int frequency; // Frequency of the node
		Vector<long long> rowIndexes; // Row indexes of the node
		// Constructor
		Node(T data = T()) {
			this->data = data;
			color = RED;
			debt = false;
			frequency = 1;
			hash = "HASH";
			left = "NULL";
			right = "NULL";
			parent = "NULL";
		}
		// functions required for file handling
		// saves the node to the file
		void updateFile(const filesystem::path& path) {
			if (path == "NULL") {
				throw runtime_error("Unable to find path");
			}
			ofstream file;
			file.open(path);
			if (!file.is_open()) {
				throw runtime_error("Error..Unable to open file for Writing");
			}

			file << this->data << '\n';
			file << this->frequency << '\n';
			for (int a = 0; a < this->frequency; a++)
			{
				if (a > 0)
					file << ' ';
				file << this->rowIndexes[a];
			}
			file << '\n';
			file << this->color << '\n';
			file << this->hash << '\n';
			/*
			The left, right and parent paths are stored as relative paths 
			*/
			file << (this->left == "NULL" ? "NULL" : makeRelative(this->left)) << '\n';
			file << (this->right == "NULL" ? "NULL" : makeRelative(this->right)) << '\n';
			file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';
			file << this->debt << '\n';
			file.close();
		}
		// reads the node from the file
		static Node readFile(const filesystem::path& path, const RedBlackTree& merc) {
			if (path == "NULL") {
				throw runtime_error("Accessing NULL path");
			}
			ifstream file;
			file.open(path);
			if (!file.is_open()) {
				throw runtime_error("Unable to open file for reading..");
			}

			Node node;
			if constexpr (is_same<T, String>::value) {
				getline(file, node.data); 
			}
			else {
				file >> node.data; 
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			file >> node.frequency;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			char delim;
			long long index;
			for (int a = 0; a < node.frequency; a++)
			{
				file >> index;
				node.rowIndexes.push_back(index);
			}
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			int color;
			file >> color;
			node.color = static_cast<NodeColor>(color);
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			getline(file, node.hash);
			filesystem::path temp;

			// the merc.branchPath allows us to get the relative path
			file >> temp;
			if (temp == "NULL")
				node.left = "NULL";
			else
			{
				node.left = merc.branchPath;
				node.left /= temp;
			}

			file >> temp;
			if (temp == "NULL")
				node.right = "NULL";
			else
			{
				node.right = merc.branchPath;
				node.right /= temp;
			}

			file >> temp;
			if (temp == "NULL")
				node.parent = "NULL";
			else
			{
				node.parent = merc.branchPath;
				node.parent /= temp;
			}

			file >> node.debt;

			file.close();
			return node;
		}
	};
	//===================================== File Functions ==========================================
	// helper function to create file path dependent on value
	filesystem::path createPath(const T& value) {

		// Construct the file path
		filesystem::path filePath = folderPath / "NODES";
		if constexpr (is_same<T, String>::value)
		{
			filePath /= value.getData();
		}
		else
		{
			filePath /= value;
		}
		filePath += ".txt";
		return filePath;
	}
	// helper function to remove file
	bool removeFile(filesystem::path& path) {
		if (filesystem::exists(path)) {
			filesystem::remove(path);
			return true;
		}
		return false;

	}
	//===================================== Encapsulated Functions ==========================================
	// function to rotate the tree to the right
	void rotateRight(filesystem::path& path) {
		Node node = Node::readFile(path, *this);

		if (node.left == "NULL") {
			throw runtime_error("Cannot perform right rotation on a node with no left child.");
		}
		// i forgot how it worked but the rotation is same as AVL so figure it out yourself idc
		Node leftNode = Node::readFile(node.left, *this);
		filesystem::path leftPath = node.left;        
		filesystem::path grandRightPath = leftNode.right; 

		node.left = grandRightPath;
		if (grandRightPath != "NULL") {
			Node grandRightNode = Node::readFile(grandRightPath, *this);
			grandRightNode.parent = path; 
			grandRightNode.updateFile(grandRightPath); 
		}

		leftNode.parent = node.parent;

		if (node.parent != "NULL") {
			Node parentNode = Node::readFile(node.parent, *this);
			if (parentNode.left == path) {
				parentNode.left = leftPath; 
			}
			else {
				parentNode.right = leftPath; 
			}
			parentNode.updateFile(node.parent); 
		}
		else {
			rootPath = leftPath;
		}

		leftNode.right = path;
		node.parent = leftPath; 
		node.color = RED;
		leftNode.color = BLACK;
		node.updateFile(path);        
		leftNode.updateFile(leftPath); 
		// path = leftPath;
	}
	// function to rotate the tree to the left
	void rotateLeft(filesystem::path& path) {
		Node node = Node::readFile(path, *this);
		Node rightNode = Node::readFile(node.right, *this);
		// i forgot how it worked but the rotation is same as AVL so figure it out yourself idc
		filesystem::path rightPath = node.right; 
		filesystem::path grandLeftChildPath = rightNode.left; 
		node.right = grandLeftChildPath;

		if (grandLeftChildPath != "NULL") {
			Node grandLeftChildNode = Node::readFile(grandLeftChildPath, *this);
			grandLeftChildNode.parent = path;
			grandLeftChildNode.updateFile(grandLeftChildPath); 
		}
		rightNode.parent = node.parent;

		if (node.parent != "NULL") {
			Node parentNode = Node::readFile(node.parent, *this);
			if (parentNode.left == path) {
				parentNode.left = rightPath; 
			}
			else {
				parentNode.right = rightPath; 
			}
			parentNode.updateFile(node.parent); 
		}
		else {
			rootPath = rightPath;
		}

		rightNode.left = path;
		node.parent = rightPath; 
		node.color = RED;
		rightNode.color = BLACK;
		node.updateFile(path);  
		rightNode.updateFile(rightPath);
		// path = rightPath;
	}
	// function to fix the orientation of the tree after insertion and fix any violations of redblack tree
	void fixOrientation_Insertion(filesystem::path& path) {
		if (path == "NULL") return;
		if (path == rootPath) {
			Node node = Node::readFile(path, *this);
			node.color = BLACK;
			node.updateFile(path);
			return;
		}
		Node node = Node::readFile(path, *this);
		filesystem::path Parentpath = node.parent;
		Node parent = Node::readFile(Parentpath, *this);

		if (parent.color == RED) {
			filesystem::path grandParentPath = parent.parent;
			Node grandParent = Node::readFile(grandParentPath, *this);
			filesystem::path unclePath = grandParent.left == Parentpath ? grandParent.right : grandParent.left;
			Node uncle;
			if (unclePath != "NULL") {
				uncle = Node::readFile(unclePath, *this);
			}

			if (unclePath != "NULL" && uncle.color == RED) {
				uncle.color = BLACK;
				parent.color = BLACK;
				if (grandParentPath != rootPath) {
					grandParent.color = RED;
					grandParent.updateFile(grandParentPath);
				}
				uncle.updateFile(unclePath);
				parent.updateFile(Parentpath);
				// recursively fix the orientation
				fixOrientation_Insertion(grandParentPath);
			}
			else {
				bool isleftChild = (grandParent.left == Parentpath);
				bool isNodeLeftChild = (parent.left == path);
				// 4 cases of rotation
				if (isleftChild && isNodeLeftChild) { // LL
					rotateRight(grandParentPath);
				}
				else if (!isleftChild && !isNodeLeftChild) { // RR
					rotateLeft(grandParentPath);
				}
				else if (isleftChild && !isNodeLeftChild) { // LR
					rotateLeft(Parentpath); // rotate left and then rotate right
					rotateRight(grandParentPath);
				}
				else if (!isleftChild && isNodeLeftChild) { // Rl
					rotateRight(Parentpath); // rotate right and then rotate left
					rotateLeft(grandParentPath);
				}
			}
		}
	}
	// function to insert a node into the tree
	void insertNode(filesystem::path& path, const T& data, const long long& rowIndex) {
		// if the path is null then create a new node
		if (path == "NULL") {
			filesystem::path newPath = createPath(data);
			Node newNode(data);
			newNode.parent = "NULL";
			newNode.rowIndexes.push_back(rowIndex);
			path = newPath;
			newNode.color = BLACK;
			newNode.updateFile(newPath);
			return;
		}
		else {
			// read the node
			Node curr = Node::readFile(path, *this);
			if (data == curr.data) {
				curr.frequency++;
				curr.rowIndexes.push_back(rowIndex);
				curr.updateFile(path);
				return;
			}
			// if the data is less than the current node data
			else if (data < curr.data) {
				if (curr.left == "NULL") {
					filesystem::path newPath = createPath(data);
					Node newNode(data);
					newNode.parent = path;
					newNode.rowIndexes.push_back(rowIndex);
					curr.left = newPath;
					newNode.updateFile(newPath);
					curr.updateFile(path);
					fixOrientation_Insertion(newPath);
					return;
				}
				else {
					// recursively insert the node
					insertNode(curr.left, data, rowIndex);
				}
			}
			// if the data is greater than the current node data
			else if (data > curr.data) {
				if (curr.right == "NULL") {
					filesystem::path newPath = createPath(data);
					Node newNode(data);
					newNode.parent = path;
					newNode.rowIndexes.push_back(rowIndex);
					curr.right = newPath;
					newNode.updateFile(newPath);
					curr.updateFile(path);
					fixOrientation_Insertion(newPath);
					return;
				}
				else {
					insertNode(curr.right, data, rowIndex);
				}
			}
		}
	}
	// function to fix the debt of the tree
	void fixDebt(filesystem::path& path) {
		if (path == "NULL") return; // if the path is null return

		Node parent;
		Node sibling;
		Node node = Node::readFile(path, *this);

		if (node.color == RED) { // if the node is red
			node.color = BLACK; // change the color to black
			node.updateFile(path); // update and return
			return;
		}
		else if (path != rootPath) {
			filesystem::path parentPath = node.parent;
			parent = Node::readFile(parentPath, *this);

			filesystem::path siblingPath = (parent.left == path) ? parent.right : parent.left;
			sibling = Node::readFile(siblingPath, *this);

			// Case 1: Sibling is RED
			if (siblingPath != "NULL" && sibling.color == RED) {
				parent.color = RED;
				sibling.color = BLACK;

				parent.updateFile(parentPath);
				sibling.updateFile(siblingPath);
				// perform rotations according to where node is currently at
				if (sibling.data > parent.data) {
					rotateLeft(parentPath);
				}
				else {
					rotateRight(parentPath);
				}
				// recursively fix the debt
				fixDebt(path);
			}

			// Case 2: Sibling is BLACK
			else if (sibling.color == BLACK) {
				filesystem::path leftNephewPath = sibling.left;
				cout << leftNephewPath << endl;
				filesystem::path rightNephewPath = sibling.right;
				cout << rightNephewPath << endl;
				Node leftNephew = (leftNephewPath != "NULL") ? Node::readFile(leftNephewPath, *this) : Node();
				Node rightNephew = (rightNephewPath != "NULL") ? Node::readFile(rightNephewPath, *this) : Node();

				// Case 2a: One of the sibling's children is RED
				if ((leftNephewPath != "NULL" && leftNephew.color == RED) ||
					(rightNephewPath != "NULL" && rightNephew.color == RED)) {

					// LL Case
					if (sibling.data < parent.data && leftNephewPath != "NULL" && leftNephew.color == RED) {
						leftNephew.color = BLACK;
						sibling.color = parent.color;
						parent.color = BLACK;

						leftNephew.updateFile(leftNephewPath);
						sibling.updateFile(siblingPath);
						parent.updateFile(parentPath);

						rotateRight(parentPath);
					}
					// RR Case
					else if (sibling.data > parent.data && rightNephewPath != "NULL" && rightNephew.color == RED) {
						rightNephew.color = BLACK;
						sibling.color = parent.color;
						parent.color = BLACK;

						rightNephew.updateFile(rightNephewPath);
						sibling.updateFile(siblingPath);
						parent.updateFile(parentPath);

						rotateLeft(parentPath);
					}
					// LR Case
					else if (sibling.data < parent.data && rightNephewPath != "NULL" && rightNephew.color == RED) {
						rightNephew.color = BLACK;
						sibling.color = RED;

						rightNephew.updateFile(rightNephewPath);
						sibling.updateFile(siblingPath);

						rotateLeft(siblingPath);

						leftNephew = Node::readFile(sibling.left, *this);
						leftNephew.color = BLACK;
						sibling.color = parent.color;
						parent.color = BLACK;

						leftNephew.updateFile(sibling.left);
						sibling.updateFile(siblingPath);
						parent.updateFile(parentPath);

						rotateRight(parentPath);
					}
					// RL Case
					else if (sibling.data > parent.data && leftNephewPath != "NULL" && leftNephew.color == RED) {
						leftNephew.color = BLACK;
						sibling.color = RED;

						leftNephew.updateFile(leftNephewPath);
						sibling.updateFile(siblingPath);

						rotateRight(siblingPath);

						rightNephew = Node::readFile(sibling.right, *this);
						rightNephew.color = BLACK;
						sibling.color = parent.color;
						parent.color = BLACK;

						rightNephew.updateFile(sibling.right);
						sibling.updateFile(siblingPath);
						parent.updateFile(parentPath);

						rotateLeft(parentPath);
					}
				}
				// Case 2b: Both of sibling's children are BLACK
				else {
					sibling.color = RED;
					sibling.updateFile(siblingPath);

					if (parent.color == RED) {
						parent.color = BLACK;
						parent.updateFile(parentPath);
					}
					else if (parent.color == BLACK && parentPath != rootPath)
					{
						fixDebt(parentPath);
					}
				}
			}
		}
		if (path == rootPath) {
			node.color = BLACK;
			node.updateFile(path);
			return;
		}
		if (path != "NULL" && node.debt) {
			if (parent.left == path)
				parent.left = "NULL";
			else
				parent.right = "NULL";
			parent.updateFile(node.parent);
			removeFile(path);
			path = "NULL";
			return;
		}
	}
	// function used to fix the orientation of the tree after deletion and fix any violations of redblack tree
	void fixOrientation_Deletion(filesystem::path& path, bool hasDebt) {
		if (path == "NULL") return;
		Node node = Node::readFile(path, *this);
		if (node.color == RED) { // removal was of a red node
			node.color = BLACK;
			node.updateFile(path); // simply change the color to black
			return;
		}
		else if(path != rootPath && hasDebt)
		{
			// the case where the node has debt comes
			fixDebt(path);
		}
	}
	// Remove a node from the tree
	void removeNode(filesystem::path& path, const T& data, const long long& rowIndex) {
		if (path.empty() || path == "NULL") // tree empty
		{
			cout << "Unable to find key..Does not exist\n";
			return;
		}
		Node node = Node::readFile(path, *this); // Read the node
		if (data < node.data) {
			removeNode(node.left, data, rowIndex); // traverse to find the node
		}
		else if (data > node.data) {
			removeNode(node.right, data, rowIndex);
		}
		// found Node
		else {
			if (node.frequency > 1) { // if the node has multiple instances
				bool found = 0;
				for (int a = 0; a < node.rowIndexes.getCurr(); a++)
				{
					if (node.rowIndexes[a] == rowIndex)
					{
						node.rowIndexes.Destroy(a);
						found = 1;
						break;
					}
				}
				if (found) // if the node is found
				{
					node.frequency--;
					node.updateFile(path);
				}
				return;
			}
			int numofChildren = 0;
			if (node.left != "NULL") numofChildren++;
			if (node.right != "NULL") numofChildren++;
			if (numofChildren <= 1) {
				// double debt case
				if ((node.left != "NULL" && node.right == "NULL") ||
					(node.right != "NULL" && node.left == "NULL") ||
					node.right == "NULL" && node.left == "NULL") {
					// mark debt if it borrows from a black node
					if (node.color == BLACK) {
						if (node.left == "NULL" && node.right == "NULL") {
							node.debt = true;
							node.updateFile(path); // basically NULL is also black so marks debt black
						}
						// any one of the child is black
						else if (node.left != "NULL") {
							Node temp = Node::readFile(node.left, *this);
							if (temp.color == BLACK) {
								node.debt = true;
								node.updateFile(path);
							}
						}
						else if (node.right != "NULL") {
							Node temp = Node::readFile(node.right, *this);
							if (temp.color == BLACK) {
								node.debt = true;
								node.updateFile(path);
							}
						}
					}
				}
				// No children
				if (node.left == "NULL" && node.right == "NULL") {
					// if the node is the root
					if (path == rootPath) {
						path = "NULL";
						return;
					}
					else if(node.color == RED)
					{
						// if the node is red just simply remove it
						filesystem::path parentPath = node.parent;
						Node parent = Node::readFile(parentPath, *this);
						// sets parent left or right to NULL
						if (rootPath != "NULL") {
							if (parent.left == path) {
								parent.left = "NULL";
							}
							else {
								parent.right = "NULL";
							}
							parent.updateFile(parentPath);
						}
						// remove the file
						removeFile(path);
						path = "NULL";
						return;
					}
					// fixing orientation in case 2 blacks are joined together due to deletion
					fixOrientation_Deletion(path, node.debt);
					// cout << path << endl;
					return;
					/*removeFile(path);
					return;*/
				}
				// 1 children
				// right child
				else if (node.left == "NULL") {
					// checking if node left or right
					if (node.right != "NULL")
					{
						// reads the necassary nodes 
						Node right = Node::readFile(node.right, *this);
						right.parent = node.parent;
						right.updateFile(node.right);
					}
					if (node.parent != "NULL")
					{
						// reading the necassary nodes
						Node parent = Node::readFile(node.parent, *this);
						parent.left == path ? parent.left = node.right : parent.right = node.right;
						parent.updateFile(node.parent);
					}
					// fixes any violation of redblack tree properties
					fixOrientation_Deletion(node.right, node.debt);
					removeFile(path);
					path = "NULL";

				}
				// left child
				else if (node.right == "NULL") {
					if (node.left != "NULL")
					{
						Node left = Node::readFile(node.left, *this);
						left.parent = node.parent;
						left.updateFile(node.left);
					}
					// checking if node left or right to parent
					if (node.parent != "NULL")
					{
						Node parent = Node::readFile(node.parent, *this);
						parent.right == path ? parent.right = node.left : parent.left = node.left;
						parent.updateFile(node.parent);
					}
					// fixes any violation of redblack tree properties
					fixOrientation_Deletion(node.left, node.debt);
					removeFile(path);
					path = "NULL";
				}
			}
			// has 2 children
			else {
				// both child exist
				// in this case we used successor approach
				if (node.left != "NULL" && node.right != "NULL") {
					Node successor = Node::readFile(node.left, *this);
					filesystem::path successorPath = node.left;
					// finds the successor
					while (successor.right != "NULL") {
						successorPath = successor.right;
						successor = Node::readFile(successor.right, *this);
					}
					// changes node with successor
					node.data = successor.data;
					node.frequency = successor.frequency;
					node.rowIndexes = successor.rowIndexes;
					node.hash = successor.hash;
					node.updateFile(path);
					filesystem::path updatedPath = createPath(successor.data);
					successor.frequency = 1;
					successor.updateFile(successorPath);
					// removes the successor
					removeNode(node.left, successor.data, rowIndex);

					node = Node::readFile(path, *this);
					// updates file names
					filesystem::rename(path, updatedPath);
					// updates the parent
					if (node.parent != "NULL")
					{
						Node parent = Node::readFile(node.parent, *this);
						parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
						parent.updateFile(node.parent);
					}
					// updates the children
					if (node.left != "NULL")
					{
						Node left = Node::readFile(node.left, *this);
						left.parent = updatedPath;
						left.updateFile(node.left);
					}
					if (node.right != "NULL")
					{
						Node right = Node::readFile(node.right, *this);
						right.parent = updatedPath;
						right.updateFile(node.right);
					}
					// updates the current path 
					path = updatedPath;
				}
			}
		}
	}
	// Print the tree
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
		Node node = Node::readFile(path, *this);
		inorderPrint(node.right, depth + 1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << node.data <<"("<<node.color<<" , "<<node.frequency<<")"<<endl;
		inorderPrint(node.left, depth + 1);
	}
	// Search for a value in the tree
	Node helperSearch(const filesystem::path& root, const T& value) {
		if (root == "NULL") {
			return Node(); // tree empty Return an empty node
		}

		Node currentNode = Node::readFile(root, *this);
		// using recursion to search for the value and return the node
		// using the balanced search tree property
		if (value < currentNode.data) {
			return helperSearch(currentNode.left, value);
		}
		else if (value > currentNode.data) {
			return helperSearch(currentNode.right, value);
		}
		else {
			return currentNode; // return the node
		}
	}
public:
	// Paths
	filesystem::path Root()const { return rootPath; }
	RedBlackTree()
	{}
	// Constructor
	RedBlackTree(filesystem::path branchPath)
	{
		// Set the paths
		this->branchPath = branchPath;
		this->folderPath = branchPath;
		this->rootPath = "NULL"; // Set the root path to NULL
		this->folderPath /= "TREE"; // Append the TREE folder
		if (!filesystem::exists(this->folderPath))
		{
			// Create the directories
			filesystem::create_directories(this->folderPath);
			filesystem::path nodesPath = this->folderPath / "NODES";
			filesystem::create_directories(nodesPath);
		}
	}
	// Load the tree from a branch constructor
	RedBlackTree(bool loadTreeFromBranch, filesystem::path branchPath)
	{
		if (loadTreeFromBranch)
		{
			loadFromBranch(branchPath);
		}
	}
	//===================================== UI Functions ==========================================
	
	// Insert a value into the tree
	void insert(const T& value, const long long& rowIndex) {
		insertNode(this->rootPath, value, rowIndex);
	}
	
	// Remove a value from the tree
	void remove(const T& value, const long long& rowIndex) {
		if (rootPath == "NULL") {
			throw runtime_error("Tree is Empty.");
		}
		removeNode(this->rootPath, value, rowIndex); // Remove the node
	}
	// Print the tree
	void print() {
		inorderPrint(rootPath); 
	}
	// Search for a value in the tree
	Vector<long long>search(const T& data)
	{
		Node node = this->helperSearch(this->rootPath, data); // Search for the node
		if (node.rowIndexes.getCurr() == 0)
		{
			cout << "No instances of key: " << data << " exist." << endl;
			return Vector<long long>(); // Return an empty vector
		}
		else
		{
			return node.rowIndexes; // Return the row indexes
		}
	}
	// Save data to file
	void saveDataToFile()
	{
		ofstream file;
		filesystem::path path = folderPath;
		path += "\\TREE_DATA.txt";
		file.open(path);
		if (!file.is_open())
			throw runtime_error("Cannot open file: \'RB_DATA.txt\' for writing.");
		file << rootPath << '\n';
		file << folderPath << '\n';
		file << branchPath << '\n';
		file.close();
	}
	// Load data from file
	void loadFromBranch(path branchPath)
	{
		branchPath /= "TREE";
		branchPath /= "TREE_DATA.txt";
		if (!exists(branchPath))
			throw runtime_error("File to load tree from doesnt exist.");
		ifstream file(branchPath);
		if (!file.is_open())
			throw runtime_error("Cannot open file: \'RB_DATA.txt\' for reading.");
		file >> rootPath; // Read the root path
		file >> folderPath; // Read the folder path
		file >> this->branchPath; // Read the branch path
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character
		file.close();
	}


};