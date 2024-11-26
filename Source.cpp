#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
	RedBlackTree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\RedBlackTree");
	tree1.insert(20);
	tree1.insert(10);
	tree1.insert(5);
	tree1.insert(15);
	tree1.insert(3);
	tree1.insert(4);
	cout << tree1.Root();

	return 0;
}