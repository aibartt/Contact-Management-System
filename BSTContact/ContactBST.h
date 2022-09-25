#ifndef BSTCONTACT_CONTACTBST_H
#define BSTCONTACT_CONTACTBST_H

#include <iostream>
#include <vector>
#include <fstream>
#include "contact.h"
#include "MyVector.h"

using namespace std;

class Node {
public:
    friend class ContactBST;
    Node(Contact *data, string key);
    ~Node();
private:
    Node* left;
    Node* right;

    string key;
    MyVector <Contact> spis;
};

class ContactBST {
public:
    ContactBST();
    ~ContactBST();
    void remove_tree(Node *ptr);
    Node* getRoot();
    int importCSV(Node* ptr, string path);
    int exportCSV(Node* ptr, string path);
    void contact_record (Node *ptr, string path, int &count);
    Node* add(Node *ptr, string key, Contact *data);
    void add_helper(string key, Contact *data);
    Node* update(Node* ptr, string key);
    Node* remove(Node* ptr, string key);
    Node* remove_help(Node *ptr, string key);
    Node* search(Node* ptr, string key);
    bool markFav(Node* ptr, string key);
    bool unmarkFav(Node* ptr, string key);
    void printASC(Node* ptr);
    void printDES(Node* ptr);
    void printFav(Node* ptr);
    Node* findMin(Node *ptr);
private:
    Node *root;
};

#endif //BSTCONTACT_CONTACTBST_H
