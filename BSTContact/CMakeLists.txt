cmake_minimum_required(VERSION 3.21)
project(BSTContact)

set(CMAKE_CXX_STANDARD 17)

add_executable(BSTContact main.cpp ContactBST.cpp ContactBST.h contact.cpp contact.h MyVector.cpp MyVector.h)
