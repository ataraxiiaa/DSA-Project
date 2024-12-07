// Necassary header files required for the code
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <filesystem>
#include "ParentTree.h"
#include "Vector.h" 

using namespace std;
using namespace std::filesystem; 
namespace fs = std::filesystem; // namespace for filesystem

/*
		B-Tree Class that inherits from the ParentTree class
        The class holds search insertion and deletion in B-Tree
        It composes of struct Key and struct Node that contain all the necassary parts and functions
*/

// pair struct allowing for 3 values
template <class T, class U, class V>
struct Pair {
    T first;
    U second;
    V third;
    Pair(T first = T(), U second = U(), V third = V()) : first(first), second(second), third(third) {}
};

template <class T>
class Btree : public ParentTree<T>
{
    //===================================== Key ==========================================

    struct Key {
        T key;
        Vector<long long> indexes;
		// to compare keys
        bool operator >(const Key& other) {
            if (this->key > other.key)
                return true;
            return false;
        }
        bool operator<(const Key& other) {
            if (this->key < other.key)
                return true;
            return false;
        }
    };

    //===================================== B-Tree Node ==========================================

    struct Node {
        // parent path
        filesystem::path parent;
		Vector<path> keyPaths; // paths to the keys
		Vector<Key> keys; // keys in the node
        Vector<path> childrenPaths;
		bool isLeaf; // is the node a leaf node

		Node(bool isLeaf = true) : isLeaf(isLeaf), parent("NULL") {} // constructor
		// function to save the node to a file
        void saveToFile(const path& path) {
			// if the path is empty or NULL throw an exception
            if (path.empty() || path == "NULL") {
                throw runtime_error("File path not valid");
            }
            ofstream file(path);
            if (!file.is_open()) {
                // unable to open file
                cout << path << endl;
                throw runtime_error("Unable to open file for saving node.");
            }
            // save key count
            file << keys.getCurr() << '\n';
            // save keys
            for (int i = 0; i < keys.getCurr(); ++i) {
                file << keys[i].key << '\n';
                file << keys[i].indexes.getCurr() << '\n';
                for (int j = 0; j < keys[i].indexes.getCurr(); ++j) {
                    file << keys[i].indexes[j];
                    if (j < keys[i].indexes.getCurr() - 1) {
                        file << ',';
                    }
                }
				if (keys[i].indexes.getCurr() > 0)
					file << '\n';
            }

            // save parent
			// MakeRelative function allows the code to be independent of the file path
            file << (this->parent == "NULL" ? "NULL" : makeRelative(this->parent)) << '\n';

            // save children count and paths
            file << childrenPaths.getCurr() << '\n';
            for (int i = 0; i < childrenPaths.getCurr(); ++i) {
                file << makeRelative(childrenPaths[i]) << '\n';
            }
            file.close();
        }
		// function to load the node from a file
        static Node LoadFromFile(const path& nodePath,const Btree& merc) {
            if (!exists(nodePath)) {
                cout << nodePath << endl;
                throw runtime_error("Node file does not exist.");
            }
            ifstream file(nodePath);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for writing.");
            }
            Node loadedNode;
            int keyCount;
            file >> keyCount;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < keyCount; ++i) {
                Key key;
                file >> key.key; // key

                int numIndexes;
                file >> numIndexes;
                file.ignore(numeric_limits<streamsize>::max(), '\n');

                for (int j = 0; j < numIndexes; ++j) {
                    int index;
                    file >> index;
                    if (file.peek() == ',') {
                        file.ignore(); // ignore comma
                    }
                    key.indexes.push_back(index);
                }
                file.ignore(numeric_limits<streamsize>::max(), '\n');
                loadedNode.keys.push_back(key);
            }
            filesystem::path temp;
            file >> temp;
			if (temp != "NULL") {
                // this allows our relative branching to work properly
                loadedNode.parent = merc.branchPath;
                loadedNode.parent /= temp;
			}
			else {
				loadedNode.parent = "NULL";
			}

