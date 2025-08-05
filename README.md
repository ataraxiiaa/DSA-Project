# GITLite – A Lightweight Version Control System in C++

## 📌 Overview

**GITLite** is a simplified Git-inspired version control system built in C++. Designed to manage large datasets efficiently, GITLite mimics core Git functionalities like **branching**, **committing**, **merging**, and **version history**, while leveraging advanced **tree data structures** and **Merkle hashing** to optimize data storage and integrity checking.

GITLite offers a hands-on demonstration of how version control systems operate internally and is particularly optimized for handling **large CSV files** with minimal memory usage.

---

## 🚀 Features

### ✅ Repository Initialization
- **Command:** `init <filename>`
- Uploads a large CSV file.
- Prompts user to choose a tree data structure:
  - AVL Tree
  - B Tree (customizable order)
  - Red-Black Tree
- User selects a column from the CSV to build the tree.
- Stores each node(row) in a separate file with metadata (parent/child linkage).

### ✅ Commit System
- **Command:** `commit "<message>"`
- Creates a new version snapshot of the current repository with a message and timestamp.
- Hashes are recalculated using either:
  - **Custom Hash (Modulo 29)**
  - **SHA-256**

### ✅ Branching
- **Command:** `branch <branch_name>`
- Creates a new branch by cloning the current tree and files into a new folder.

### ✅ Branch Checkout
- **Command:** `checkout <branch_name>`
- Switches to another branch, loading its tree and working state.

### ✅ Commit Log
- **Command:** `log`
- Displays commit history (ID, message, timestamp) for the current branch.

### ✅ Branch Listing
- **Command:** `branches`
- Lists all existing branches.

### ✅ Branch Deletion
- **Command:** `delete-branch <branch_name>`
- Deletes the specified branch folder.

### ✅ Merging
- **Command:** `merge <source_branch> <target_branch>`
- Merges commits and file changes from one branch into another.

### ✅ Tree Visualization (Bonus Feature)
- **Command:** `visualize-tree <branch_name>`
- Displays a textual representation of the tree structure.

### ✅ Current Branch Display
- **Command:** `current-branch`
- Shows the active working branch.

### ✅ Save Repository
- **Command:** `save`
- Saves the current repository state to a file.

### ✅ Load Repository
- **Command:** `load <file_name>`
- Loads repository state from a specified file.

### ✅ Insert Entry
- **Command:** `insert`
- Adds a new row/entry into the dataset.

### ✅ Search Entry
- **Command:** `search`
- Searches for entries in the dataset.

### ✅ Remove Entry
- **Command:** `remove`
- Removes an entry from the dataset.

### ✅ Update Entry
- **Command:** `update`
- Updates an existing entry in the dataset.

### ✅ Print Current Tree
- **Command:** `print`
- Prints the current tree structure.

### ✅ Print Merkle Tree
- **Command:** `print-merc`
- Prints the current Merkle tree for integrity verification.

---

## 🔍 Key Concepts Demonstrated

### 🧠 Data Structures
- **AVL Tree, B Tree, and Red-Black Tree** for optimized data insertion, deletion, and lookup.
- Each node corresponds to a real file on disk for efficient memory usage.

### 🧮 Hashing & Integrity
- **Merkle Tree** concept implemented for file integrity and change detection.
- Ability to detect and isolate corrupted nodes by comparing root hashes.

### 💾 File System Integration
- Changes to the tree (add/update/delete nodes) reflect in the actual file system.
- Ensures consistency and minimizes memory footprint.

### 📤 Efficient Data Transfer
- Instead of syncing full datasets, GITLite transfers only **affected tree nodes**, saving bandwidth and time.

---

## 📈 Real-World Applications

- **Large-scale Data Sync:** Ideal for teams managing large files (e.g., medical datasets, simulations).
- **Decentralized Storage Systems:** Tree-based hashing and file separation emulate distributed storage behavior.
- **Educational Use:** Helps students grasp Git internals, version control logic, and advanced data structures.

---

## 🧰 Technologies Used

| Technology      | Purpose                                       |
|----------------|-----------------------------------------------|
| **C++**         | Core implementation                          |
| **File I/O**    | Node-level data persistence                  |
| **Custom Hashing & SHA-256** | Data integrity and Merkle root creation |
| **Tree Structures** | Data organization and search optimization |

---

## 🧠 Skills Demonstrated

- Advanced C++ (file handling, classes, pointers)
- Implementation of self-balancing trees (AVL, B Tree, Red-Black Tree)
- Hashing algorithms and Merkle Trees
- File system synchronization techniques
- Efficient memory management with large datasets

---

## 📂 Example Commands

```bash
> init data.csv
Choose tree type (AVL/B/Red-Black): AVL
Select column to organize tree: PatientID

> commit "Initial commit"

> branch feature-x

> checkout feature-x

> commit "Added filtering for high-risk patients"

> log

> merge feature-x main

> visualize-tree main
```

---

## ⚠ Limitations & Scope for Future Work

- Tree visualization is textual (basic console view); future versions may integrate GUI or Graphviz.
- No remote syncing or network support yet.
- Merge conflicts are not resolved automatically—handled manually by user.

---

## 📚 Dataset Used

The project uses a simulated **healthcare dataset** containing:
- Patient demographics
- Medical conditions
- Hospital billing
- Admission/discharge logs

This enables realistic testing and performance evaluation for tree-based data handling.

---

## 📢 Final Notes

This project replicates the **core spirit of Git**, showcasing a version-controlled system with data integrity, branching, and change tracking — all from scratch in C++ without external libraries.

Ideal for students, educators, and developers looking to understand Git internals and data structure applications in real systems.
