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
	void insertNode(filesystem::path& path,T data) {
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
	filesystem::path root;
	filesystem::path folderPath;

public:
	filesystem::path Root()const { return root; }
	RedBlackTree(filesystem::path folderPath,filesystem::path root = "NULL") :root(root),folderPath(folderPath) {}
	//===================================== UI Functions ==========================================
	void insert(T value) {
		insertNode(root, value);
	}
	/*
	void remove(T value) {
		if (!root) {
			cout << "Tree is empty\n";
			return;
		}
		removeNode(root, value);
	}
	RedBlackNode* Search(RedBlackNode* root,T value) {
		if (!root) {
			cout << "Unable to find value..\n";
			return nullptr;
		}
		if (value < root->data) {
			Search(root->left, value);
		}
		else if (value > root->data) {
			Search(root->right, value);
		}
		else {
			return root;
		}
	}
	void helper(RedBlackNode* root) {
		if (root) {
			cout << root->data << " " << "(";
			if (root->color) cout << "BLACK";
			else cout << "RED";
			cout << ") ";
			helper(root->left);
			helper(root->right);
		}
	}
	void preOrder() {
		helper(root);
	}*/
};