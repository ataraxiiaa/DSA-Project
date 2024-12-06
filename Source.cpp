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