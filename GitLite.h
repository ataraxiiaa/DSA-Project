#pragma once
#include<fstream>
#include<filesystem>
#include "Vector.h"
#include "ParentTree.h"
#include"AVL.h"
#include"RedBlackTree.h"
#include"MerkleTree.h"
#include "RowEntry.h"
using namespace std;

class GitLite
{
private:
	filesystem::path repoPath;
	filesystem::path CSVPath;
	int colNumber;
	int treeType;					//1=AVL, 2=RB, 3=BTree
	int hashType;					//1= instructor, 2=SHA
	filesystem::path currentBranch;
	Vector<filesystem::path> branches;
	MerkleTree* currentMerkle;
	ParentTree<String>* currentTree;

	//applies changes from changesFile to current trees
	void applyChanges(path changesFile)
	{
		ifstream ifile(changesFile);
		if (!ifile.is_open())
			throw runtime_error("Failed to open CHANGES.txt file.");

		String operation;
		String row;
		int fieldIndex;
		long long rowIndex;
		char delim;
		while (getline(ifile, operation))
		{
			if (operation == "INSERT")
			{
				//read row
				ifile >> rowIndex >> delim;
				getline(ifile, row);
				rowIndex = currentMerkle->getCounter();
				RowEntry rowData;
				rowData.readRow(rowIndex, row);

				currentMerkle->insert(rowData);								//insert with index in merkle
				currentTree->insert(rowData.cells[colNumber], rowIndex);	//insert data and index in tree
				currentMerkle->saveDataToFile();
				currentTree->saveDataToFile();
			}
			else if (operation == "REMOVE")
			{
				//read row
				ifile >> rowIndex >> delim;
				getline(ifile, row);
				RowEntry rowData;
				rowData.readRow(rowIndex, row);

				//remove from both trees
				currentMerkle->remove(rowIndex);
				currentTree->remove(rowData.cells[colNumber], rowIndex);
				currentMerkle->saveDataToFile();
				currentTree->saveDataToFile();
			}
			else if (operation == "UPDATE")
			{
				//read the updated field's index
				ifile >> fieldIndex;
				ifile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				//read row
				ifile >> rowIndex >> delim;
				getline(ifile, row);
				RowEntry rowData;
				rowData.readRow(rowIndex, row);

				//update AVL/RB/Btree if updated field is chosen column number
				if (fieldIndex == this->colNumber)
				{
					this->currentTree->remove(this->currentMerkle->searchRowEntry(rowIndex).cells[fieldIndex], rowIndex);
					this->currentTree->insert(rowData.cells[fieldIndex], rowIndex);
				}
				//update merkle
				this->currentMerkle->update(rowIndex, fieldIndex, rowData.cells[fieldIndex]);
				currentTree->saveDataToFile();
			}
			else if (operation == "")
				break;

		}
	}
public:
	GitLite(): colNumber(-1), currentMerkle(nullptr), currentTree(nullptr), treeType(-1)
	{}
	~GitLite()
	{
		if (currentMerkle)
			delete currentMerkle;
		if (currentTree)
			delete currentTree;
	}
	void initRepo()
	{
		currentMerkle = nullptr;
		currentTree = nullptr;
		colNumber = -1;
		treeType = -1;
		branches.clear();
		currentBranch = "";

		//create repo folder
		cout << "Enter Repository name: ";
		cin >> repoPath;

		//create new repo if doesn't exist
		if (!exists(repoPath))
		{
			create_directory(repoPath);
			//store CSV path
			cout << "Enter CSV file path: ";
			cin >> CSVPath;
			while (!exists(CSVPath))
			{
				cout << "Invalid CSV path. Enter again: ";
				cin >> CSVPath;
			}

			//create master branch
			currentBranch = repoPath;
			currentBranch /= "master";
			branches.push_back(currentBranch);

			//choose tree
			cout << "1. AVL\n";
			cout << "2. Red Black tree\n";
			cout << "3. BTree\n";
			cout << "Choose tree type: ";
			cin >> treeType;
			while (treeType < 1 || treeType>3)
			{
				cout << "Invalid option. Choose again: ";
				cin >> treeType;
			}

			cout << "1: Instructor hash\n";
			cout << "2: SHA-256\n";
			cout << "Enter hash choice: ";
			cin >> hashType;
			while (hashType != 1 && hashType != 2)
			{
				cout << "Choose within range: ";
				cin >> hashType;
			}
			::hashTypeGlobal = hashType;


			//read file
			fstream CSV(CSVPath);
			if (!CSV.is_open()) {
				std::cerr << "Error: Could not open file." << std::endl;
				return;
			}

			//read header of CSV
			String header;
			getline(CSV, header);
			Vector<String> colNames;
			String currentColumn;
			for (int a = 0; a < header.getSize(); a++)
			{
				if (header[a] != ',')
				{
					currentColumn += header[a];
				}
				else
				{
					colNames.push_back(currentColumn);
					currentColumn = "";
				}
			}
			if(!(currentColumn==""))
				colNames.push_back(currentColumn);

			//display and select column;
			cout << "==== columns ====\n";
			for (int a = 0; a < colNames.getCurr(); a++)
			{
				cout << a << ": " << colNames[a] << endl;
			}
			cout << "Choose column to build tree on: ";
			cin >> colNumber;
			while (colNumber < 0 || colNumber >= colNames.getCurr())
			{
				cout << "Invalid index, enter again: ";
				cin >> colNumber;
			}


			//create MerkleTree and AVL/RB/BTree
			currentMerkle = new MerkleTree(currentBranch);
			if (treeType == 1)//AVL
			{
				currentTree = new AVL<String>(currentBranch);
			}
			else if (treeType == 2)//RedBlack
			{
				currentTree = new RedBlackTree<String>(currentBranch);
			}
			else if (treeType == 3)//BTree
			{

			}
			String rowString;
			long long rowIndex;
			while (true)
			{
				getline(CSV, rowString);
				if (rowString[0] == ',' || !rowString)
					break;

				rowIndex = currentMerkle->getCounter();
				cout << rowIndex << '\n';
				RowEntry rowData;
				rowData.readRow(rowIndex, rowString);
				currentMerkle->insert(rowData);					//insert with index in merkle
				currentTree->insert(rowData.cells[colNumber], rowIndex);	//insert data and index in tree
			}
			CSV.close();
			currentMerkle->saveDataToFile();
			currentTree->saveDataToFile();
			saveRepoToFile();
			cout << "Created new repository: " <<repoPath<< endl;
		}
		//if repo does exist, load the repo from the repo_data.txt
		else
		{
			loadRepoFromFile();
			cout << "Loaded existing repository: " << repoPath << endl;
		}
	}
	void printCurrentTree()
	{
		if (currentTree)
			this->currentTree->print();
		else
			cout << "Error: No tree loaded." << endl;
	}
	void printCurrentBranch()
	{
		if (currentBranch == "")
			cout << "Error: No branch loaded." << endl;
		else
			cout << "Current branch: " << currentBranch << endl;
	}
	void printAllBranches()
	{
		if (branches.getCurr() == 0)
		{
			cout << "Error: No branch exists." << endl;
			return;
		}
		for (int a = 0; a < branches.getCurr(); a++)
		{
			cout << "- " << branches[a] << endl;
		}
	}
	void createBranch()
	{
		path branchName;
		cout << "Enter branch name: ";
		cin >> branchName;
		path branchPath = repoPath / branchName;
		for (int a = 0; a < branches.getCurr(); a++)
		{
			if (branches[a] == branchPath)
			{
				cout << "Error: Branch " << branchName << " already exists." << endl;
				return;
			}
		}
		branches.push_back(branchPath);
		filesystem::copy(currentBranch, branchPath, filesystem::copy_options::recursive);

		//update branch names in new trees' data files
		path newMerkleFilePath = branchPath / "MERKLETREE" / "MERKLE_DATA.txt";
		MerkleTree::updateNewBranch(newMerkleFilePath, currentBranch.filename(), branchPath.filename());

		path newTreePath = branchPath / "TREE" / "TREE_DATA.txt";
		ParentTree<String>::updateNewBranch(newTreePath, currentBranch.filename(), branchPath.filename());

		saveRepoToFile();
		cout << "Branch: " << branchName << " created."<<endl;
	}

