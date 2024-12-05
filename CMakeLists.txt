cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DSA-Project)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyProject
        AVL.h
        Source.cpp "RedBlackTree.h" "String.h" "qq.h" "Btree.h" "Vector.h" "GitLite.h")