#include "GitLite.h"
using namespace std;

int main()
{
	//Btree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\Btree", 3);


	//vector<int> keys = { 50, 20, 70, 10, 30, 60, 90, 40, 80, 100, 25, 35, 75, 85, 95 ,100,105,110,125,130,135,140,145,50};
	//for (int key : keys) {
	//	cout << key << endl;
	//	tree1.insert(key,0);
	//}
	//tree1.printTree(tree1.getRoot());
	//tree1.search(25);

	//// Test Deletion
	//tree1.remove(25);
	//tree1.remove(40);
	//tree1.remove(35);
	//tree1.remove(70);
	//tree1.remove(80);
	//tree1.printTree(tree1.getRoot());
	GitLite git;
	String input;
	while (true)
	{
		cout << "> ";
		input = "";
		cin >> input;

		if (input == "init")
		{
			git.initRepo();
		}
		else if (input == "print")
		{
			git.printCurrentTree();
		}
		else if (input == "current-branch")
		{
			git.printCurrentBranch();
		}
		else if (input == "branches")
		{
			git.printAllBranches();
		}
		else if (input == "create-branch")
		{
			git.createBranch();
		}
		else if (input == "checkout")
		{
			git.checkout();
		}
		else if (input == "delete-branch")
		{
			git.deleteBranch();
		}
		else if (input == "save")
		{
			git.saveRepoToFile();
			cout << "Repository data saved to file: "<< git.getRepoDataFile() << endl;
		}
		else if (input == "load")
		{
			filesystem::path temp;
			cout << "Enter REPO_DATA.txt file path: ";
			cin >> temp;
			if (filesystem::exists(temp))
			{
				git.loadRepoFromFile(temp);
				cout << "Repository loaded from: " << git.getRepoDataFile() << endl;
			}
			else
				cout << "Error: Invalid file path." << endl;
		}
		else if (input == "insert")
		{
			git.insert();
		}
		else if (input == "search")
		{
			git.search();
		}
		else if (input == "remove")
		{
			git.remove();
		}
		else if (input == "update")
		{
			git.update();
		}
		else if (input == "exit")
		{
			break;
		}
		else
		{
			cout << "Invalid command.\n";
		}
	}
	return 0;
}