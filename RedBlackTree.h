#pragma once

#include <string>
#include <iostream>
using namespace std;

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
		NodeColor color;
		bool debt;
		int frequency;
		RedBlackNode(T data, RedBlackNode* left = nullptr, RedBlackNode* right = nullptr, RedBlackNode* parent = nullptr) {
			this->left = left;
			this->right = right;
			this->parent = parent;
			this->data = data;
			color = RED;
			debt = false;
			frequency = 1;
		}
	};
	RedBlackNode* root;
	//===================================== RedBlackNode Functions ==========================================
	void rotateRight(RedBlackNode*& node) {
		RedBlackNode* temp = node->left;
		node->left = temp->right;
		if (temp->right) temp->right->parent = node;
		temp->right = node;

		if (node->parent) {
			if (node->data < node->parent->data) {
				node->parent->left = temp;
			}
			else {
				node->parent->right = temp;
			}
		}
		else {
			root = temp;
		}
		RedBlackNode* temp2 = node->parent;
		node->parent = temp;
		temp->parent = temp2;
		node = temp;
	}
	void rotateLeft(RedBlackNode*& node) {
		RedBlackNode* temp = node->right;
		node->right = temp->left;
		if (temp->left) temp->left->parent = node;
		temp->left = node;
		if (node->parent) {
			if (node->data < node->parent->data) {
				node->parent->right = temp;
			}
			else {
				node->parent->left = temp;
			}
		}
		else {
			root = temp;
		}
		RedBlackNode* temp2 = node->parent;
		node->parent = temp;
		temp->parent = temp2;
		node = temp;
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
				}
			}
			else {
				int data = node->data;
				if (data < parent->data && parent->data < grand->data) { // LL
					grand->color = RED;
					parent->color = BLACK;
					rotateRight(grand);
				}
				else if (data > parent->data && parent->data > grand->data) { // RR
					grand->color = RED;
					parent->color = BLACK;
					rotateLeft(grand);
				}
				else if (data < parent->data && parent->data > grand->data) { // RL
					rotateRight(grand);
					grand->color = RED;
					parent->color = BLACK;
					rotateLeft(grand);
				}
				else if (data > parent->data && parent->data < grand->data) { // LR
					rotateLeft(grand);
					grand->color = RED;
					parent->color = BLACK;
					rotateRight(grand);
				}
			}
		}
	}
	void insertNode(RedBlackNode*& root, T data) {
		if (!root) {
			root = new RedBlackNode(data);
			fixOrientation_Insertion(root);
			return;
		}
		else {
			if (data == root->data) {
				// handling same case
				return;
			}
			else if (data < root->data) {
				if (!root->left) {
					root->left = new RedBlackNode(data);
					root->left->parent = root;
					fixOrientation_Insertion(root->left);
					return;
				}
				else {
					insertNode(root->left, data);
				}
			}
			else if (data > root->data) {
				if (!root->right) {
					root->right = new RedBlackNode(data);
					root->right->parent = root;
					fixOrientation_Insertion(root->right);
					return;
				}
				else {
					insertNode(root->right, data);
				}
			}
		}
	}
	void fixDebt(RedBlackNode*& node) {
		if (node->color == RED) {
			node->color = BLACK;
		}
		else if (node != root) {
			// handling debt cases
			RedBlackNode* parent = node->parent;
			RedBlackNode* sibling;
			if (parent->left == node) {
				sibling = parent->right;
			}
			else {
				sibling = parent->left;
			}
			// case 1
			if (sibling && sibling->color == RED) {
				// swap sibling and parent colors
				parent->color = RED;
				sibling->color = BLACK;
				// rotate on indebt childs side
				// sibling right so rotate left
				if (sibling->data > parent->data) {
					rotateLeft(parent);
				}
				else {
					rotateRight(parent);
				}
				// recursively check up the tree to ensure rules stay same
				fixDebt(node);
			}

			else if (sibling->color == BLACK) {
				if ((sibling->left && sibling->left->color == RED) ||
					(sibling->right && sibling->right->color == RED)) {

					if (sibling->data < parent->data && (sibling->left && sibling->left->color == RED)) { // LL
						sibling->left->color == BLACK;
						sibling->color = parent->color;
						parent->color = BLACK;
						rotateRight(parent);
					}
					else if (sibling->data > parent->data && (sibling->right && sibling->right->color == RED)) { // RR
						sibling->right->color == BLACK;
						sibling->color = parent->color;
						parent->color = BLACK;
						rotateLeft(parent);
					}
					else if (sibling->data < parent->data && (sibling->left && sibling->left->color == BLACK)) { // LR
						sibling->right->color == BLACK;
						sibling->color = parent->color;
						parent->color = BLACK;
						rotateLeft(sibling);
						rotateRight(parent);
					}
					else if (sibling->data > parent->data && (sibling->right && sibling->right->color == BLACK)) { // LR
						sibling->right->color == BLACK;
						sibling->color = parent->color;
						parent->color = BLACK;
						rotateRight(sibling);
						rotateLeft(parent);
					}
				}
				else {
					sibling->color = RED;
					if (parent->color == RED) parent->color = BLACK;
					else if (parent->color == BLACK && parent != root) fixDebt(parent);
				}
			}
		}
		if (node == this->root) {
			node->color = BLACK;
			return;
		}
		if (node && node->debt) {
			if (node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
			delete node;
			node = nullptr;
		}
	}
	void fixOrientation_Deletion(RedBlackNode*& node, bool debt) {
		if (node->color == RED) {
			node->color = BLACK;
			return;
		}
		else if(node != root && debt)
		{
			fixDebt(node);
		}
	}
	void removeNode(RedBlackNode*& root, T value) {
		if (!root) {
			cout << "Unable to find value..\n";
			return;
		}
		if (value < root->data) {
			removeNode(root->left, value);
		}
		else if (value > root->data) {
			removeNode(root->right, value);
		}
		else {
			// found Node
			// condition to see if node has debt
			if ((root->left && !root->right) || (root->right && !root->left) || (!root->left && !root->right)) {
				if (root->color == BLACK && ((!root->left && !root->right) ||
					(root->left && root->left->color == BLACK ||
						root->right && root->right->color == BLACK))) {
					root->debt = true;
				}
				// No children
				if (!root->left && !root->right) {
					if (root == this->root) {
						delete root;
						root = nullptr;
						return;
					}
					else if(root->color == RED)
					{
						if (root) {
							if (root->parent->right == root) {
								root->parent->right = nullptr;
							}
							else {
								root->parent->left = nullptr;
							}
						}
						delete root;
						root = nullptr;
						return;
					}
				}
				// 1 child
				else if (!root->left) { // right child
					RedBlackNode<T>* temp = root;
					root = root->right;
					root->parent = temp->parent;
					root->parent->right = root;
					delete temp;
				}
				else if (!root->right) { // left child
					RedBlackNode<T>* temp = root;
					root = root->left;
					root->parent = temp->parent;
					root->parent->left = root;
					delete temp;
				}
				fixOrientation_Deletion(root, root->debt);
			}
			// 2 Children
			else if (root->left && root->right) {
				RedBlackNode<T>*& successor = root->left;
				while (successor && successor->right) successor = successor->right;
				T temp = successor->data;
				successor->data = root->data;
				root->data = temp;
				removeNode(successor, successor->data);
			}
		}
	}

public:
	RedBlackTree() :root(nullptr) {}

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
	RedBlackNode* Root()const { return root; }
	void preOrder() {
		helper(root);
	}
};