            int numChildren;
            file >> numChildren;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < numChildren; ++i) {
                file >> temp;
                filesystem::path childPath = merc.branchPath;
				childPath /= temp;
                loadedNode.childrenPaths.push_back(childPath);
            }

            loadedNode.isLeaf = (numChildren == 0);

            file.close();
            return loadedNode;

        }
    };

    //===================================== B-Tree Functions ==========================================

    // function to search for a key in the tree
    Pair<filesystem::path, int, int> searchNode(const T& value) {
        if (rootPath == "NULL") {
            return Pair<filesystem::path, int, int>();
        }

        filesystem::path currPath = rootPath;
        int currIndex = 0;
        int currKeyIndex = -1;
        Node currNode = Node::LoadFromFile(currPath,*this);

        while (!currNode.isLeaf) {
            currIndex = currNode.keys.getCurr();

            for (int a = 0; a < currNode.keys.getCurr(); a++) {
                if (value == currNode.keys[a].key) {
                    currIndex = a;
					currKeyIndex = a;
					break;
                }
                if (value < currNode.keys[a].key) {
                    currIndex = a;
                    currKeyIndex = a;
                    break;
                }
            }
            currPath = currNode.childrenPaths[currIndex];
            currNode = Node::LoadFromFile(currPath,*this);
        }

        for (int a = 0; a < currNode.keys.getCurr(); a++) {
            if (value == currNode.keys[a].key) {
                currKeyIndex = a;
                break;
            }
        }
        return Pair<filesystem::path, int, int>(currPath, currIndex, currKeyIndex);
    }
	// split nodes when the node is full
    void splitNodes(Node& node, filesystem::path& currPath) {

        int mid = node.keys.getCurr() / 2;
        Key shiftedKey = node.keys[mid];
        Node leftNode, rightNode;
		// paths for the new nodes
        filesystem::path leftNodePath = folderPath /"NODES"/ ("DISK_" + to_string(nodeCount) + ".txt");
        nodeCount++;
        filesystem::path rightNodePath = folderPath /"NODES"/ ("DISK_" + to_string(nodeCount) + ".txt");
        nodeCount++;
        // seperating keys
        for (int i = 0; i < mid; ++i) {
            leftNode.keys.push_back(node.keys[i]);
        }

        for (int i = mid + 1; i < node.keys.getCurr(); ++i) {
            rightNode.keys.push_back(node.keys[i]);
        }

        node.keys.clear();
        // if node is not leaf seperate the children too
        if (!node.isLeaf) {
            // for left child
            for (int i = 0; i <= mid; ++i) {
                path oldChildPath = node.childrenPaths[i];
                Node leftChild = Node::LoadFromFile(oldChildPath,*this);
                leftChild.parent = leftNodePath;
                leftChild.saveToFile(oldChildPath);
                leftNode.childrenPaths.push_back(node.childrenPaths[i]);
            }
			// for right child
            for (int i = mid + 1; i < node.childrenPaths.getCurr(); ++i) {
                path oldChildPath = node.childrenPaths[i];
                Node rightChild = Node::LoadFromFile(oldChildPath,*this);
                rightChild.parent = rightNodePath;
                rightChild.saveToFile(oldChildPath);
                rightNode.childrenPaths.push_back(node.childrenPaths[i]);
            }

            node.childrenPaths.clear();
        }
		// if the node is root
        if (currPath == rootPath || (!node.isLeaf && node.parent == "NULL")) {
			// create a new root
            Node newRoot;
            newRoot.isLeaf = false;
            filesystem::path newRootPath = folderPath /"NODES"/ "ROOT.txt";

            // update children
            if (exists(newRootPath)) {
                filesystem::remove(newRootPath);
            }
			// save the left and right nodes
            leftNode.parent = currPath;
            leftNode.saveToFile(leftNodePath);

            rightNode.parent = currPath;
            rightNode.saveToFile(rightNodePath);

			// saving the key
            newRoot.keys.push_back(shiftedKey);

            // saving children
            newRoot.childrenPaths.push_back(leftNodePath);
            newRoot.childrenPaths.push_back(rightNodePath);
            // save the new root
            newRoot.saveToFile(newRootPath);

            // update the root path
            rootPath = newRootPath;
        }
		// if the node is not root
        else {
			// update the parent node
            Node parentNode = Node::LoadFromFile(node.parent,*this);
            filesystem::path parentPath = node.parent;

			// takes the inserted key to the parent
            parentNode.keys.insertSorted(shiftedKey);

            int index = 0;
            for (int i = 0; i < parentNode.childrenPaths.getCurr(); ++i) {
                if (parentNode.childrenPaths[i] == currPath) {
                    index = i;
                    break;
                }
            }
			// update the children
            parentNode.childrenPaths[index] = leftNodePath;
			parentNode.childrenPaths.inserAt(rightNodePath, index + 1); // updates children paths

			// save the nodes
            leftNode.parent = node.parent;
            leftNode.saveToFile(leftNodePath);

            rightNode.parent = node.parent;
            rightNode.saveToFile(rightNodePath);

            parentNode.saveToFile(node.parent);
			// split the parent node if it exceeds the degree
            if (parentNode.keys.getCurr() >= degree) {
                splitNodes(parentNode, node.parent);
            }
            filesystem::remove(currPath);
        }
    }
	// function for insertion
    void insertNode(filesystem::path& root, const T& value,const long long& rowIndex) {
        if (root == "NULL") {
            //initialize the  folder
            path rootPath = folderPath / "NODES" / "ROOT.txt";

            Node newNode;
            Key newKey;
            newKey.key = value;
			newKey.indexes.push_back(rowIndex);
            newNode.isLeaf = true;
            newNode.keys.push_back(newKey);

            //save the root node
            newNode.saveToFile(rootPath);
            //update the root path
            root = rootPath;
        }
        else {
            // Locate the appropriate node for insertion
            Pair<filesystem::path, int, int> toBeInserted = searchNode(value);

            filesystem::path currPath = toBeInserted.first;
            Node node = Node::LoadFromFile(currPath,*this);

			// If the key already exists, update the index
			int low = 0, high = node.keys.getCurr() - 1;
			bool keyExists = false;
            while (low <= high) {
				int mid = low + (high - low) / 2;
				if (node.keys[mid].key == value) {
					node.keys[mid].indexes.push_back(rowIndex);
					node.saveToFile(currPath);
					keyExists = true;
					break;
				}
				else if (node.keys[mid].key < value) {
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
            }
            // Insert the new key
            if (!keyExists) {
                Key newKey;
                newKey.key = value;
				newKey.indexes.push_back(rowIndex);
                node.keys.insertSorted(newKey);
                node.saveToFile(currPath);

                // Split the node if it exceeds the degree
                if (node.keys.getCurr() >= degree) {
                    splitNodes(node, currPath);
                }
            }
        }
    }
	// helper function to remove leaf node
    void removeLeaf(filesystem::path& path, Node& node, int index) {
		int minKeys = ceil(degree / 2.0) - 1; // Minimum keys required in a node

        // base case : enough keys can remove without it being less than minKeys
        if (node.keys.getCurr() > minKeys) {
            node.keys.Destroy(index);
            node.saveToFile(path);
            return;
        }
        Node parentNode = Node::LoadFromFile(node.parent,*this);
        // case 2: borrow from left sibling
        if (index > 0) {
            Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1],*this);
            if (leftSibling.keys.getCurr() > minKeys) {
                Key borrowedKey = leftSibling.keys[leftSibling.keys.getCurr() - 1];
                leftSibling.keys.Destroy(leftSibling.keys.getCurr() - 1);
                node.keys.Destroy(index);
                node.keys.insertSorted(parentNode.keys[index - 1]);

                // Update parent key
                parentNode.keys[index - 1] = borrowedKey;

                leftSibling.saveToFile(parentNode.childrenPaths[index - 1]);
                parentNode.saveToFile(leftSibling.parent);
                node.saveToFile(path);
                return;
            }
        }

        // case 3: borrow from right sibling
        if (index < parentNode.childrenPaths.getCurr() - 1) {
			// borrow from right sibling
            Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1],*this);
            if (rightSibling.keys.getCurr() > minKeys) {
				// borrow from right sibling
                Key borrowedKey = rightSibling.keys[0];
                rightSibling.keys.Destroy(0);
                node.keys.Destroy(index);
                node.keys.insertSorted(parentNode.keys[index]);

                parentNode.keys[index] = borrowedKey;
				// save the nodes
                rightSibling.saveToFile(parentNode.childrenPaths[index + 1]);
                parentNode.saveToFile(rightSibling.parent);
                node.saveToFile(path);
                return;
            }
        }

        // case 4: merge with a sibling
        if (index > 0) {
            // merge with left sibling
            Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1],*this);
            // parentNode.keys.push_back(leftSibling.keys[index - 1]);
            Key newKey = parentNode.keys[index - 1];
            leftSibling.keys.push_back(newKey);
            for (int i = 0; i < node.keys.getCurr(); ++i) {
                leftSibling.keys.insertSorted(node.keys[i]);
            }
            if (!node.isLeaf) {
                for (int i = 0; i < node.childrenPaths.getCurr(); ++i) {
                    leftSibling.childrenPaths.push_back(node.childrenPaths[i]);
                }
            }
            parentNode.keys.Destroy(index - 1);
            filesystem::path deletePath = parentNode.childrenPaths[index - 1];
            parentNode.childrenPaths.Destroy(index - 1);
            leftSibling.keys.Destroy(index);
			// save the nodes
            leftSibling.saveToFile(parentNode.childrenPaths[index - 1]);
            parentNode.saveToFile(node.parent);

            filesystem::remove(deletePath);

        }
        else {
            // merge with right sibling
            Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1],*this);
            // parentNode.keys.push_back(rightSibling.keys[0]);
            Key newKey = parentNode.keys[index];
            node.keys.push_back(newKey);
            for (int i = 1; i < rightSibling.keys.getCurr(); ++i) {
                node.keys.insertSorted(rightSibling.keys[i]);
            }
            // If not leaf, also transfer child pointers
            if (!rightSibling.isLeaf) {
                for (int i = 0; i < rightSibling.childrenPaths.getCurr(); ++i) {
                    node.childrenPaths.push_back(rightSibling.childrenPaths[i]);
                }
            }

            parentNode.childrenPaths.Destroy(index + 1);
            parentNode.keys.Destroy(index);

            node.saveToFile(parentNode.childrenPaths[index]);
            parentNode.saveToFile(node.parent);

            filesystem::remove(parentNode.childrenPaths[index + 1]);
        }
        // checking if parent node gets messed up
        if (parentNode.keys.getCurr() < minKeys) {
            if (parentNode.parent == "NULL") {
                // If parent is root and has no keys left change root
                if (parentNode.childrenPaths.getCurr() == 1) {
                    // filesystem::remove(root);
                    Node newRoot = Node::LoadFromFile(parentNode.childrenPaths[0], *this);
                    this->rootPath = folderPath / "ROOT.txt";
                    newRoot.saveToFile(rootPath);
                    filesystem::remove(parentNode.childrenPaths[0]);
                }
            }
            else {
				// Recursive call to fix the parent node
                removeLeaf(parentNode.parent, parentNode, index);
            }
        }
    }
	// helper function to remove internal node
    void removeInternal(filesystem::path& path, Node& node, int index, T value = T()) {
		// Minimum keys required in a node
        int minKeys = ceil(degree / 2.0) - 1;

        
        Node leftSibling = Node::LoadFromFile(node.childrenPaths[index], *this);
        Node rightSibling = Node::LoadFromFile(node.childrenPaths[index + 1], *this);

		// Case 1: Borrow from left sibling
        if (leftSibling.keys.getCurr() > minKeys) {
            Node pre = leftSibling;
            filesystem::path prePath = node.childrenPaths[index];
            while (!pre.isLeaf) {
                pre = Node::LoadFromFile(prePath, *this);
                prePath = pre.childrenPaths[pre.childrenPaths.getCurr() - 1];
            }
            Key newKey = pre.keys.back();
            node.keys[index] = newKey;
            node.saveToFile(path);

            removeLeaf(prePath, pre, pre.keys.getCurr() - 1);
        }
		// Case 2: Borrow from right sibling
        else if (rightSibling.keys.getCurr() > minKeys) {
            Node suc = rightSibling;
            filesystem::path suckPath = node.childrenPaths[index + 1];
            while (!suc.isLeaf) {
                suc = Node::LoadFromFile(suckPath, *this);
                suckPath = suc.childrenPaths[0];
            }
            Key newKey = suc.keys[0];
            node.keys[index] = newKey;
            node.saveToFile(path);
            removeLeaf(suckPath, suc, 0);
        }
		// Case 3: Merge with left sibling
        else {
            // Key from parent to be merged into left sibling
            Key mergeKey = node.keys[index];
            if (mergeKey.key != value)
                leftSibling.keys.push_back(mergeKey);

            // Move all keys and children from the right sibling to the left sibling
            for (int i = 0; i < rightSibling.keys.getCurr(); ++i) {
                leftSibling.keys.push_back(rightSibling.keys[i]);
            }
            if (!rightSibling.isLeaf) {
                for (int i = 0; i < rightSibling.childrenPaths.getCurr(); ++i) {
                    leftSibling.childrenPaths.push_back(rightSibling.childrenPaths[i]);

                    // Update the parent reference for the child being moved
                    Node childNode = Node::LoadFromFile(rightSibling.childrenPaths[i], *this);
                    childNode.parent = node.childrenPaths[index]; // Update to leftSibling's file
                    childNode.saveToFile(rightSibling.childrenPaths[i]);
                }
            }

            // Remove the merged key and right child path from the parent node
            node.keys.Destroy(index);
            filesystem::path rightSiblingPath = node.childrenPaths[index];
            node.childrenPaths.Destroy(index);

            // Save updated left sibling and parent node
            leftSibling.saveToFile(node.childrenPaths[index]);
            node.saveToFile(path);

            // Remove the right sibling file
            filesystem::remove(rightSiblingPath);

            // Check if the parent node violates the minimum keys condition
            if (node.keys.getCurr() < minKeys) {
                if (node.parent != "NULL") {
                    Node parentNode = Node::LoadFromFile(node.parent, *this);
                    int parentIndex = parentNode.childrenPaths.search(path);

                    // Recursive call to fix the parent node
                    removeInternal(node.parent, parentNode, parentIndex);
                }
                else if (node.keys.getCurr() == 0) {
                    rootPath = node.childrenPaths[index - 1];
                    leftSibling.parent = "NULL";
                    leftSibling.saveToFile(rootPath);
                    filesystem::remove(path);
                }
            }
        }
    }
	// helper function to search Node for deletion
    Pair<filesystem::path, int, int> searchNode_Deletion(const T& value) {
		// if the tree is empty
        if (rootPath == "NULL") {
            return Pair<filesystem::path, int, int>("NULL", -1, -1);
        }
		// search for the node that contains the key
        filesystem::path currPath = rootPath;
        int childIndexInParent = -1;
        int keyIndexInNode = -1;
		// loop until the leaf node is reached
        while (true) {
			// load the node
            Node currNode = Node::LoadFromFile(currPath, *this);

            int i = 0;
			// find the index of the key in the node
            while (i < currNode.keys.getCurr() && value > currNode.keys[i].key) {
                i++;
            }
			// if the key is found
            if (i < currNode.keys.getCurr() && value == currNode.keys[i].key) {
                keyIndexInNode = i;
                break;
            }
			// if the key is not found
            if (currNode.isLeaf) {
                return Pair<filesystem::path, int, int>("NULL", -1, -1);
            }
			// update the path and the index of the child in the parent
            childIndexInParent = i;
            currPath = currNode.childrenPaths[i];
        }
		// return the path of the node, the index of the key in the node and the index of the child in the parent
        return Pair<filesystem::path, int, int>(currPath, keyIndexInNode, childIndexInParent);
    }
	// function to remove Node from the tree
    void removeNode(filesystem::path& root, const T& value) {
        if (root == "NULL") {
            // if treep empty throws an exception
            throw runtime_error("B-tree is empty.");
        }
        // search the node that we have to delete
        Pair<path, int, int> toBeRemoved = searchNode_Deletion(value);

        if (toBeRemoved.second == -1) {
			// if no instance of the key is found
            return;
        }
		// load the node to be removed
        Node node = Node::LoadFromFile(toBeRemoved.first, *this);
		// removing just leaf key from the tree
        if (node.parent == "NULL" && node.isLeaf) {
			// if the node is the root and is a leaf
            node.keys.removeAt(toBeRemoved.second);
            if (node.keys.getCurr() == 0) {
				// if the root has no keys left
                filesystem::remove(this->rootPath);
                this->rootPath = "NULL";
            }
            else {
				// update the root node
                node.saveToFile(toBeRemoved.first);
            }
        }
		// remove leaf key from the tree
        else if (node.isLeaf) {
			// sends file path the node is stored in, the node itself and the index of the key to be removed
            removeLeaf(toBeRemoved.first, node, toBeRemoved.third);
        }
		// remove internal key from the tree
        else {
			// sends file path the node is stored in, the node itself and the index of the key to be removed
            removeInternal(toBeRemoved.first, node, toBeRemoved.second, value);
        }

    }
	int degree; // Degree of the B-tree
	int nodeCount; // Used to name the text files
