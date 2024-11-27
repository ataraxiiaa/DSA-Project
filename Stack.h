#pragma once
template <class T>
class Stack
{
	class Node
	{
	public:
		T data;
		Node<T>* next;

		Node(T data = NULL )
		{
			this->data = data;
			next = nullptr;
		}
		Node()
		{
			next = nullptr;
		}
	};

	Node<T>* top;

public:

	Stack()
	{
		top = nullptr;
	}

	bool isEmpty()
	{
		return top == nullptr;
	}

	T& Top()
	{
		if (isEmpty())
		{
			std::cerr << "Error: Stack is empty" << endl;
			return T();
		}
		return this->top->data;
	}

	void push(T val)
	{
		Node<T>* temp = new Node<T>(val);
		temp->next = top;
		top = temp;
	}
	T pop()
	{
		if (isEmpty())
		{
			std::cerr << "Error: Stack is empty"<<endl;
			return T();
		}

		T temp = top->data;
		Node<T>* deletingNode = top;
		top = top->next;
		delete deletingNode;
		return temp;
	}

	~Stack()
	{
		while (!isEmpty())
		{
			pop();
		}
	}
};