	void checkout()
	{
		path branchName;
		cout << "Enter branch name: ";
		cin >> branchName;
		path branchPath = repoPath / branchName;
		for (int a = 0; a < branches.getCurr(); a++)
		{
			if (branches[a] == branchPath)
			{
				currentBranch = branches[a];
				cout << "Switched to branch: " << branchName  << endl;

				//switch to target branch's trees
				if (currentMerkle)
					delete currentMerkle;
				if (currentTree)
					delete currentTree;

				currentMerkle = new MerkleTree(true, currentBranch);
				if (treeType == 1)//AVL
				{
					currentTree = new AVL<String>(true, currentBranch);
				}
				else if (treeType == 2)//RB
				{
					currentTree = new RedBlackTree<String>(true, currentBranch);
				}
				else if (treeType == 3)//BTree
				{

				}
				saveRepoToFile();
				return;
			}
		}
		cout << "Error: branch does not exist." << endl;
	}

	void deleteBranch()
	{
		path branchName;
		cout << "Enter branch name: ";
		cin >> branchName;
		path branchPath = repoPath / branchName;
		if (currentBranch == branchPath)
		{
			cout << "Error: Attempting to delete current branch. Checkout to another branch first." << endl;
			return;
		}
		else
		{
			for (int a = 0; a < branches.getCurr(); a++)
			{
				if (branches[a] == branchPath)
				{
					branches.Destroy(a);
					filesystem::remove_all(branchPath);
					cout << "Branch: " << branchPath << " removed." << endl;
					saveRepoToFile();
					return;
				}
			}
			cout << "Error: branch not found." << endl;
		}
	}
	void merge()
	{
		//input the other branch
		cout << "Enter name of branch to merge into current branch: ";
		path otherBranch;
		cin >> otherBranch;
		otherBranch = repoPath / otherBranch;
		if (!exists(otherBranch))
		{
			cout << "Branch does not exist." << endl;
			return;
		}
		if (otherBranch == currentBranch)
		{
			cout << "Cannot merge a branch into itself." << endl;
			return;
		}

		//store current branch commits in vector
		path currentBranchCommitFile=currentBranch/"COMMITS"/"COMMIT_DATA.txt";
		Vector<path> currentBranchCommits;
		if (exists(currentBranchCommitFile))
		{
			ifstream file(currentBranchCommitFile);
			if (!file.is_open())
				throw runtime_error("Cannot open current branch commit file.");
			path temp;
			while (true)
			{
				file >> temp;
				if (file.eof() || temp.empty())
					break;
				currentBranchCommits.push_back(temp);
			}
		}

		//store other branch's commits in vector
		path otherBranchCommitFile = otherBranch / "COMMITS" / "COMMIT_DATA.txt";
		Vector<path> otherBranchCommits;
		if (exists(otherBranchCommitFile))
		{
			ifstream file(otherBranchCommitFile);
			if (!file.is_open())
				throw runtime_error("Cannot open other branch commit file.");
			path temp;
			while (true)
			{
				file >> temp;
				if (file.eof() || temp.empty())
					break;
				otherBranchCommits.push_back(temp);
			}
		}

		//simply delete other branch if there are no commits in it
		if (otherBranchCommits.getCurr() == 0)
		{
			for (int a = 0; a < branches.getCurr(); a++)
			{
				if (branches[a] == otherBranch)
				{
					branches.Destroy(a);
					filesystem::remove_all(otherBranch);
					saveRepoToFile();
					cout << "Branches merged." << endl;
					return;
				}
			}
		}

		//if current commits are 0, apply all commits in other branch to current branch
		if (currentBranchCommits.getCurr() == 0) 
		{
			//apply changes
			for (int a = 0; a < otherBranchCommits.getCurr(); a++)
			{
				path changesFile = otherBranchCommits[a] / "CHANGES.txt";
				applyChanges(changesFile);
			}

			//delete other branch
			for (int a = 0; a < branches.getCurr(); a++)
			{
				if (branches[a] == otherBranch)
				{
					branches.Destroy(a);
					filesystem::remove_all(otherBranch);
					saveRepoToFile();
					cout << "Branches merged." << endl;
					return;
				}
			}
		}

		//find the commit where both branches diverge, then apply other branch's commits from there on
		int firstUncommonCommitIndex = -1;
		for (int a = 0; a < otherBranchCommits.getCurr() && a < currentBranchCommits.getCurr(); a++)
		{
			if (otherBranchCommits[a] != currentBranchCommits[a])
			{
				firstUncommonCommitIndex = a;
				break;
			}
		}

		//if no uncommon commit found till min(currBranchCommits, otherBranchCommits)
		if (firstUncommonCommitIndex == -1)
		{
			//if current branch is ahead of /equal to other branch
			if (currentBranchCommits.getCurr() >= otherBranchCommits.getCurr())
			{
				//delete other branch
				for (int a = 0; a < branches.getCurr(); a++)
				{
					if (branches[a] == otherBranch)
					{
						branches.Destroy(a);
						filesystem::remove_all(otherBranch);
						saveRepoToFile();
						cout << "Branches merged." << endl;
						return;
					}
				}
			}
			//if current branch is behind other branch
			else
			{
				//apply other branch changes from new commits onwards
				for (int a = currentBranchCommits.getCurr(); a < otherBranchCommits.getCurr(); a++)
				{
					path changesFile = otherBranchCommits[a] / "CHANGES.txt";
					applyChanges(changesFile);
				}
				//delete other branch
				for (int a = 0; a < branches.getCurr(); a++)
				{
					if (branches[a] == otherBranch)
					{
						branches.Destroy(a);
						filesystem::remove_all(otherBranch);
						saveRepoToFile();
						cout << "Branches merged." << endl;
						return;
					}
				}
			}
		}
		//found uncommon commit
		else
		{
			//apply changes from uncommon commit onwards
			for (int a = firstUncommonCommitIndex; a < otherBranchCommits.getCurr(); a++)
			{
				path changesFile = otherBranchCommits[a] / "CHANGES.txt";
				applyChanges(changesFile);
			}
			//delete other branch
			for (int a = 0; a < branches.getCurr(); a++)
			{
				if (branches[a] == otherBranch)
				{
					branches.Destroy(a);
					filesystem::remove_all(otherBranch);
					saveRepoToFile();
					cout << "Branches merged." << endl;
					return;
				}
			}
		}

		
	}

