#pragma once
#include<filesystem>
template <class T>
class ParentTree
{
public:
	std::filesystem::path rootPath;
	std::filesystem::path folderPath;

	virtual void insert(const T& data, const long long& rowIndex) = 0;
	virtual void remove(const T& data, const long long& rowIndex) = 0;
	virtual void print() = 0;
	virtual void saveDataToFile() = 0;
};