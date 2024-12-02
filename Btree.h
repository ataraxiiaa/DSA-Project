#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "qq.h"
#include "Vector.h"
using namespace std::filesystem;

template<class T> 
class Btree {
	//===================================== B-Tree Node ==========================================
	struct Node {
		Vector<T> keys;
		Vector<filesystem::path> children;
		bool isLeaf;
		filesystem::path parent;
		Node() {
			isLeaf = true;
			parent = "NULL";
		}
		

	};
	//===================================== File Functions ==========================================
	filesystem::path createPath(T value) {
		if (!filesystem::exists(folderPath)) {
			cout << "Created file directory successfully: " << folderPath << endl;
			filesystem::create_directories(folderPath);
		}
		filesystem::path newPath = folderPath;
		string fileName;
		if constexpr (is_same<T, string>::value) {
			fileName = value;
		}
		else {
			fileName = to_string(value);
		}
		fileName += ".txt";
		newPath /= fileName;
		return newPath;
	}
	bool removeFile(filesystem::path& path) {
		if (filesystem::exists(path)) {
			filesystem::remove(path);
			return true;
		}
		return false;

	}
	filesystem::path root;
	filesystem::path folderPath;
	int degree;
	//===================================== B-Tree Functions ==========================================

	
public:
	//===================================== B-Tree UI Functions ==========================================
	Btree(filesystem::path folderPath,int degree = 3) :degree(degree) {
		this->root = "NULL";
		this->folderPath = folderPath;
	}
	void insert(T data) {
		
	}

};