	void saveRepoToFile()
	{
		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
		ofstream file(repoFilePath);
		if (!file.is_open())
			throw runtime_error("Cannot open repo data file for writing.");

		file << repoPath << '\n';
		file << CSVPath << '\n';
		file << colNumber << '\n';
		file << treeType << '\n';
		file << hashType << '\n';
		file << currentBranch << '\n';
		file << branches.getCurr() << '\n';
		for (int a = 0; a < branches.getCurr(); a++)
		{
			file << branches[a] << '\n';
		}
	}
	void loadRepoFromFile(path filePath="NULL")
	{
		filesystem::path repoFilePath;
		if (filePath == "NULL")
		{
			repoFilePath = repoPath / "REPO_DATA.txt";
		}
		else
		{
			repoFilePath = filePath;
		}
		ifstream file(repoFilePath);
		if (!file.is_open()) {
			throw runtime_error("Cannot open repo data file for reading.");
		}

		String line;

		file >> repoPath;
		file >> CSVPath;

		file >> colNumber;
		file.ignore(numeric_limits<streamsize>::max(), '\n');
		file >> treeType;
		file.ignore(numeric_limits<streamsize>::max(), '\n');
		file >> hashType;
		::hashTypeGlobal = hashType;
		file.ignore(numeric_limits<streamsize>::max(), '\n');
		file >> currentBranch;
		int branchCount;
		file >> branchCount;
		file.ignore(numeric_limits<streamsize>::max(), '\n');

		branches.clear();
		for (int i = 0; i < branchCount; i++)
		{
			filesystem::path currBranch;
			file >> currBranch;
			branches.push_back(currBranch);
		}

		//load trees from branch
		if (currentMerkle)
			delete currentMerkle;
		currentMerkle = new MerkleTree(true, currentBranch);

		if (currentTree)
			delete currentTree;
		if (treeType == 1)//AVL
		{
			currentTree = new AVL<String>(true, currentBranch);
		}
		else if (treeType == 2)//RB
		{
			currentTree = new RedBlackTree<String>(true, currentBranch);
		}
		else if (treeType == 3)//BTree
		{

		}


		file.close();
	}
	path getRepoDataFile()
	{
		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
		return repoFilePath;
	}
	void insert()
	{
		fstream CSV(CSVPath);
		if (!CSV.is_open()) {
			std::cerr << "Error: Could not open file." << std::endl;
			return;
		}
		//read header of CSV
		String header;
		getline(CSV, header);
		Vector<String> colNames;
		String currentColumn;
		for (int a = 0; a < header.getSize(); a++)
		{
			if (header[a] != ',')
			{
				currentColumn += header[a];
			}
			else
			{
				colNames.push_back(currentColumn);
				currentColumn = "";
			}
		}
		if (!(currentColumn == ""))
			colNames.push_back(currentColumn);
		RowEntry newRow;
		for (int a = 0; a < colNames.getCurr(); a++)
		{
			currentColumn = "";
			cout << colNames[a] << ": ";
			getline(cin, currentColumn);
			for (int a = 0; a < currentColumn.getSize(); a++)
			{
				if (isAlphabet(currentColumn[a]))
					currentColumn.getData()[a] = convertToUppercase(currentColumn[a]);
			}
			newRow.cells.push_back(currentColumn);
		}
		newRow.rowIndex = -1;
		storeChange("INSERT", newRow);

		cout << "Entry inserted." << endl;
	}
	void search()
	{
		cout << "Enter key to search: ";
		String input;
		getline(cin, input);
		for (int a = 0; a < input.getSize(); a++)
		{
			if (isAlphabet(input[a]))
				input.getData()[a] = convertToUppercase(input[a]);
		}
		Vector<long long> indexes=this->currentTree->search(input);
		if (indexes.getCurr() == 0)
			return;
		for (int a = 0; a < indexes.getCurr(); a++)
		{
			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a])<<endl;
		}
	}
	void remove()
	{
		cout << "Enter key to remove: ";
		String input;
		getline(cin, input);
		for (int a = 0; a < input.getSize(); a++)
		{
			if (isAlphabet(input[a]))
				input.getData()[a] = convertToUppercase(input[a]);
		}
		Vector<long long> indexes = this->currentTree->search(input);
		if (indexes.getCurr() == 0)
			return;
		for (int a = 0; a < indexes.getCurr(); a++)
		{
			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a]) << endl;
		}

		cout << "\n1: remove all instances" << endl;
		cout << "2: remove a specific instance" << endl;
		cout << "Enter choice: ";
		int choice=0;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "Invalid choice. Enter again: ";
			cin >> choice;
		}
		if (choice == 1)
		{
			for (int a = 0; a < indexes.getCurr(); a++)
			{
				RowEntry deletedRow = this->currentMerkle->searchRowEntry(indexes[a]);
				storeChange("REMOVE", deletedRow);
				cout << "Entry: " << a << " removed" << endl;
			}
		}
		else if (choice == 2)
		{
			cout << "Enter index of entry to remove: ";
			cin >> choice;
			while (choice < 0 || choice >= indexes.getCurr())
			{
				cout << "Invalid index. Choose within range: ";
				cin >> choice;
			}
			RowEntry deletedRow = this->currentMerkle->searchRowEntry(indexes[choice]);
			storeChange("REMOVE", deletedRow);
			cout << "Entry: " << choice << " removed" << endl;
		}
	}
	void update()
	{
		//read key and display all instances of that key
		cout << "Enter key to update: ";
		String input;
		getline(cin, input);
		for (int a = 0; a < input.getSize(); a++)
		{
			if (isAlphabet(input[a]))
				input.getData()[a] = convertToUppercase(input[a]);
		}
		Vector<long long> indexes = this->currentTree->search(input);
		if (indexes.getCurr() == 0)
			return;
		for (int a = 0; a < indexes.getCurr(); a++)
		{
			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a]) << endl;
		}

		//ask if update all instances or only 1
		cout << "\n1: update all instances" << endl;
		cout << "2: update a specific instance" << endl;
		cout << "Enter choice: ";
		int choice = 0;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "Invalid choice. Enter again: ";
			cin >> choice;
		}


		//read header of CSV
		fstream CSV(CSVPath);
		if (!CSV.is_open()) {
			std::cerr << "Error: Could not open file." << std::endl;
			return;
		}
		String header;
		getline(CSV, header);
		Vector<String> colNames;
		String currentColumn;
		for (int a = 0; a < header.getSize(); a++)
		{
			if (header[a] != ',')
			{
				currentColumn += header[a];
			}
			else
			{
				colNames.push_back(currentColumn);
				currentColumn = "";
			}
		}
		if (!(currentColumn == ""))
			colNames.push_back(currentColumn);


		//ask for field that has to be updated
		cout << endl;
		for (int a = 0; a < colNames.getCurr(); a++)
		{
			cout << a << ": " << colNames[a] << endl;
		}
		int field = -1;
		cout << "Enter field to update: ";
		cin >> field;
		while (field < 0 || field >= colNames.getCurr())
		{
			cout << "Invalid index. Enter within range: ";
			cin >> field;
		}

		//enter the new value of the replacement
		String newField;
		cout << "Enter new value of field: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, newField);
		for (int a = 0; a < newField.getSize(); a++)
		{
			if (isAlphabet(newField[a]))
				newField.getData()[a] = convertToUppercase(newField[a]);
		}

		if (choice == 1)
		{
			for (int a = 0; a < indexes.getCurr(); a++)
			{
				RowEntry updatedRow = this->currentMerkle->searchRowEntry(indexes[a]);
				updatedRow.cells[field] = newField;
				storeChange("UPDATE", updatedRow, field);
				cout << "Entry: " << a << " updated" << endl;
			}
		}
		else if (choice == 2)
		{
			cout << "Enter index of entry to update: ";
			cin >> choice;
			while (choice < 0 || choice >= indexes.getCurr())
			{
				cout << "Invalid index. Choose within range: ";
				cin >> choice;
			}
			RowEntry updatedRow = this->currentMerkle->searchRowEntry(indexes[choice]);
			updatedRow.cells[field] = newField;
			storeChange("UPDATE", updatedRow, field);
			cout << "Entry: " << choice << " updated" << endl;
		}
	}
	void storeChange(const String& operation, RowEntry& op, int fieldIndex=-1)
	{
		path tempFolder = this->currentBranch / "temp";
		if (!exists(tempFolder))
		{
			filesystem::create_directories(tempFolder);
		}
		path changesFile = tempFolder / "CHANGES.txt";
		ofstream file(changesFile, ios::app);
		if (!file.is_open())
			throw runtime_error("Failed to open CHANGES.txt file.");


		if (operation == "UPDATE")
		{
			file << operation << '\n';
			file << fieldIndex << '\n';
			file << op.rowIndex << ',' << op << '\n';
		}
		else
		{
			file << operation << '\n';
			file << op.rowIndex << ',' << op << '\n';
		}
	}
	void commit()
	{
		if (!exists(currentBranch / "temp"))
		{
			cout << "No changes to commit." << endl;
			return;
		}
		cout << "Enter message: ";
		path message;
		String messagestr;
		getline(cin, messagestr);
		message = messagestr.getData();

		while (exists(currentBranch / message))
		{
			cout << "This commit exists, enter new message: ";
			message.clear();
			cin >> message;
		}

		//create commits folder
		if (!exists(currentBranch / "COMMITS"))
		{
			create_directories(currentBranch / "COMMITS");
		}
		//create the current commit message folder
		create_directories(currentBranch / "COMMITS"/ message);

		//store commit history in file
		ofstream file(currentBranch / "COMMITS" / "COMMIT_DATA.txt", ios::app);
		if (!file.is_open())
			throw runtime_error("Failed to open COMMIT_DATA.txt file.");
		file << (currentBranch / "COMMITS" / message) << '\n';
		file.close();

		//paste temp folder's changes file to current commit folder
		path changesFile = currentBranch / "temp" / "CHANGES.txt";
		filesystem::copy(changesFile, currentBranch / "COMMITS" / message / changesFile.filename(), filesystem::copy_options::overwrite_existing);
		filesystem::remove_all(currentBranch/"temp");


		//apply changes
		changesFile = currentBranch / "COMMITS" / message / "CHANGES.txt";
		applyChanges(changesFile);
		cout << "Changes commited." << endl;
	}

	void log()
	{
		if (!exists(currentBranch / "COMMITS" / "COMMIT_DATA.txt"))
		{
			cout << "No commits saved." << endl;
			return;
		}
		ifstream file(currentBranch / "COMMITS" / "COMMIT_DATA.txt");
		if (!file.is_open())
			throw runtime_error("Failed to open COMMIT_DATA.txt file.");
		path currCommit;
		int counter = 1;
		while (true)
		{
			file >> currCommit;
			if (file.eof() || currCommit.empty())
				break;
			cout << "Commit # " << counter++ << ": " << currCommit.filename() << endl;
		}
	}
	void printMerc()
	{
		this->currentMerkle->print();
	}
};

