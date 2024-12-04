#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Vector.h"
using namespace std;
using namespace std::filesystem;

template <class T>
class Btree {
    //===================================== B-Tree Node ==========================================
    struct Node {
        Vector<filesystem::path> keys;
        Vector<filesystem::path> children;
        bool isLeaf;
        filesystem::path directory;
        filesystem::path parent;

        Node() : isLeaf(true), directory("NULL"),parent("NULL") {}

        void saveKey(const T& key, const filesystem::path& nodeDirectory) {
            if (!filesystem::exists(nodeDirectory)) {
                create_directories(nodeDirectory);
                cout << "Created node directory: " << nodeDirectory << endl;
            }

            filesystem::path keyPath = nodeDirectory / (std::to_string(key) + ".txt");
            ofstream file(keyPath);
            if (!file.is_open()) {
                throw runtime_error("Unable to create file to save key");
            }
            file << key;
            file.close();
            keys.push_back(keyPath);
        }
        T loadKey(filesystem::path& path) {
            ifstream file(path);
            if (!file.is_open()) {
                throw runtime_error("Unable ot open file to read");
            }
            T key;
            file >> key;
            file.close();
            return key;
        }
    };

    filesystem::path root;
    filesystem::path folderPath;
    int degree;
    int curr;
    //===================================== File Functions ==========================================
    Node readNode(const filesystem::path& nodePath) {
        Node currentNode;
        currentNode.directory = nodePath;
        currentNode.isLeaf = true;

        for (filesystem::directory_entry entry : filesystem::directory_iterator(nodePath)) {
            if (filesystem::is_directory(entry)) {
                currentNode.isLeaf = false;
                currentNode.children.push_back(entry.path());
            } else if (entry.path().extension() == ".txt") {
                currentNode.keys.push_back(entry.path());
            }
        }

        return currentNode;
    }
    void updateNode(Node& node) {
        for (int i=0;i<node.keys.getCurr();++i) {
            if (!filesystem::exists(node.keys[i])) {
                ofstream file(node.keys[i]);
                file.close();
            }
        }
        for (int i=0;i<node.children.getCurr();++i) {
            if (!filesystem::exists(node.children[i])) {
                create_directories(node.children[i]);
            }
        }
    }
    void splitNode(Node& node) {
        int splitIndex = node.keys.getCurr() / 2;
        Node leftNode,rightNode;
        leftNode.directory = node.directory / ("child_"+to_string(curr++));
        rightNode.directory = node.directory / ("child_"+to_string(curr++));
        create_directories(leftNode.directory);
        create_directories(rightNode.directory);
        for (int i=0;i<splitIndex;++i) {
            leftNode.keys.push_back(node.keys[i]);
        }
        for (int i=splitIndex+1;i<node.keys.getCurr();++i) {
            rightNode.keys.push_back(node.keys[i]);
        }
        if (!node.isLeaf) {
            for (int i=0;i<=splitIndex;++i) {
                leftNode.children.push_back(node.children[i]);
            }
            for (int i=splitIndex+1;i<node.children.getCurr();++i) {
                rightNode.children.push_back(node.children[i]);
            }
        }
        updateNode(leftNode);
        updateNode(rightNode);
        if (node.directory == root) {
            Node newRoot;
            filesystem::path newRootDir = folderPath / "NewRoot";
            create_directories(newRootDir);
            newRoot.directory = newRootDir;

            newRoot.keys.push_back(node.keys[splitIndex]);
            newRoot.children.push_back(leftNode.directory);
            newRoot.children.push_back(rightNode.directory);

            updateNode(newRoot);
            root = newRootDir;
        }
        node.keys.clear();
        node.children.clear();
        node.keys.push_back(node.keys[splitIndex]);
        updateNode((node));
    }
    void insertNode(Node& node, const T& value) {
        if (node.isLeaf) {
            node.saveKey(value, node.directory);
            if (node.keys.getCurr() == degree) {
                splitNode(node);
            }
        } else {

        }
    }

public:
    //===================================== B-Tree UI Functions ==========================================
    Btree(const filesystem::path& folderPath, int degree = 3) : folderPath(folderPath), degree(degree) {
        curr = 0;
        root = folderPath / "root";
        if (!filesystem::exists(root)) {
            create_directories(root);
            cout << "Created root directory for B-tree: " << root << endl;
        }
    }

    void insert(const T& data) {
        Node rootNode = readNode(root);
        insertNode(rootNode, data);
        updateNode(rootNode);
    }
};
