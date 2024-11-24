#include <iostream>
#include "AVL.h"
using namespace std;

int main()
{
	AVL<int> tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(7);
	tree.insert(4);
	tree.saveRootToFile();


	ifstream root("AVL_Root.txt");
	if (root.is_open())
	{
		string rootPath;
		root >> rootPath;
		root.close();

		AVL<int> tree2(rootPath);
		tree2.print();
	}

	return 0;
}