#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
	RedBlackTree<int> rbt;
	rbt.insert(10);
	rbt.insert(5);
	rbt.insert(20);
	rbt.insert(17);
	rbt.preOrder();
	/*AVL<string> tree("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Project1\\AVLTree1_NODES");
	tree.insert("Fahad BIN FAISAL");
	tree.insert("Ali nigger");
	tree.insert("Ahmar");
	tree.insert("ALIBROTHER HEHE");
	tree.insert("goat");
	tree.insert("A VERY LONG MEESSAGE I CAN FINALLY READ SPACES HAHA");
	tree.saveRootToFile();
	tree.print();
	cout << endl<<endl;

	AVL<int> tree2("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Project1\\AVLTree2_NODES");
	tree2.insert(5);
	tree2.insert(7);
	tree2.insert(2);
	tree2.insert(4);
	tree2.insert(1);
	tree2.insert(9);
	tree2.insert(5);
	tree2.saveRootToFile();
	tree2.print();*/


	return 0;
}