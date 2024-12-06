#pragma once
#include<filesystem>
using namespace std;
using namespace filesystem;

template <class T>
class ParentTree
{
protected:
	//convert absolute paths to relative
	static filesystem::path makeRelative(const filesystem::path& fullPath)
	{
		filesystem::path result;
		bool treeFound = false;

		for (const auto& part : fullPath) {
			if (part == "TREE") {
				treeFound = true;
			}
			if (treeFound) {
				result /= part;
			}
		}
		return result;
	}

public:
	static void updateNewBranch(const path& targetFile, const path& oldBranch, const path& newBranch)
	{
		ifstream file(targetFile);
		if (!file.is_open())
			throw runtime_error("Cannot open file: \'TREE_DATA.txt\' for reading.");

		path tempRootPath;
		path tempFolderPath;
		long long tempStaticCounter;
		path tempBranchPath;

		file >> tempRootPath;
		file >> tempFolderPath;
		file >> tempBranchPath;

		file.close();

		ofstream rewritefile(targetFile);
		if (!rewritefile.is_open())
			throw runtime_error("Cannot open file: \'MERKLE_DATA.txt\' for writing.");

		path newPath;

		newPath.clear();
		for (const auto& part : tempRootPath) {
			if (part == oldBranch) {
				newPath /= newBranch;
			}
			else {
				newPath /= part;
			}
		}
		rewritefile << newPath << '\n';

		newPath.clear();
		for (const auto& part : tempFolderPath) {
			if (part == oldBranch) {
				newPath /= newBranch;
			}
			else {
				newPath /= part;
			}
		}
		rewritefile << newPath << '\n';

		newPath.clear();
		for (const auto& part : tempBranchPath) {
			if (part == oldBranch) {
				newPath /= newBranch;
			}
			else {
				newPath /= part;
			}
		}
		rewritefile << newPath << '\n';

		rewritefile.close();
	}

	std::filesystem::path rootPath;
	std::filesystem::path folderPath;
	std::filesystem::path branchPath;

	virtual void insert(const T& data, const long long& rowIndex) = 0;
	virtual void remove(const T& data, const long long& rowIndex) = 0;
	virtual void print() = 0;
	virtual void saveDataToFile() = 0;
};