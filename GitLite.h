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
	int treeType;//1=AVL, 2=RB, 3=BTree
	filesystem::path currentBranch;
	Vector<filesystem::path> branches;
	MerkleTree* currentMerkle;
	ParentTree<String>* currentTree;

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
		RowEntry newRow;
		for (int a = 0; a < colNames.getCurr(); a++)
		{
			currentColumn = "";
			cout << colNames[a] << ": ";
			getline(cin, currentColumn);
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
		Vector<long long> indexes=this->currentTree->search(input);
		if (indexes.getCurr() == 0)
			return;
		for (int a = 0; a < indexes.getCurr(); a++)
		{
			cout << "Entry " << a << ": " << this->currentMerkle->search(indexes[a])<<endl;
		}
	}
	void storeChange(const String& operation, RowEntry& op)
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
		file << operation << '\n';
		file << op.rowIndex << ',' << op << '\n';
	}
	
};
