#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
	RedBlackTree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\RedBlackTree");
	tree1.insert(20);
	tree1.insert(10);
	tree1.insert(5);
	tree1.insert(24);

	tree1.remove(20);
	tree1.insert(22);
	tree1.insert(30);
	tree1.insert(29);

	tree1.print();

	return 0;
}