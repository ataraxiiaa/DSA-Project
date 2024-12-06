#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
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
        void saveToFile(const path& path) {
            if (path.empty() || path == "NULL") {
                throw runtime_error("File path not valid");
            }
            ofstream file(path);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for saving node.");
            }
            // save key count
            file <<keys.getCurr() << '\n';
            // save keys
            for (int i=0;i<keys.getCurr();++i) {
                file << keys[i].key << '\n';
                file << keys[i].indexes.getCurr() << '\n';
                for (int i = 0; i < keys[i].indexes.getCurr(); ++i) {
                    file << keys[i].indexes[i];
                    if (i < keys[i].indexes.getCurr() - 1) {
                        file << ',';
                    }
                }
                file << "ROW INDICES\n";
            }

            // save parent
            file << parent << '\n';

            // save children count and paths
            file << childrenPaths.getCurr()<<'\n';
            for (int i=0;i<childrenPaths.getCurr();++i) {
                file << childrenPaths[i].string() << '\n';
            }
            file.close();
        }
        static Node LoadFromFile(const path& nodePath) {
            if (!exists(nodePath)) {
                throw runtime_error("Node file does not exist.");
            }
            ifstream file(nodePath);
            if (!file.is_open()) {
                throw runtime_error("Unable to open file for writing.");
            }
            Node loadedNode;
            int keyCount;
            file >> keyCount;
            file.ignore(numeric_limits<streamsize>::max(),'\n');

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

            file >> loadedNode.parent;

            int numChildren;
            file >> numChildren;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < numChildren; ++i) {
                string childPath;
                getline(file, childPath);
                loadedNode.childrenPaths.push_back(childPath);
            }

            loadedNode.isLeaf = (numChildren == 0);

            file.close();
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
        Node currNode = Node::LoadFromFile(currPath);

        while (!currNode.isLeaf) {
            currIndex = currNode.keys.getCurr();

            for (int a = 0; a < currNode.keys.getCurr(); a++) {
                cout<<currNode.keys[a].key<<" "<<endl;
                if (value <= currNode.keys[a].key) {
                    currIndex = a;
                    currKeyIndex = a;
                    break;
                }
            }
            currPath = currNode.childrenPaths[currIndex];
            currNode = Node::LoadFromFile(currPath);
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
        filesystem::path leftNodePath = folderPath / ("DISK_" + to_string(nodeCount) + ".txt");
        nodeCount++;
        filesystem::path rightNodePath = folderPath / ("DISK_" + to_string(nodeCount) + ".txt");
        nodeCount++;
        for (int i = 0; i < mid; ++i) {
            leftNode.keys.push_back(node.keys[i]);
        }

        for (int i = mid + 1; i < node.keys.getCurr(); ++i) {
            rightNode.keys.push_back(node.keys[i]);
        }

        node.keys.clear();

        if (!node.isLeaf) {
            for (int i = 0; i <= mid; ++i) {
                path oldChildPath = node.childrenPaths[i];
                Node leftChild = Node::LoadFromFile(oldChildPath);
                leftChild.parent = leftNodePath;
                leftChild.saveToFile(oldChildPath);
                leftNode.childrenPaths.push_back(node.childrenPaths[i]);
            }

            for (int i = mid + 1; i < node.childrenPaths.getCurr(); ++i) {
                path oldChildPath = node.childrenPaths[i];
                Node rightChild = Node::LoadFromFile(oldChildPath);
                rightChild.parent = rightNodePath;
                rightChild.saveToFile(oldChildPath);
                rightNode.childrenPaths.push_back(node.childrenPaths[i]);
            }

            node.childrenPaths.clear();
        }
        if (currPath == root || (!node.isLeaf && node.parent == "NULL")) {
            Node newRoot;
            newRoot.isLeaf = false;
            filesystem::path newRootPath = folderPath / "ROOT.txt";

            // update children
            if (exists(newRootPath)) {
                filesystem::remove(newRootPath);
            }
            leftNode.parent = currPath;
            leftNode.saveToFile(leftNodePath);

            rightNode.parent = currPath;
            rightNode.saveToFile(rightNodePath);


            newRoot.keys.push_back(shiftedKey);

            // saving children
            newRoot.childrenPaths.push_back(leftNodePath);
            newRoot.childrenPaths.push_back(rightNodePath);
            // save the new root
            newRoot.saveToFile(newRootPath);

            // update the root path
            root = newRootPath;
            cout<<"Root at: "<<root<<endl;
        }
        else {

            Node parentNode = Node::LoadFromFile(node.parent);
            filesystem::path parentPath = node.parent;

            parentNode.keys.insertSorted(shiftedKey);

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
            leftNode.saveToFile(leftNodePath);

            rightNode.parent = node.parent;
            rightNode.saveToFile(rightNodePath);

            parentNode.saveToFile(node.parent);
            if (parentNode.keys.getCurr() >= degree) {
                splitNodes(parentNode, node.parent);
            }
            filesystem::remove(currPath);
        }
    }
    void insertNode(filesystem::path& root,const T& value) {
        if (root == "NULL") {
            //initialize the  folder
            if (!exists(folderPath)) {
                create_directories(folderPath);
            }
            path rootPath = folderPath / "ROOT.txt";

            Node newNode;
            Key newKey;
            newKey.key = value;
            newNode.isLeaf = true;
            newNode.keys.push_back(newKey);

            //save the root node
            newNode.saveToFile(rootPath);

            //update the root path
            root = rootPath;
            cout<<"Root at: "<<root<<endl;
        }
        else {
            // Locate the appropriate node for insertion
            Pair<filesystem::path, int, int> toBeInserted = searchNode(value);
            filesystem::path currPath = toBeInserted.first;
            Node node = Node::LoadFromFile(currPath);

            // Insert the new key
            Key newKey;
            newKey.key = value;
            node.keys.insertSorted(newKey);

            node.saveToFile(currPath);

            // Split the node if it exceeds the degree
            if (node.keys.getCurr() >= degree) {
                splitNodes(node, currPath);
            }
        }
    }
    void removeLeaf(filesystem::path& path, Node& node, int index) {
        int minKeys = ceil(degree / 2.0) - 1;

        // base case : enough keys can remove without it being less than minKeys
        if (node.keys.getCurr() > minKeys) {
            node.keys.Destroy(index);
            node.saveToFile(path);
            return;
        }
        Node parentNode = Node::LoadFromFile(node.parent);
        // case 2: borrow from left sibling
        if (index > 0) {
            Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1]);
            if (leftSibling.keys.getCurr() > minKeys) {
                Key borrowedKey = leftSibling.keys[leftSibling.keys.getCurr() - 1];
                leftSibling.keys.Destroy(leftSibling.keys.getCurr() - 1);
                node.keys.Destroy(index);
                node.keys.insertSorted(parentNode.keys[index-1]);

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
            Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1]);
            if (rightSibling.keys.getCurr() > minKeys) {
                Key borrowedKey = rightSibling.keys[0];
                rightSibling.keys.Destroy(0);
                node.keys.Destroy(index);
                node.keys.insertSorted(parentNode.keys[index]);

                parentNode.keys[index] = borrowedKey;

                rightSibling.saveToFile(parentNode.childrenPaths[index + 1]);
                parentNode.saveToFile(rightSibling.parent);
                node.saveToFile(path);
                return;
            }
        }

        // case 4: merge with a sibling
        if (index > 0) {
            // merge with left sibling
            Node leftSibling = Node::LoadFromFile(parentNode.childrenPaths[index - 1]);
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
            filesystem::path deletePath = parentNode.childrenPaths[index-1];
            parentNode.childrenPaths.Destroy(index-1);
            leftSibling.keys.Destroy(index);
            leftSibling.saveToFile(parentNode.childrenPaths[index - 1]);
            parentNode.saveToFile(node.parent);

            filesystem::remove(deletePath);

        } else {
            // merge with right sibling
            Node rightSibling = Node::LoadFromFile(parentNode.childrenPaths[index + 1]);
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

            parentNode.childrenPaths.Destroy(index+1);
            parentNode.keys.Destroy(index);

            node.saveToFile(parentNode.childrenPaths[index]);
            parentNode.saveToFile(node.parent);

            filesystem::remove(parentNode.childrenPaths[index + 1]);
        }
        if (parentNode.keys.getCurr() < minKeys) {
            if (parentNode.parent == "NULL") {
                // If parent is root and has no keys left change root
                if (parentNode.childrenPaths.getCurr() == 1) {
                    // filesystem::remove(root);
                    Node newRoot = Node::LoadFromFile(parentNode.childrenPaths[0]);
                    this->root = folderPath / "ROOT.txt";
                    newRoot.saveToFile(root);

                    filesystem::remove(parentNode.childrenPaths[0]);
                }
            } else {
                removeLeaf(parentNode.parent, parentNode, index);
            }
        }
    }
    void removeInternal(filesystem::path& path, Node& node, int index) {
        int minKeys = ceil(degree/2.0)-1;

        // if (index > 0)
        Node leftSibling = Node::LoadFromFile(node.childrenPaths[index-1]);
        Node rightSibling = Node::LoadFromFile(node.childrenPaths[index]);

        if (leftSibling.keys.getCurr() > minKeys) {
            Node pre = leftSibling;
            filesystem::path prePath = node.childrenPaths[index-1];
            while (!pre.isLeaf) {
                pre = Node::LoadFromFile(prePath);
                prePath = pre.childrenPaths[pre.childrenPaths.getCurr() - 1];
            }
            Key newKey = pre.keys.back();
            node.keys[index-1] = newKey;
            node.saveToFile(path);

            removeLeaf(prePath, pre, pre.keys.getCurr() - 1);
        }
        else if (rightSibling.keys.getCurr() > minKeys) {
            Node suc = rightSibling;
            filesystem::path suckPath = node.childrenPaths[index];
            while (!suc.isLeaf) {
                suc = Node::LoadFromFile(suckPath);
                suckPath = suc.childrenPaths[0];
            }
            Key newKey = suc.keys[0];
            node.keys[index-1] = newKey;
            node.saveToFile(path);
            removeLeaf(suckPath, suc, 0);
        }
        else {
            // move key down and merge
            cout<<"Key values: \n";
            for (int i=0;i<node.keys.getCurr();++i) {
                cout<<node.keys[i].key<<" ";
                cout<<node.childrenPaths[i].string()<<endl;
            }
            cout<<endl;
            leftSibling.keys.push_back(node.keys[index-1]);

            // move all keys and children from right child to left child
            for (int i = 0; i < rightSibling.keys.getCurr(); ++i) {
                leftSibling.keys.push_back(rightSibling.keys[i]);
            }
            if (!rightSibling.isLeaf) {
                for (int i = 0; i < rightSibling.childrenPaths.getCurr(); ++i) {
                    leftSibling.childrenPaths.push_back(rightSibling.childrenPaths[i]);
                }
            }

            // Remove the key and right child path from the parent node
            node.keys.Destroy(index-1);
            node.childrenPaths.Destroy(index + 1);

            // Save updated nodes
            leftSibling.saveToFile(node.childrenPaths[index]);
            node.saveToFile(path);

            filesystem::remove(node.childrenPaths[index + 1]);

            if (node.keys.getCurr() < minKeys) {
                if (node.parent != "NULL") {
                    Node parentNode = Node::LoadFromFile(node.parent);
                    int parentIndex = parentNode.childrenPaths.search(path);
                    removeInternal(node.parent, parentNode, parentIndex);
                } else if (node.keys.getCurr() == 0) {
                    root = node.childrenPaths[index];
                    leftSibling.parent = "NULL";
                    leftSibling.saveToFile(root);
                    filesystem::remove(path);
                }
            }
        }
    }
    Pair<filesystem::path, int, int> searchNode_Deletion(const T& value) {
        if (root == "NULL") {
            return Pair<filesystem::path, int, int>("NULL", -1, -1);
        }

        filesystem::path currPath = root;
        int childIndexInParent = -1;
        int keyIndexInNode = -1;

        while (true) {
            Node currNode = Node::LoadFromFile(currPath);

            int i = 0;
            while (i < currNode.keys.getCurr() && value > currNode.keys[i].key) {
                i++;
            }

            if (i < currNode.keys.getCurr() && value == currNode.keys[i].key) {
                keyIndexInNode = i;
                break;
            }

            if (currNode.isLeaf) {
                return Pair<filesystem::path, int, int>("NULL", -1, -1);
            }

            childIndexInParent = i;
            currPath = currNode.childrenPaths[i];
        }

        return Pair<filesystem::path, int, int>(currPath, keyIndexInNode, childIndexInParent);
    }

    void removeNode(filesystem::path& root,const T& value) {
        if (root == "NULL") {
            throw runtime_error ("B-tree is empty.");
        }
        Pair<path,int,int> toBeRemoved = searchNode_Deletion(value);

        if (toBeRemoved.third == -1) {
            return;
        }

        Node node = Node::LoadFromFile(toBeRemoved.first);
        // removing just leaf key
        if (node.parent == "NULL" && node.isLeaf) {
            node.keys.removeAt(toBeRemoved.third);
            if(node.keys.getCurr() == 0) {
                filesystem::remove(this->root);
                this->root = "NULL";
            }
            else {
                node.saveToFile(toBeRemoved.first);
            }
        }
        else if (node.isLeaf) {
            removeLeaf(toBeRemoved.first,node,toBeRemoved.third);
        }
        else {
            removeInternal(toBeRemoved.first,node,toBeRemoved.third);
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
    filesystem::path getRoot() {
        return root;
    }
    void insert(const T& value) {
        insertNode(root,value);
    }
    void remove(const T& value) {
        removeNode(root,value);
    }
    void printTree(filesystem::path root, int depth = 0)
    {
        cout << "depth " << depth << ": ";
        Node x = Node::LoadFromFile(root);
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
};
