#include "AVL.h"
#include "RedBlackTree.h"
#include "Btree.h"
using namespace std;

int main()
{
	Btree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Btree",4);
	tree1.insert(5);
	tree1.insert(7);
	tree1.insert(8);
	tree1.insert(9);
	tree1.insert(10);
	tree1.insert(11);
	tree1.insert(12);
	tree1.insert(4);
	tree1.insert(15);
	tree1.insert(3);
	tree1.insert(19);
	tree1.insert(22);
	tree1.insert(25);
	tree1.insert(6);
	tree1.insert(26);
	tree1.insert(29);
	return 0;
}