#include "GitLite.h"
using namespace std;

int main()
{
	GitLite git;
	String input;
	while (!(input == "exit"))
	{
		cout << '>';
		input = "";
		cin >> input;
		if (input == "init")
		{
			git.initRepo();
		}
		if (input == "print")
		{
			git.printCurrentTree();
		}

		else
		{
			cout << "Invalid command.\n";
		}

	}
	return 0;
}