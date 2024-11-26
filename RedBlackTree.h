#pragma once

#include <string>
#include <iostream>
#include <filesystem>
using namespace std;
using namespace std::filesystem;

enum NodeColor {
	RED, // 0
	BLACK // 1
};


template<class T>
class RedBlackTree {
	//===================================== RedBlackNode Node ==========================================
	struct RedBlackNode {
		T data;
		string hash;
		filesystem::path left;
		filesystem::path right;
		filesystem::path parent;
		NodeColor color;
		bool debt;
		int frequency;
		RedBlackNode(T data = T()) {
			this->data = data;
			color = RED;
			debt = false;
			frequency = 1;
			hash = "HASH";
			left = "NULL";
			right = "NULL";
			parent = "NULL";
		}
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
			file << this->color << '\n';
			file << this->hash << '\n';
			file << this->left << '\n';
			file << this->right << '\n';
			file << this->parent << '\n';
			file << this->debt << '\n';
			file.close();
		}
		static RedBlackNode readFile(const filesystem::path& path) {
			if (path == "NULL") {
				throw runtime_error("Accessing NULL path");
			}
			ifstream file;
			file.open(path);
			if (!file.is_open()) {
				throw runtime_error("Unable to open file for reading..");
			}

			RedBlackNode node;
			if constexpr (is_same<T, string>::value) {
				getline(file, node.data); 
			}
			else {
				file >> node.data; 
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			file >> node.frequency;
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			int color;
			file >> color;
			node.color = static_cast<NodeColor>(color);
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			getline(file, node.hash);
			file >> node.left;
			file >> node.right;
			file >> node.parent;
			file >> node.debt;

			file.close();
			return node;
		}
	};
	//===================================== File Functions ==========================================
	filesystem::path createPath(T value) {
		if (!filesystem::exists(folderPath)) {
			cout << "Created file directory successfully: "<<folderPath << endl;
			filesystem::create_directories(folderPath);
		}
		filesystem::path newPath = folderPath;
		string fileName;
		if constexpr (is_same<T, string>::value) {
			fileName = value;
		}
		else {
			fileName = to_string(value);
		}
		fileName += ".txt";
		newPath /= fileName;
		return newPath;
	}
	bool removeFile(filesystem::path& path) {
		if (filesystem::exists(path)) {
			filesystem::remove(path);
			return true;
		}
		return false;

	}
	//===================================== RedBlackNode Functions ==========================================
	//===================================== Encapsulated Functions ==========================================
	void rotateRight(filesystem::path& path) {
		RedBlackNode node = RedBlackNode::readFile(path);

		if (node.left == "NULL") {
			throw runtime_error("Cannot perform right rotation on a node with no left child.");
		}
		RedBlackNode leftNode = RedBlackNode::readFile(node.left);
		filesystem::path leftPath = node.left;        
		filesystem::path grandRightPath = leftNode.right; 

		node.left = grandRightPath;
		if (grandRightPath != "NULL") {
			RedBlackNode grandRightNode = RedBlackNode::readFile(grandRightPath);
			grandRightNode.parent = path; 
			grandRightNode.updateFile(grandRightPath); 
		}

		leftNode.parent = node.parent;

		if (node.parent != "NULL") {
			RedBlackNode parentNode = RedBlackNode::readFile(node.parent);
			if (parentNode.left == path) {
				parentNode.left = leftPath; 
			}
			else {
				parentNode.right = leftPath; 
			}
			parentNode.updateFile(node.parent); 
		}
		else {
			root = leftPath;
		}

		leftNode.right = path;
		node.parent = leftPath; 
		node.color = RED;
		leftNode.color = BLACK;
		node.updateFile(path);        
		leftNode.updateFile(leftPath); 
		// path = leftPath;
	}
	void rotateLeft(filesystem::path& path) {
		RedBlackNode node = RedBlackNode::readFile(path);
		RedBlackNode rightNode = RedBlackNode::readFile(node.right);

		filesystem::path rightPath = node.right; 
		filesystem::path grandLeftChildPath = rightNode.left; 
		node.right = grandLeftChildPath;

		if (grandLeftChildPath != "NULL") {
			RedBlackNode grandLeftChildNode = RedBlackNode::readFile(grandLeftChildPath);
			grandLeftChildNode.parent = path;
			grandLeftChildNode.updateFile(grandLeftChildPath); 
		}
		rightNode.parent = node.parent;

		if (node.parent != "NULL") {
			RedBlackNode parentNode = RedBlackNode::readFile(node.parent);
			if (parentNode.left == path) {
				parentNode.left = rightPath; 
			}
			else {
				parentNode.right = rightPath; 
			}
			parentNode.updateFile(node.parent); 
		}
		else {
			root = rightPath;
		}

		rightNode.left = path;
		node.parent = rightPath; 
		node.color = RED;
		rightNode.color = BLACK;
		node.updateFile(path);  
		rightNode.updateFile(rightPath);
		// path = rightPath;
	}

