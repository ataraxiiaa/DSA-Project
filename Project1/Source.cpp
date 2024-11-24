#include "RedBlackTree.h"
using namespace std;

int main() {
	
	RedBlackTree<int> rbt;
	rbt.insert(10);
	rbt.insert(20);
	rbt.insert(30);
	rbt.insert(15);

	rbt.preOrder();

	return 0;
}