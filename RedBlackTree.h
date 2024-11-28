#pragma once

#include <string>
#include <filesystem>
#include "String.h"
using namespace std::filesystem;
enum NodeColor {
	RED,
	BLACK
};


template<class T>
class RedBlackTree {
	//===================================== RedBlackNode Node ==========================================
	struct RedBlackNode {
		T data;
		RedBlackNode* left, * right, * parent;
		string hash;
		NodeColor color;
		filesystem::path path;
		bool debt;
		int frequency;
		RedBlackNode(T data = T(), RedBlackNode* left = nullptr, RedBlackNode* right = nullptr, RedBlackNode* parent = nullptr) {
			this->left = left;
			this->right = right;
			this->parent = parent;
			this->data = data;
			hash = "HASH";
			color = RED;
			debt = false;
			frequency = 1;
			path = "NULL";
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
			file << (this->left ? this->left->path : "NULL");
			file << '\n';
			file << (this->right ? this->right->path : "NULL");
			file << '\n';
			file << (this->parent ? this->parent->path : "NULL");
			file << '\n';
			file << this->debt << '\n';

			file.close();
		}
		string sanitizePath(const string& rawPath) {
			string sanitizedPath = rawPath;

			// Remove surrounding quotes if present
			if (!sanitizedPath.empty() && sanitizedPath.front() == '"' && sanitizedPath.back() == '"') {
				sanitizedPath = sanitizedPath.substr(1, sanitizedPath.size() - 2);
			}

			return sanitizedPath;
		}

		static RedBlackNode readFile(const filesystem::path& path) {
			if (path == "NULL") {
				throw runtime_error("Accessing NULL path");
			}

			ifstream file(path);
			if (!file.is_open()) {
				throw runtime_error("Unable to open file for reading.");
			}

			RedBlackNode node;

			if constexpr (is_same<T, String>::value) {
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

			// Read and sanitize paths
			string left, right, parent;
			file >> left >> right >> parent;

			node.left = (left != "NULL") ? new RedBlackNode() : nullptr;
			if (node.left) {
				//filesystem::path leftPath;
				//cout << left << endl;
				//for (int i = 0; left[i] != '\0'; ++i) {
				//	leftPath += left[i];
				//}
				//cout << leftPath << endl;
				filesystem::path newPath = folderPath;
				// string fileName;
				if constexpr (is_same<T, String>::value) {
					newPath /= node.left->data.getData();
				}
				else {
					newPath /= to_string(node.left->data);
				}
				newPath += ".txt";
				node.left->path = node.left->data;
			}

			node.right = (right != "NULL") ? new RedBlackNode() : nullptr;
			if (node.right) {
				//filesystem::path rightPath;
				//cout << right << endl;
				//for (int i = 0; right[i] != '\0'; ++i) {
				//	rightPath += right[i];
				//}
				//cout << rightPath << endl;
				node.right->path = right;
			}

			node.parent = (parent != "NULL") ? new RedBlackNode() : nullptr;
			if (node.parent) {
				//filesystem::path parentPath;
				//cout << parent << endl;
				//for (int i = 0; right[i] != '\0'; ++i) {
				//	parentPath += right[i];
				//}
				//cout << parentPath << endl;
				node.parent->path = parent;
			}

			file >> node.debt;

			file.close();
			return node;
		}


	};
	filesystem::path createPath(T value) {
		if (!filesystem::exists(folderPath)) {
			cout << "Created file directory successfully: " << folderPath << endl;
			filesystem::create_directories(folderPath);
		}
		filesystem::path newPath = folderPath;
		// string fileName;
		if constexpr (is_same<T, String>::value) {
			newPath /= value.getData();
		}
		else {
			newPath /= to_string(value);
		}
		newPath += ".txt";
		// newPath /= fileName;
		return newPath;
	}
	//===================================== RedBlackNode Functions ==========================================
	//===================================== Encapsulated Functions ==========================================
	
