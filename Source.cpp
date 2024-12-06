#include "AVL.h"
#include "RedBlackTree.h"
#include "Btree.h"
using namespace std;

int main()
{
	Btree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Btree",4);

	tree1.insert(1);
	tree1.insert(2);
	tree1.insert(3);
	tree1.insert(4);
	tree1.insert(5);
	tree1.insert(6);
	tree1.insert(7);
	tree1.insert(8);
	tree1.insert(9);
	tree1.insert(10);
	tree1.insert(11);
	tree1.insert(12);
	tree1.insert(13);
	tree1.remove(12);
	tree1.insert(15);

	// tree1.insert(10);
	// tree1.insert(20);
	// tree1.insert(30);
	// tree1.insert(40);
	// tree1.remove(10);
	// tree1.remove(40);
	// tree1.insert(40);
	// tree1.insert(50);
	// tree1.insert(35);
	// tree1.remove(50);
	// tree1.insert(50);
	// tree1.remove(20);
	// tree1.remove(30);


	return 0;
}