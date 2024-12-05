#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Vector.h" // Ensure this file provides all necessary vector functionalities

using namespace std;
using namespace std::filesystem;
namespace fs = std::filesystem;

template <class T,class U,class V>
struct Pair {
    T first;
    U second;
    V third;
    Pair(T first = T(), U second = U(), V third = V()) : first(first), second(second), third(third) {}
};

template <class T>
class Btree {
    struct Key {
        T key;
        Vector<int> indexes;
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
        void updateFile(const path& keyFile) {
            if (keyFile.parent_path() == "") return;
            if (!exists(keyFile.parent_path())) {
                create_directories(keyFile.parent_path());
            }

            ofstream file(keyFile);
            if (!file.is_open()) {
                throw runtime_error("Unable to create file to save key");
            }
            file << key << '\n';
            for (int a = 0; a < indexes.getCurr(); a++) {
                file << indexes[a];
                if (a < indexes.getCurr() - 1)
                    file << ',';
                else
                    file << '\n';
            }
            file.close();
        }

        static Key loadFromFile(const path& keyFile) {
            Key loadedKey;
            ifstream file(keyFile);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file to load key");
            }
            file >> loadedKey.key;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            int index;
            char delim = ',';
            while (file >> index) {
                loadedKey.indexes.push_back(index);
                if (file.peek() == '\n' || file.eof()) {
                    break;
                }
                file.ignore(); // Skip the delimiter
            }
            file.close();
            return loadedKey;
        }
    };

    struct Node {
        path directory;
        path parent;
        path keysFolder;
        path childrenFolder;
        Vector<path> keyPaths;
        Vector<Key> keys;
        Vector<path> childrenPaths;
        bool isLeaf;

        Node(bool isLeaf = true) : isLeaf(isLeaf), directory("NULL"), parent("NULL") {}

        void saveToFolder(const path& nodeFolder) {
            // Create node folder with KEYS and CHILDREN subfolders
            if (!exists(nodeFolder)) {
                create_directories(nodeFolder);
                cout << "Created node directory: " << nodeFolder << endl;
            }

            keysFolder = nodeFolder / "KEYS";
            childrenFolder = nodeFolder / "CHILDREN";
            create_directories(keysFolder);
            create_directories(childrenFolder);
            directory = nodeFolder;

            // Write parent path
            path parentFile = nodeFolder / "PARENT.txt";
            ofstream parentFileStream(parentFile);
            if (!parentFileStream.is_open())
                throw runtime_error("Cannot open parent file for writing");
            parentFileStream << parent;
            parentFileStream.close();

            // Update keys
            for (int a = 0; a < keyPaths.getCurr(); a++) {
                keys[a].updateFile(keyPaths[a]);
            }
            // Update children
            path childrenFile = childrenFolder / "CHILDREN.txt";
            ofstream childrenFileStream(childrenFile);
            if (!childrenFileStream.is_open())
                throw runtime_error("Cannot open children file for writing");
            for (int a = 0; a < childrenPaths.getCurr(); a++) {
                childrenFileStream << childrenPaths[a].string() << '\n';
            }
            childrenFileStream.close();
        }

        static Node loadFromFolder(const path& nodeFolder) {
            Node loadedNode;
            if (!exists(nodeFolder)) {
                cout<<nodeFolder<<endl;
                throw runtime_error("Node folder does not exist");
            }

            loadedNode.directory = nodeFolder;

            // Save parent path
            path parentFile = loadedNode.directory / "PARENT.txt";
            if (!exists(parentFile)) {
                throw runtime_error("Parent file does not exist");
            }
            ifstream parentFileStream(parentFile);
            if (!parentFileStream.is_open())
                throw runtime_error("Cannot open parent file for reading");
            parentFileStream >> loadedNode.parent;
            parentFileStream.close();

            // Save keys folder path
            loadedNode.keysFolder = nodeFolder / "KEYS";
            if (!exists(loadedNode.keysFolder)) {
                create_directories(loadedNode.keysFolder);
            }

            // Save children folder path
            loadedNode.childrenFolder = nodeFolder / "CHILDREN";
            if (!exists(loadedNode.childrenFolder)) {
                create_directories(loadedNode.childrenFolder);
            }

            // Load keys and key paths
            for (const directory_entry& entry : directory_iterator(loadedNode.keysFolder)) {
                loadedNode.keyPaths.push_back(entry.path());
                Key currKey = Key::loadFromFile(entry.path());
                loadedNode.keys.insertSorted(currKey);
            }

            // Load children paths
            path childrenFile = loadedNode.childrenFolder / "CHILDREN.txt";
            if (exists(childrenFile)) {
                ifstream childrenFileStream(childrenFile);
                if (!childrenFileStream.is_open())
                    throw runtime_error("Cannot open children file for reading");

                string buffer;
                loadedNode.isLeaf = true;
                while (getline(childrenFileStream, buffer)) {
                    loadedNode.isLeaf = false;
                    loadedNode.childrenPaths.push_back(buffer);
                }
                childrenFileStream.close();
            }
            return loadedNode;
        }
    };
    Key createKey(const T& data, const filesystem::path& nodePath) {
        Key newKey;
        newKey.key = data;
        newKey.updateFile(nodePath / "KEYS" / (to_string(newKey.key) + ".txt"));
        return newKey;
    }
    Pair<filesystem::path, int, int> searchNode(const T& value) {
        if (root == "NULL") {
            return Pair<filesystem::path, int, int>();
        }

        filesystem::path currPath = root;
        int currIndex = 0;
        int currKeyIndex = -1;
        Node currNode = Node::loadFromFolder(currPath);

        while (!currNode.isLeaf) {
            currIndex = currNode.keys.getCurr();

            for (int a = 0; a < currNode.keys.getCurr(); a++) {
                if (value < currNode.keys[a].key) {
                    currIndex = a;
                    break;
                }
            }
            currPath = currNode.childrenPaths[currIndex];
            currNode = Node::loadFromFolder(currPath);
        }

        for (int a = 0; a < currNode.keys.getCurr(); a++) {
            if (value == currNode.keys[a].key) {
                currKeyIndex = a;
                break;
            }
        }

        return Pair<filesystem::path, int, int>(currPath, currIndex, currKeyIndex);
    }
    void splitNodes(Node& node,filesystem::path& currPath) {
        cout<<"Node Values: \n";
        for (int i=0;i<node.keys.getCurr();++i) {
            cout<<node.keys[i].key<<" ";
        }
        cout<<endl;

        int mid = node.keys.getCurr()/2;
        Key shiftedKey = node.keys[mid];
        Node leftNode,rightNode;
        filesystem::path leftNodePath = folderPath / ("NODE_" + to_string(nodeCount));
        nodeCount++;
        filesystem::path rightNodePath = folderPath / ("NODE_" + to_string(nodeCount));
        nodeCount++;
        for (int i = 0; i < mid; ++i) {
            path oldKeyPath = node.keyPaths[i];
            path newKeyPath = leftNode.keysFolder / oldKeyPath.filename();
            rename(oldKeyPath, newKeyPath);
            Key key = createKey(node.keys[i].key,leftNodePath);
            leftNode.keys.push_back(key);
            leftNode.keyPaths.push_back(newKeyPath);
        }

        for (int i = mid + 1; i < node.keys.getCurr(); ++i) {
            path oldKeyPath = node.keyPaths[i];
            path newKeyPath = rightNode.keysFolder / oldKeyPath.filename();
            rename(oldKeyPath, newKeyPath);
            Key key = createKey(node.keys[i].key,rightNodePath);
            rightNode.keys.push_back(key);
            rightNode.keyPaths.push_back(newKeyPath);
        }

        node.keys.clear();
        node.keyPaths.clear();

        if (!node.isLeaf) {
            for (int i = 0; i <= mid; ++i) {
                path oldChildPath = node.childrenPaths[i];
                path newChildPath = folderPath / oldChildPath.filename();

                // rename(oldChildPath, newChildPath);
                Node leftChild = Node::loadFromFolder(oldChildPath);
                leftChild.parent = leftNodePath;
                leftChild.saveToFolder(oldChildPath);
                leftNode.childrenPaths.push_back(newChildPath);
            }

            for (int i = mid + 1; i < node.childrenPaths.getCurr(); ++i) {
                path oldChildPath = node.childrenPaths[i];
                path newChildPath = folderPath / oldChildPath.filename();
                Node rightChild = Node::loadFromFolder(oldChildPath);
                rightChild.parent = rightNodePath;
                rightChild.saveToFolder(oldChildPath);
                // rename(oldChildPath, newChildPath);

                rightNode.childrenPaths.push_back(newChildPath);
            }

            node.childrenPaths.clear();
        }
        if (currPath == root || (!node.isLeaf && node.parent == "NULL")) {
            Node newRoot;
            filesystem::path newRootPath = folderPath / "ROOT";
            if (!exists(newRootPath)) {
                create_directories(newRootPath);
            }
            else {
                remove_all(newRootPath);
                create_directories(newRootPath);
            }
            // update children
            leftNode.parent = currPath;
            leftNode.saveToFolder(leftNodePath);

            rightNode.parent = currPath;
            rightNode.saveToFolder(rightNodePath);

            // move up the shifted key
            path shiftedKeyPath = newRootPath / "KEYS" / (to_string(shiftedKey.key) + ".txt");
            shiftedKey.updateFile(shiftedKeyPath);

            newRoot.keys.push_back(shiftedKey);
            newRoot.keyPaths.push_back(shiftedKeyPath);

            // saving children
            newRoot.childrenPaths.push_back(leftNodePath);
            newRoot.childrenPaths.push_back(rightNodePath);
            // save the new root
            newRoot.saveToFolder(newRootPath);

            // update the root path
            root = newRootPath;
            cout<<"Root at: "<<root<<endl;
        }
        else {

            Node parentNode = Node::loadFromFolder(node.parent);
            filesystem::path parentPath = node.parent;

            filesystem::path newKeyPath = parentNode.keysFolder / (to_string(shiftedKey.key) + ".txt");
            shiftedKey.updateFile(newKeyPath);

            parentNode.keys.insertSorted(shiftedKey);
            parentNode.keyPaths.push_back(newKeyPath);
            int index = 0;
            for (int i = 0; i < parentNode.childrenPaths.getCurr(); ++i) {
                if (parentNode.childrenPaths[i] == currPath) {
                    index = i;
                    break;
                }
            }
            parentNode.childrenPaths[index] = leftNodePath;
            parentNode.childrenPaths.inserAt(rightNodePath, index+1);

            leftNode.parent = node.parent;
            leftNode.saveToFolder(leftNodePath);

            rightNode.parent = node.parent;
            rightNode.saveToFolder(rightNodePath);

            parentNode.saveToFolder(node.parent);
            if (parentNode.keys.getCurr() >= degree) {
                splitNodes(parentNode, node.parent);
            }
            remove_all(currPath);
        }
    }
    void insertNode(filesystem::path& root,const T& value) {
        if (root == "NULL") {
            //initialize the root folder
            path rootPath = folderPath / "ROOT";
            create_directories(rootPath);

            Node newNode;
            Key newKey;
            newKey.key = value;

            //correct the key file path to be within the root folder
            path keyFile = rootPath /"KEYS"/(to_string(value) + ".txt");

            //create and save the key file
            newKey.updateFile(keyFile);

            //link the key file to the new node
            newNode.keys.push_back(newKey);
            newNode.keyPaths.push_back(keyFile);

            //save the root node folder
            newNode.saveToFolder(rootPath);

            //update the root path
            root = rootPath;
            cout<<"Root at: "<<root<<endl;
        }
        else {
            // get the data required to insert node
            // this includes the path of the node to be inserted into
            Pair<filesystem::path, int, int> toBeInserted = searchNode(value);
            filesystem::path currPath = toBeInserted.first;
            Node node = Node::loadFromFolder(currPath);
            // make new key
            Key newkey;
            newkey.key = value;
            path keysFolder = currPath / "KEYS";

            // open key folder if it does not exist
            if (!exists(keysFolder)) {
                create_directories(keysFolder);
            }
            path keyPath = keysFolder / (to_string(value) + ".txt");

            // updating the whole node with new inserted key
            newkey.updateFile(keyPath);
            node.keys.insertSorted(newkey);
            node.keyPaths.push_back(keyPath);
            node.saveToFolder(currPath);

            // splitting the node if it has more or equal to degree keys
            if (node.keys.getCurr() >= degree) {
                splitNodes(node,currPath);
            }
        }
    }
    filesystem::path root;
    filesystem::path folderPath;
    int degree;
    int nodeCount;
public:
    Btree(filesystem::path folderPath,int degree = 3) {
        this->root = "NULL";
        this->folderPath = folderPath;
        this->degree = degree;
        nodeCount = 0;
    }
    void insert(const T& value) {
        insertNode(root,value);
    }
};
