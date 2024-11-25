#pragma once

#include <string>
#include <iostream>
using namespace std;

enum NodeColor {
	RED,
	BLACK
};
template<class T> 
struct RedBlackNode {
	T data;
	RedBlackNode* left, * right, * parent;
	NodeColor color;
	RedBlackNode(T data, RedBlackNode* left = nullptr, RedBlackNode* right = nullptr, RedBlackNode* parent = nullptr) {
		this->left = left;
		this->right = right;
		this->parent = parent;
		this->data = data;
		color = RED;
	}
};

template<class T> 
class RedBlackTree {
	RedBlackNode<T>* root;
	
	void rotateRight(RedBlackNode<T>*& node) {
		RedBlackNode<T>* temp = node->left;
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
		RedBlackNode<T>* temp2 = node->parent;
		node->parent = temp;
		temp->parent = temp2;
		node = temp;
	}
	void rotateLeft(RedBlackNode<T>*& node) {
		RedBlackNode<T>* temp = node->right;
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
		RedBlackNode<T>* temp2 = node->parent;
		node->parent = temp;
		temp->parent = temp2;
		node = temp;
	}
	void fixOrientation(RedBlackNode<T>*& node) {
		if (!node) return;
		if (node == root) {
			node->color = BLACK;
			return;
		}
		node->color = RED;
		RedBlackNode<T>* parent = node->parent;
		if (parent->color == RED) {
			RedBlackNode<T>* grand = node->parent->parent;
			RedBlackNode<T>* uncle = nullptr;
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
					parent->color = BLACK;;
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
	void insertNode(RedBlackNode<T>*& root, T data) {
		if (!root) {
			root = new RedBlackNode<T>(data);
			fixOrientation(root);
			return;
		}
		else {
			if (data == root->data) {
				// handling same case
				return;
			}
			else if (data < root->data) {
				if (!root->left) {
					root->left = new RedBlackNode<T>(data);
					root->left->parent = root;
					fixOrientation(root->left);
					return;
				}
				else {
					insertNode(root->left, data);
				}
			}
			else if (data > root->data) {
				if (!root->right) {
					root->right = new RedBlackNode<T>(data);
					root->right->parent = root;
					fixOrientation(root->right);
					return;
				}
				else {
					insertNode(root->right, data);
				}
			}
		}
	}

public:
	RedBlackTree():root(nullptr) {}

	void insert(T value) {
		insertNode(root, value);
	}
	void helper(RedBlackNode<T>* root) {
		if (root) {
			cout << root->data << " " << "(";
			if (root->color) cout << "BLACK";
			else cout << "RED";
			cout<< ") ";
			helper(root->left);
			helper(root->right);
		}
	}
	void preOrder() {
		helper(root);
	}
};