	void rotateRight(RedBlackNode*& node) {
		RedBlackNode* leftNode = node->left;
		RedBlackNode* grandRightNode = leftNode->right;

		node->left = grandRightNode;
		if (grandRightNode != nullptr) {
			grandRightNode->parent = node;
			grandRightNode->updateFile(grandRightNode->path);
		}

		leftNode->parent = node->parent;

		if (node->parent != nullptr) {
			RedBlackNode* parentNode = node->parent;
			if (parentNode->left == node) {
				parentNode->left = leftNode;
			}
			else {
				parentNode->right = leftNode;
			}
			parentNode->updateFile(parentNode->path);
		}
		else {
			root = leftNode;
		}

		leftNode->right = node;
		node->parent = leftNode;
		node->color = RED;
		leftNode->color = BLACK;
		node->updateFile(node->path);
		leftNode->updateFile(leftNode->path);
	}
	void rotateLeft(RedBlackNode*& node) {
		RedBlackNode* rightNode = node->right;
		RedBlackNode* grandLeftNode = rightNode->left;

		node->right = grandLeftNode;
		if (grandLeftNode != nullptr) {
			grandLeftNode->parent = node;
			grandLeftNode->updateFile(grandLeftNode->path);
		}

		rightNode->parent = node->parent;

		if (node->parent != nullptr) {
			RedBlackNode* parentNode = node->parent;
			if (parentNode->right == node) {
				parentNode->right = rightNode;
			}
			else {
				parentNode->left = rightNode;
			}
			parentNode->updateFile(parentNode->path);
		}
		else {
			root = rightNode;
		}

		rightNode->left = node;
		node->parent = rightNode;
		node->color = RED;
		rightNode->color = BLACK;
		node->updateFile(node->path);
		rightNode->updateFile(rightNode->path);
	}
	void fixOrientation_Insertion(RedBlackNode*& node) {
		if (!node) return;
		if (node == root) {
			node->color = BLACK;
			return;
		}
		node->color = RED;
		RedBlackNode* parent = node->parent;
		if (parent->color == RED) {
			RedBlackNode* grand = node->parent->parent;
			RedBlackNode* uncle = nullptr;
			if (parent->data < grand->data) { // parent left so uncle right
				uncle = grand->right;
			}
			else {
				uncle = grand->left;
			}

			if (uncle && uncle->color == RED) {
				uncle->color = BLACK;
				parent->color = BLACK;

				if (grand != root) {
					grand->color = RED;
					grand->updateFile(grand->path);
				}
				uncle->updateFile(uncle->path);
				parent->updateFile(parent->path);
				fixOrientation_Insertion(grand);
			}
			else {
				int data = node->data;
				if (data < parent->data && parent->data < grand->data) { // LL
					rotateRight(grand);
				}
				else if (data > parent->data && parent->data > grand->data) { // RR
					rotateLeft(grand);
				}
				else if (data < parent->data && parent->data > grand->data) { // RL
					rotateRight(parent);
					rotateLeft(grand);
				}
				else if (data > parent->data && parent->data < grand->data) { // LR
					rotateLeft(parent);
					rotateRight(grand);
				}
			}
		}
		root->color = BLACK;
	}
	void insertNode(RedBlackNode*& root, T data) {
		if (root == nullptr) {
			filesystem::path newPath = createPath(data);
			RedBlackNode* newNode = new RedBlackNode(data);
			newNode->parent = nullptr;
			root = newNode;
			newNode->color = BLACK;
			newNode->path = newPath;
			newNode->updateFile(newPath); 
			return;
		}
		else {
			RedBlackNode* curr = root;
			RedBlackNode* parent = nullptr;
			bool isLeftChild = false;

			while (curr) {
				parent = curr; 
				if (curr->data == data) {
					curr->frequency++;
					return;
				}
				else if (curr->data > data) {
					isLeftChild = true;
					curr = curr->left;
				}
				else {
					isLeftChild = false;
					curr = curr->right;
				}
			}

			RedBlackNode* newNode = new RedBlackNode(data);
			newNode->parent = parent;
			filesystem::path newPath = createPath(data);
			newNode->path = newPath;
			if (isLeftChild) {
				parent->left = newNode;
				parent->updateFile(parent->path);
			}
			else {
				parent->right = newNode;
				parent->updateFile(parent->path);
			}
			newNode->updateFile(newNode->path);
			fixOrientation_Insertion(newNode);
		}
	}

	void inorderPrint(RedBlackNode* root, int depth = 0)
	{
		if (!root) return;
		// RedBlackNode node = RedBlackNode::readFile(root->path);
		inorderPrint(root->right, depth + 1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << root->data << "(" << root->color << " , " << root->frequency << ")" << endl;
		inorderPrint(root->left, depth + 1);
	}
	void inorderPrint_File(const filesystem::path path, int depth = 0)
	{
		// cout << path << endl;
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
		inorderPrint_File(node.right->path, depth + 1);
		for (int a = 0; a < depth; a++)
		{
			cout << '\t';
		}
		cout << node.data << "(" << node.color << " , " << node.frequency << ")" << endl;
		inorderPrint_File(node.left->path, depth + 1);
	}
	RedBlackNode* root;
	filesystem::path folderPath;

public:
	RedBlackTree(filesystem::path folderPath) :root(nullptr),folderPath(folderPath) {}
	//===================================== UI Functions ==========================================
	void insert(T value) {
		insertNode(root, value);
	}
	void remove(T value) {
		if (!root) {
			cout << "Tree is empty\n";
			return;
		}
		removeNode(root, value);
	}
	RedBlackNode* Search(RedBlackNode* root, T value) {
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
	RedBlackNode* Root()const { return root; }
	void preOrder() {
		inorderPrint(root);
	}
	void print() {
		inorderPrint_File(root->path);
	}
};