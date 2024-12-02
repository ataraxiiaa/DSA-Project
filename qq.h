#include <iostream>
using namespace std;

template<class T>
class qq {
	//===================================== Queue Node ==========================================
	struct Node {
		T data;
		Node* next;
		Node(T data=T()):data(data) {}
	};
	Node* frontPointer;
	Node* rearPointer;

public:
	//===================================== Queue functions ==========================================
	qq() {
		frontPointer = rearPointer = nullptr;
	}
	bool isEmpty() { return frontPointer == nullptr; }
	void enqueue(T data) {
		Node* newNode = new Node(data);
		if (isEmpty()) {
			frontPointer = rearPointer = newNode;
		}
		else {
			rear->next = newNode;
			rear = rear->next;
		}
	}
	T front() {
		return frontPointer->data;
	}
	T rear() {
		return rearPointer->data;
	}
	T dequeue() {
		if (isEmpty()) {
			throw runtime_error("Queue already empty");
		}
		else {
			T data = frontPointer->data;
			Node* temp = frontPointer;
			frontPointer = frontPointer->next;
			delete temp;
			return data;
		}
	}
	void clear() {
		while (!this->isEmpty()) {
			this->dequeue();
		}
	}
	~qq() {
		clear();
	}
};