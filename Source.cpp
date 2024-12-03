#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
	RedBlackTree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\RedBlackTreetest");
	int values[] = { 20,15,25,10,5,30,35,40,50,45,60,55,65,70,
					1,8,3,6 };
		// 1, 8, 3, 6, 12, 18, 22, 28, 32, 38, 48, 52, 58, 62, 68 };

	// Insert values into the tree
	for (int val : values) {
		tree1.insert(val);
	}
	// Print tree structure
	cout << tree1.Root();
	tree1.print();

	int deleteValues[] = { 1,20, 10, 30, 65, 50, 55, 25 };
	for (int val : deleteValues) {
		cout << "\nDeleting " << val << "..." << std::endl;
		tree1.remove(val);
		tree1.print();
	}
	return 0;
}