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
		else
		{
			cout << "Invalid command.\n";
		}

	}
	return 0;
}