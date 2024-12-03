#pragma once
#include<fstream>
#include<filesystem>
#include "Vector.h"
#include "ParentTree.h"
#include"AVL.h"
#include"RedBlackTree.h"
#include<memory>
using namespace std;

class GitLite
{
public:
	GitLite(): colNumber(-1), tree(nullptr)
	{}
	void initRepo()
	{
		//create repo folder
		cout << "Enter Repository name: ";
		cin >> repoPath;
		if (!exists(repoPath))
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
		int treeType;
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
			return ;
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
		while (colNumber < 0 || colNumber >=colNames.getCurr())
		{
			cout << "Invalid index, enter again: ";
			cin >> colNumber;
		}
		

		if (treeType == 1)//AVL
		{
			
		}
		else if (treeType == 2)//RedBlack
		{

		}
		else if (treeType == 3)//BTree
		{

		}


		
	}

private:
	filesystem::path repoPath;
	filesystem::path CSVPath;
	ParentTree* tree;
	int colNumber;
	filesystem::path currentBranch;
	Vector<filesystem::path> branches;

};
