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

	void saveRepoToFile()
	{
		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
		ofstream file(repoFilePath);
		if (!file.is_open())
			throw runtime_error("Cannot open repo data file for writing.");

		file << repoPath<<'\n';
		file << CSVPath << '\n';
		file << colNumber << '\n';
		file << treeType << '\n';
		file << currentBranch << '\n';
		file << branches.getCurr() << '\n';
		for (int a = 0; a < branches.getCurr(); a++)
		{
			file << branches[a] << '\n';
		}
		if (currentMerkle)
		{
			file << 1 << '\n';
			file << currentMerkle->rootPath << '\n';
			file << currentMerkle->folderPath << '\n';
		}
		else
		{
			file << 0 << '\n';
		}
		if (currentTree)
		{
			file << 1 << '\n';
			file << currentTree->rootPath << '\n';
			file << currentTree->folderPath << '\n';
		}
		else
		{
			file << 0 << '\n';
		}
	}
	void loadRepoFromFile()
	{
		filesystem::path repoFilePath = repoPath / "REPO_DATA.txt";
		ifstream file(repoFilePath);
		if (!file.is_open()) {
			throw runtime_error("Cannot open repo data file for reading.");
		}

		String line;

		file>> repoPath;
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

		int hasMerkle;
		file >> hasMerkle;
		file.ignore(numeric_limits<streamsize>::max(), '\n'); 
		if (hasMerkle == 1)
		{
			filesystem::path merkleRoot;
			file >> merkleRoot;
			filesystem::path merkleFolder;
			file >> merkleFolder;
			currentMerkle = new MerkleTree(merkleFolder,merkleRoot);
		}
		else 
		{
			currentMerkle = nullptr;
		}


		int hasTree;
		file >> hasTree;
		file.ignore(numeric_limits<streamsize>::max(), '\n');

		if (hasTree == 1) 
		{
			filesystem::path treeRoot;
			file >> treeRoot;
			filesystem::path treeFolder;
			file >> treeFolder;

			if (treeType == 1)//AVl
			{
				currentTree = new AVL<String>(treeFolder, treeRoot);
			}
			else if (treeType == 2)//RB
			{

			}
			else if (treeType == 3)//B
			{

			}

		}
		else 
		{
			currentTree = nullptr;
		}

		file.close();
	}


public:
	GitLite(): colNumber(-1), currentMerkle(nullptr), currentTree(nullptr)
	{}
	~GitLite()
	{
		if (currentMerkle)
			delete currentMerkle;
	}
	void initRepo()
	{
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

			}
			else if (treeType == 3)//BTree
			{

			}
			String rowString;
			long long rowIndex = 0;
			while (true)
			{
				getline(CSV, rowString);
				if (rowString[0] == ',' || !rowString)
					break;
				cout << rowIndex << '\n';
				RowEntry rowData;
				rowData.readRow(rowIndex, rowString);
				currentMerkle->insert(rowIndex, rowData);					//insert with index in merkle
				currentTree->insert(rowData.cells[colNumber], rowIndex);	//insert data and index in tree
				rowIndex++;
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

};
