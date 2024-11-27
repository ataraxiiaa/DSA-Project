#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

int main()
{
   /* RedBlackTree<int> tree1("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\LR");
    int values[] = { 30, 20, 25, 40, 35, 50, 45 };

    for (int val : values) {
        tree1.insert(val);
    }
    tree1.print();*/
    RedBlackTree<String> tree2("C:\\Users\\HP\\source\\repos\\ataraxiiaa\\DSA-Project\\NameTest");

    std::ifstream file("C:\\Users\\hp\\Downloads\\HealthCare-dataset\\healthcare_dataset.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    char line[1024]; // Buffer for reading lines
    long long counter = 0;

    // Skip the header line if present
    if (file.getline(line, sizeof(line))) {
        std::cout << "Skipping header: " << line << std::endl;
    }

    while (file.getline(line, sizeof(line))) {
        // Debug output to verify the line being read
        std::cout << counter++ << ": Reading line: " << line << std::endl;

        int index = 0; // Index for iterating through the line
        String name;   // To store the name (first column)

        // Extract the first column (up to the first comma)
        while (line[index] != ',' && line[index] != '\0') {
            name += line[index++];
        }

        // Insert the extracted name into the tree
        tree2.insert(name);
    }

    file.close();

    // Print the tree to verify the data
    tree2.print();

    return 0;
}

