#include "AVL.h"
#include "RedBlackTree.h"
#include "Btree.h"
#include <vector>
using namespace std;

int main()
{
	Btree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Btree",3);

	vector<int> keys = {50, 20, 70, 10, 30, 60, 90, 40, 80, 100, 25, 35, 75, 85, 95};
	for (int key : keys) {
		tree1.insert(key);
		// tree1.printTree(tree1.getRoot()); // Print after each insertion for debugging
	}

	// Test Deletion
	tree1.remove(25);
	tree1.remove(40);
	tree1.remove(35);
	tree1.remove(70);
	tree1.remove(80);
	tree1.printTree(tree1.getRoot());
	// vector<int> deleteKeys = {25, 40, 30, 70, 80};
	// for (int key : deleteKeys) {
	// 	cout<<"Deleting Key: "<<key<<endl;
	// 	tree1.remove(key);
	// 	tree1.printTree(tree1.getRoot()); // Print after each deletion for debugging
	// 	cout<<endl;
	// }



	return 0;
}