	void fixOrientation_Insertion(filesystem::path& path) {
		if (path == "NULL") return;
		if (path == root) {
			RedBlackNode node = RedBlackNode::readFile(path);
			node.color = BLACK;
			node.updateFile(path);
			return;
		}
		RedBlackNode node = RedBlackNode::readFile(path);
		filesystem::path Parentpath = node.parent;
		RedBlackNode parent = RedBlackNode::readFile(Parentpath);

		if (parent.color == RED) {
			filesystem::path grandParentPath = parent.parent;
			RedBlackNode grandParent = RedBlackNode::readFile(grandParentPath);
			filesystem::path unclePath = grandParent.left == Parentpath ? grandParent.right : grandParent.left;
			RedBlackNode uncle;
			if (unclePath != "NULL") {
				uncle = RedBlackNode::readFile(unclePath);
			}

			if (unclePath != "NULL" && uncle.color == RED) {
				uncle.color = BLACK;
				parent.color = BLACK;
				if (grandParentPath != root) {
					grandParent.color = RED;
					grandParent.updateFile(grandParentPath);
				}
				uncle.updateFile(unclePath);
				parent.updateFile(Parentpath);
			}
			else {
				bool isleftChild = (grandParent.left == Parentpath);
				bool isNodeLeftChild = (parent.left == path);

				if (isleftChild && isNodeLeftChild) { // LL
					rotateRight(grandParentPath);
				}
				else if (!isleftChild && !isNodeLeftChild) { // RR
					rotateLeft(grandParentPath);
				}
				else if (isleftChild && !isNodeLeftChild) { // LR
					rotateLeft(Parentpath);
					rotateRight(grandParentPath);
				}
				else if (!isleftChild && isNodeLeftChild) { // Rl
					rotateRight(Parentpath);
					rotateLeft(grandParentPath);
				}
			}
		}
	}
	void insertNode(filesystem::path& path, T data) {
		if (path == "NULL") {
			filesystem::path newPath = createPath(data);
			RedBlackNode newNode(data);
			newNode.parent = "NULL";
			path = newPath;
			newNode.color = BLACK;
			newNode.updateFile(newPath);
			return;
		}
		else {
			RedBlackNode curr = RedBlackNode::readFile(path);
			if (data == curr.data) {
				curr.frequency++;
				curr.updateFile(path);
				return;
			}
			else if (data < curr.data) {
				if (curr.left == "NULL") {
					filesystem::path newPath = createPath(data);
					RedBlackNode newNode(data);
					newNode.parent = path;
					curr.left = newPath;
					newNode.updateFile(newPath);
					curr.updateFile(path);
					fixOrientation_Insertion(newPath);
					return;
				}
				else {
					insertNode(curr.left, data);
				}
			}
			else if (data > curr.data) {
				if (curr.right == "NULL") {
					filesystem::path newPath = createPath(data);
					RedBlackNode newNode(data);
					newNode.parent = path;
					curr.right = newPath;
					newNode.updateFile(newPath);
					curr.updateFile(path);
					fixOrientation_Insertion(newPath);
					return;
				}
				else {
					insertNode(curr.right, data);
				}
			}
		}
	}
	void fixDebt(filesystem::path& path) {
		if (path == "NULL" ) return;
		RedBlackNode parent;
		RedBlackNode sibling;
		RedBlackNode node = RedBlackNode::readFile(path);

		if (node.color == RED) {
			node.color = BLACK;
			node.updateFile(path);
			return;
		}
		else if (path != root) {
			filesystem::path parentPath = node.parent;
			parent = RedBlackNode::readFile(parentPath);

			filesystem::path siblingPath = (parent.left == path) ? parent.right : parent.left;
			sibling = RedBlackNode::readFile(siblingPath);

			// Case 1: Sibling is RED
			if (siblingPath != "NULL" && sibling.color == RED) {
				parent.color = RED;
				sibling.color = BLACK;

				parent.updateFile(parentPath);
				sibling.updateFile(siblingPath);

				if (sibling.data > parent.data) {
					rotateLeft(parentPath);
				}
				else {
					rotateRight(parentPath);
				}

				fixDebt(path);
			}

			// Case 2: Sibling is BLACK
			else if (sibling.color == BLACK) {
				filesystem::path leftNephewPath = sibling.left;
				cout << leftNephewPath << endl;
				filesystem::path rightNephewPath = sibling.right;
				cout << rightNephewPath << endl;
				RedBlackNode leftNephew = (leftNephewPath != "NULL") ? RedBlackNode::readFile(leftNephewPath) : RedBlackNode();
				RedBlackNode rightNephew = (rightNephewPath != "NULL") ? RedBlackNode::readFile(rightNephewPath) : RedBlackNode();

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

						leftNephew = RedBlackNode::readFile(sibling.left);
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

						rightNephew = RedBlackNode::readFile(sibling.right);
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
					else if (parent.color == BLACK && parentPath != root)
					{
						fixDebt(parentPath);
					}
				}
			}
		}
		if (path == root) {
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

	void fixOrientation_Deletion(filesystem::path& path, bool hasDebt) {
		if (path == "NULL") return;
		RedBlackNode node = RedBlackNode::readFile(path);
		if (node.color == RED) {
			node.color = BLACK;
			node.updateFile(path);
			return;
		}
		else if(path != root && hasDebt)
		{
			fixDebt(path);
		}
	}
	void removeNode(filesystem::path& path, const T& data) {
		if (path.empty() || path == "NULL")
		{
			cout << "Unable to find value..Does not exist\n";
			return;
		}
		RedBlackNode node = RedBlackNode::readFile(path);
		if (data < node.data) {
			removeNode(node.left, data);
		}
		else if (data > node.data) {
			removeNode(node.right, data);
		}
		// found Node
		else {
			if (node.frequency > 1) {
				node.frequency--;
				node.updateFile(path);
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
					if (node.color == BLACK) {
						if (node.left == "NULL" && node.right == "NULL") {
							node.debt = true;
							node.updateFile(path);
						}
						else if (node.left != "NULL") {
							RedBlackNode temp = RedBlackNode::readFile(node.left);
							if (temp.color == BLACK) {
								node.debt = true;
								node.updateFile(path);
							}
						}
						else if (node.right != "NULL") {
							RedBlackNode temp = RedBlackNode::readFile(node.right);
							if (temp.color == BLACK) {
								node.debt = true;
								node.updateFile(path);
							}
						}
					}
				}
				// No children
				if (node.left == "NULL" && node.right == "NULL") {
					if (path == root) {
						path = "NULL";
						return;
					}
					else if(node.color == RED)
					{
						filesystem::path parentPath = node.parent;
						RedBlackNode parent = RedBlackNode::readFile(parentPath);
						if (root != "NULL") {
							if (parent.left == path) {
								parent.left = "NULL";
							}
							else {
								parent.right = "NULL";
							}
							parent.updateFile(parentPath);
						}
						removeFile(path);
						path = "NULL";
						return;
					}
					fixOrientation_Deletion(path, node.debt);
					cout << path << endl;
					return;
					/*removeFile(path);
					return;*/
				}
				// 1 children
				else if (node.left == "NULL") {
					if (node.right != "NULL")
					{
						RedBlackNode right = RedBlackNode::readFile(node.right);
						right.parent = node.parent;
						right.updateFile(node.right);
					}
					if (node.parent != "NULL")
					{
						RedBlackNode parent = RedBlackNode::readFile(node.parent);
						parent.left == path ? parent.left = node.right : parent.right = node.right;
						parent.updateFile(node.parent);
					}
				
					fixOrientation_Deletion(node.right, node.debt);
					removeFile(path);
					path = "NULL";

				}
				else if (node.right == "NULL") {
					if (node.left != "NULL")
					{
						RedBlackNode left = RedBlackNode::readFile(node.left);
						left.parent = node.parent;
						left.updateFile(node.left);
					}
					if (node.parent != "NULL")
					{
						RedBlackNode parent = RedBlackNode::readFile(node.parent);
						parent.right == path ? parent.right = node.left : parent.left = node.left;
						parent.updateFile(node.parent);
					}
					fixOrientation_Deletion(node.left, node.debt);
					removeFile(path);
					path = "NULL";
				}
			}
			else {
				// both child exist
				if (node.left != "NULL" && node.right != "NULL") {
					RedBlackNode successor = RedBlackNode::readFile(node.left);
					filesystem::path successorPath = node.left;
					while (successor.right != "NULL") {
						successorPath = successor.right;
						successor = RedBlackNode::readFile(successor.right);
					}
					node.data = successor.data;
					node.frequency = successor.frequency;
					node.hash = successor.hash;
					node.updateFile(path);
					filesystem::path updatedPath = createPath(successor.data);
					successor.frequency = 1;
					successor.updateFile(successorPath);
					removeNode(node.left, successor.data);

					node = RedBlackNode::readFile(path);
					filesystem::rename(path, updatedPath);
					if (node.parent != "NULL")
					{
						RedBlackNode parent = RedBlackNode::readFile(node.parent);
						parent.left == path ? parent.left = updatedPath : parent.right = updatedPath;
						parent.updateFile(node.parent);
					}
					if (node.left != "NULL")
					{
						RedBlackNode left = RedBlackNode::readFile(node.left);
						left.parent = updatedPath;
						left.updateFile(node.left);
					}
					if (node.right != "NULL")
					{
						RedBlackNode right = RedBlackNode::readFile(node.right);
						right.parent = updatedPath;
						right.updateFile(node.right);
					}
					path = updatedPath;
				}
			}
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
		RedBlackNode node = RedBlackNode::readFile(path);
		inorderPrint(node.right, depth + 1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << node.data <<"("<<node.color<<")"<<endl;
		inorderPrint(node.left, depth + 1);
	}
	filesystem::path root;
	filesystem::path folderPath;

public:
	filesystem::path Root()const { return root; }
	RedBlackTree(filesystem::path folderPath,filesystem::path root = "NULL") :root(root),folderPath(folderPath) {}
	//===================================== UI Functions ==========================================
	void insert(T value) {
		insertNode(root, value);
	}
	
	void remove(T value) {
		if (root == "NULL") {
			throw runtime_error("Tree is Empty.");
		}
		removeNode(root, value);
	}
	void print() {
		inorderPrint(root);
	}
	filesystem::path Search(filesystem::path root, T value) {
		if (root == "NULL") {
			cout << "Unable to find the searched value: " << value << endl;
			return "NULL";
		}

		RedBlackNode currentNode = RedBlackNode::readFile(root);

		if (value < currentNode.data) {
			return Search(currentNode.left, value); 
		}
		else if (value > currentNode.data) {
			return Search(currentNode.right, value); 
		}
		else {
			cout << "Value found: " << value << " at path: " << root << endl;
			return root; 
		}
	}
};