public:
    // constructor
    Btree(filesystem::path folderPath, int degree = 3) {
        this->rootPath = "NULL"; // initally kept as NULL
        this->folderPath = folderPath;
		this->branchPath = folderPath; // make the branch
        this->folderPath /= "TREE"; // make the folder
        this->degree = degree;
        if (!exists(this->folderPath)) {
            create_directories(this->folderPath);
            filesystem::path nodesPath = this->folderPath / "NODES"; // to hold all the nodes
            filesystem::create_directories(nodesPath);
        }
        nodeCount = 0; // used to name the text files
    }
    filesystem::path getRoot() {
        return rootPath;
    }
	// insert declared in parent tree class but implemented here
	// insert a key into the tree
    void insert(const T& data, const long long& rowIndex) override
    {
        insertNode(rootPath, data,rowIndex);
    }
	// remove declared in parent tree class but implemented here
	// remove a key from the tree
    void remove(const T& data, const long long& rowIndex) override
    {
        removeNode(rootPath, data);
    }
	// function to print the tree
    void print() override
    {
        printTree(rootPath);
    }
	// helper function to print the tree
    void printTree(filesystem::path root, int depth = 0)
    {
        cout << "depth " << depth << ": ";
        Node x = Node::LoadFromFile(root, *this);
        for (int i = 0; i < x.keys.getCurr(); i++)
        {
            cout << x.keys[i].key << " ";
        }
        cout << endl;

        depth++;
        if (x.childrenPaths.getCurr() != 0)
        {
            for (int i = 0; i < x.childrenPaths.getCurr(); i++)
            {
                printTree(x.childrenPaths[i], depth);
            }
        }
    }
	// Save the tree to a file
    void saveDataToFile()
    {
        ofstream file;
        filesystem::path path = folderPath;
        path += "\\TREE_DATA.txt";
        file.open(path);
        if (!file.is_open())
            throw runtime_error("Cannot open file: \'B-TREE_DATA.txt\' for writing.");
		file << rootPath << '\n'; // save root path
		file << folderPath << '\n'; // save folder path
		file << branchPath << '\n'; // save branch path
        file.close();
    }

	// Load the tree from a file
    void loadFromBranch(filesystem::path branchPath)
    {
		// all the data is stored in a file
        branchPath /= "TREE";
        branchPath /= "TREE_DATA.txt";
		// handling the case where the file doesnt exist
        if (!exists(branchPath))
            throw runtime_error("File to load tree from doesnt exist.");
        ifstream file(branchPath);
		// handling the case where the file cannot be opened
        if (!file.is_open())
            throw runtime_error("Cannot open file: \'AVL_DATA.txt\' for reading.");
		// file pathing and reading the data
        file >> rootPath;
        file >> folderPath;
        file >> this->branchPath;
        file.close();
    }

	// function to search for a key in the tree
	// declared in parent class
    Vector<long long> search(const T& data) override
    {
		// search for the key in the tree
		Pair<filesystem::path,int,int> searchNode = this->searchNode_Deletion(data);
        if (searchNode.second == -1) {
			// key not found
            cout << "No instances of key: " << data << " exist." << endl;
			return Vector<long long>(); // return an empty vector
        }
        else {
			// key found
			Node node = Node::LoadFromFile(searchNode.first, *this);
			return node.keys[searchNode.second].indexes; // return the indexes of the key
        }
    }
};