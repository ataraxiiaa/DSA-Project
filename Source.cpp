///*
//	Fahad Bin Faisal, 23i-0614, Section G
//	Ali Abdullah, 23i-0842, Section G
//	Ahmar Ali, 23p-0686, Section G
//*/
#include "GitLite.h"
using namespace std;

int main()
{
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
		else if (input == "print-merc")
		{
			git.printMerc();
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
		else if (input == "commit")
		{
			git.commit();
		}
		else if (input == "log")
		{
			git.log();
		}
		else if (input == "merge")
		{
			git.merge();
		}
		else if (input == "exit")
		{
			break;
		}
		else if (input == "help")
		{
			cout << "Commands:\n";
			cout << "init - Initialize a new repository.\n";
			cout << "print - Print the current tree.\n";
			cout << "print-merc - Print the mercurial tree.\n";
			cout << "current-branch - Print the current branch name.\n";
			cout << "branches - Print all branches.\n";
			cout << "create-branch - Create a new branch.\n";
			cout << "checkout - Checkout to a branch.\n";
			cout << "delete-branch - Delete a branch.\n";
			cout << "save - Save the repository data to a file.\n";
			cout << "load - Load the repository data from a file.\n";
			cout << "insert - Insert a new key into the current tree.\n";
			cout << "search - Search for a key in the current tree.\n";
			cout << "remove - Remove a key from the current tree.\n";
			cout << "update - Update a key in the current tree.\n";
			cout << "commit - Commit changes to the current branch.\n";
			cout << "log - Show commit history of the current branch.\n";
			cout << "merge - Merge another branch into the current branch.\n";
			cout << "exit - Exit the program.\n";
			cout << "help - Show this help message.\n";
		}
		else if (input == "clear")
		{
			system("cls");
		}
		else
		{
			cout << "Invalid command.\n";
		}

	}
	return 0;
}