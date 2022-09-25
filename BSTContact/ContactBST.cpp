#include "ContactBST.h"


Node::Node(Contact *data, string key) {
    left = nullptr;
    right = nullptr;
    spis.push_back(*data);
    this->key = key;
}

Node::~Node() {}

ContactBST::ContactBST() : root(nullptr) {}

ContactBST::~ContactBST() {
    remove_tree(root);
}

void ContactBST::remove_tree(Node *ptr) {
    if (ptr == nullptr) {
        return;
    }
    cout << "check" << endl;
    remove_tree(ptr->left);
    remove_tree(ptr->right);
    delete ptr;
}

Node* ContactBST::getRoot(){
    return root;
}

int ContactBST::importCSV(Node* ptr, string path) {
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        return -1;
    } else {
        int count = 0;
        string line;
        while (!fin.eof()) {
            line = "";
            getline(fin, line);
            string fname, lname, email, primaryPhone, city, country;
            bool isFav;
            size_t i = 0;
            while(line[i] != ',') {
                fname.push_back(line[i]);
                i++;
            } i+= 2;
            while(line[i] != ',') {
                lname.push_back(line[i]);
                i++;
            } i+= 2;
            while(line[i] != ',') {
                email.push_back(line[i]);
                i++;
            } i+= 2;
            while(line[i] != ',') {
                primaryPhone.push_back(line[i]);
                i++;
            } i+= 2;
            while(line[i] != ',') {
                city.push_back(line[i]);
                i++;
            } i+= 2;
            while(line[i] != ',') {
                country.push_back(line[i]);
                i++;
            } i+= 2;
            if (line[i] == '1') {
                isFav = true;
            } else {
                isFav = false;
            }
            Contact* data = new Contact(fname, lname, email, primaryPhone, city, country, isFav);
            string key;
            key.append(fname); key.push_back(' '); key.append(lname);
            add_helper(key, data);
            delete data;
            count++;
        }
        return count;
    }
}

void ContactBST::contact_record (Node *ptr, string path, int &count) {
    if (ptr == nullptr) {
        return;
    }
    if (ptr->left != nullptr) {
        contact_record(ptr->left, path, count);
    }
    ofstream ref_file;
    ref_file.open(path, std::ios_base::app);
    for (size_t i = 0; i < ptr->spis.size(); i++) {
        ref_file << ptr->spis[i].fname << ", " << ptr->spis[i].lname << ", " << ptr->spis[i].email << ", " << ptr->spis[i].primaryPhone << ", "
        << ptr->spis[i].city << ", " << ptr->spis[i].country << ", " << int(ptr->spis[i].isFav) << endl;
        count++;
    }
    ref_file.close();
    if (ptr->right != nullptr) {
        contact_record(ptr->right, path, count);
    }
}

int ContactBST::exportCSV(Node* ptr, string path) {
    std::ofstream ref_file;
    ref_file.open(path);
    if (!ref_file.is_open()) {
        return -1;
    } else {
        ref_file.close();
        int count = 0;
        contact_record(ptr, path, count);
        return count;
    }
}

void ContactBST::add_helper(string key, Contact *data) {
    root = add(root, key, data);
}

Node* ContactBST::add(Node *ptr, string key, Contact *data) {
    if (ptr == nullptr) {
        return new Node(data, key);
    }
    if (ptr->key > key) {
        ptr->left = add(ptr->left, key, data);
    } else if (ptr->key < key) {
        ptr->right = add(ptr->right, key, data);
    } else if (ptr->key == key) {
        ptr->spis.push_back(*data);
    }
    return ptr;
}

Node* ContactBST::update(Node* ptr, string key) {
    if (ptr == nullptr) {
        cout << "Nothing found" << endl;
        return nullptr;
    } else if (key > ptr->key) {
        update(ptr->right, key);
    } else if (key < ptr->key) {
        update(ptr->left, key);
    } else if (key == ptr->key) {
        int key_person;
        int key_parameter;
        char update_stop = 'y';
        cout << ptr->spis.size() << " records found:" << endl;
        for (size_t i = 0; i < ptr->spis.size(); i++) {
            cout << i + 1 << ". " << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' '
            << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' ' << ptr->spis[i].city << ' ' << ptr->spis[i].country << endl;
        }
        cout << endl << "Please select the record you want to edit: ";
        cin >> key_person;
        while (key_person < 1 || key_person > ptr->spis.size()) {
            cin >> key_person;
        }
        while (update_stop == 'y') {
            cout
                    << "Which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4) Phone, 5) City, 6) Country: ";
            cin >> key_parameter;
            while (key_parameter < 1 || key_parameter > 6) {
                cin >> key_parameter;
            }
            if (key_parameter == 1) {
                cout << "Please enter the new First Name: ";
                cin >> ptr->spis[key_person - 1].fname;
            } else if (key_parameter == 2) {
                cout << "Please enter the new Last Name: ";
                cin >> ptr->spis[key_person - 1].lname;
            } else if (key_parameter == 3) {
                cout << "Please enter the new email: ";
                cin >> ptr->spis[key_person - 1].email;
            } else if (key_parameter == 4) {
                cout << "Please enter the new number phone: ";
                cin >> ptr->spis[key_person - 1].primaryPhone;
            } else if (key_parameter == 5) {
                cout << "Please enter the new city: ";
                cin >> ptr->spis[key_person - 1].city;
            } else if (key_parameter == 6) {
                cout << "Please enter the new country: ";
                cin >> ptr->spis[key_person - 1].country;
            }
            cout << "Do you want to edit another field (y/n)? ";
            cin >> update_stop;
            while (update_stop != 'y' && update_stop != 'n') {
                cin >> update_stop;
            }
        }
    }
    return ptr;
}

Node* ContactBST::remove(Node* ptr, string key) {
    Node* temp;
    if (ptr == nullptr) {
        return nullptr;
    } else if (key > ptr->key) {
        remove(ptr->right, key);
    } else if (key < ptr->key) {
        remove(ptr->left, key);
    } else if (key == ptr->key) {
        int key_person;
        int key_parameter;
        char update_stop = 'y';
        cout << ptr->spis.size() << " records found:" << endl;
        for (size_t i = 0; i < ptr->spis.size(); i++) {
            cout << i + 1 << ". " << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' '
                 << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' ' << ptr->spis[i].city << ' ' << ptr->spis[i].country << endl;
        }
        cout << endl << "Please select the record you want to edit: ";
        cin >> key_person;
        while (key_person < 1 || key_person > ptr->spis.size()) {
            cin >> key_person;
        }
        Contact* it = ptr->spis.cbegin();
        ptr->spis.erase(key_person - 1);
        cout << "The contact record has succesfully benn deleted!" << endl;
        if (ptr->spis.empty()) {
            remove_help(root, key);
        }
    }
    return ptr;
}

Node* ContactBST::remove_help (Node *ptr, string key) {
    Node* temp;
    if (ptr == nullptr)
        return ptr;
    if (key < ptr->key)
        ptr->left = remove_help(ptr->left,key);
    else if (key > ptr->key)
        ptr->right = remove_help(ptr->right,key);
    else{
        if (ptr != nullptr && ptr->left == nullptr && ptr->right == nullptr){ // if it is a leaf node
            delete ptr;
            ptr = nullptr;
        }
        else if (ptr->right && ptr->left){
            temp = findMin(ptr->right);
            ptr->key = temp->key;
            ptr->right = remove_help(ptr->right, ptr->key);
        }
        else{
            temp = ptr;
            if (ptr->right == nullptr){
                ptr = ptr->left;
            }
            else if (ptr->left == nullptr){
                ptr = ptr->right;
            }
            delete temp;
        }
    }
    return ptr;
}

Node* ContactBST::search(Node* ptr, string key) {
    if (ptr == nullptr) {
        cout << "User with this key does not exist" << endl;
        return nullptr;
    } else if (key > ptr->key) {
        search(ptr->right, key);
    } else if (key < ptr->key) {
        search(ptr->left, key);
    } else if (key == ptr->key) {
        int key_person;
        int key_parameter;
        char update_stop = 'y';
        cout << ptr->spis.size() << " records found:" << endl;
        for (size_t i = 0; i < ptr->spis.size(); i++) {
            cout << i + 1 << ". First name: " << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << endl
                 << "   Email: " << ptr->spis[i].email << endl
                 << "   Phone#: " << ptr->spis[i].primaryPhone << endl
                 << "   City: " << ptr->spis[i].city << endl
                 << "   Country: " << ptr->spis[i].country << endl;
        }
        return ptr;
    }
    return ptr;
}

Node* ContactBST::findMin(Node *ptr) {
    if (ptr == nullptr)
        return nullptr;
    else if (ptr->left == nullptr)
        return ptr;
    else
        return findMin(ptr->left);
}

bool ContactBST::markFav(Node* ptr, string key) {
    if (ptr == nullptr) {
        cout << "User with this key does not exist" << endl;
        return false;
    } else if (key > ptr->key) {
        markFav(ptr->right, key);
    } else if (key < ptr->key) {
        markFav(ptr->left, key);
    } else if (key == ptr->key) {
        int key_person;
        cout << ptr->spis.size() << " records found:" << endl;
        for (size_t i = 0; i < ptr->spis.size(); i++) {
            cout << i + 1 << ". " << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' '
                 << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' ' << ptr->spis[i].city << ' ' << ptr->spis[i].country << endl;
        }
        cout << endl << "Please select the record you want to mark as favorite: ";
        cin >> key_person;
        while (key_person < 1 || key_person > ptr->spis.size()) {
            cin >> key_person;
        }
        if (!(ptr->spis[key_person - 1].isFav)) {
            ptr->spis[key_person - 1].isFav = true;
            cout << ptr->spis[key_person - 1].fname << ' ' << ptr->spis[key_person - 1].lname << " (" << ptr->spis[key_person - 1].email
            << ") has successfully been marked as favorite" << endl;
            return true;
        } else {
            cout << ptr->spis[key_person - 1].fname << ' ' << ptr->spis[key_person - 1].lname << " (" << ptr->spis[key_person - 1].email
                 << ") already marked as favorite" << endl;
            return false;
        }
    }
    return false;
}

bool ContactBST::unmarkFav(Node* ptr, string key) {
    if (ptr == nullptr) {
        cout << "User with this key does not exist" << endl;
        return false;
    } else if (key > ptr->key) {
        unmarkFav(ptr->right, key);
    } else if (key < ptr->key) {
        unmarkFav(ptr->left, key);
    } else if (key == ptr->key) {
        int key_person;
        cout << ptr->spis.size() << " records found:" << endl;
        for (size_t i = 0; i < ptr->spis.size(); i++) {
            cout << i + 1 << ". " << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' '
                 << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' ' << ptr->spis[i].city << ' ' << ptr->spis[i].country << endl;
        }
        cout << endl << "Please select the record you want to mark as favorite: ";
        cin >> key_person;
        while (key_person < 1 || key_person > ptr->spis.size()) {
            cin >> key_person;
        }
        if (ptr->spis[key_person - 1].isFav) {
            ptr->spis[key_person - 1].isFav = false;
            cout << ptr->spis[key_person - 1].fname << ' ' << ptr->spis[key_person - 1].lname << " (" << ptr->spis[key_person - 1].email
                 << ") has successfully been unmarked as favorite" << endl;
            return true;
        } else {
            cout << ptr->spis[key_person - 1].fname << ' ' << ptr->spis[key_person - 1].lname << " (" << ptr->spis[key_person - 1].email
                 << ") already unmarked as favorite" << endl;
            return false;
        }
    }
    return false;
}

void ContactBST::printASC(Node* ptr) {
    if (ptr == nullptr) {
        return;
    }
    if (ptr->left != nullptr) {
        printASC(ptr->left);
    }
    for (size_t i = 0; i < ptr->spis.size(); i++) {
        cout << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' ' << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' '
             << ptr->spis[i].city << ' ' << ptr->spis[i].country << ' ' << int(ptr->spis[i].isFav) << endl;
    }
    if (ptr->right != nullptr) {
        printASC(ptr->right);
    }
}

void ContactBST::printDES(Node* ptr) {
    if (ptr == nullptr) {
        return;
    }
    if (ptr->right != nullptr) {
        printDES(ptr->right);
    }
    for (size_t i = 0; i < ptr->spis.size(); i++) {
        cout << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' ' << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone << ' '
        << ptr->spis[i].city << ' ' << ptr->spis[i].country << ' ' << int(ptr->spis[i].isFav) << endl;
    }
    if (ptr->left != nullptr) {
        printDES(ptr->left);
    }
}

void ContactBST::printFav(Node* ptr) {
    if (ptr == nullptr) {
        return;
    }
    if (ptr->left != nullptr) {
        printFav(ptr->left);
    }
    for (size_t i = 0; i < ptr->spis.size(); i++) {
        if (ptr->spis[i].isFav) {
            cout << ptr->spis[i].fname << ' ' << ptr->spis[i].lname << ' ' << ptr->spis[i].email << ' ' << ptr->spis[i].primaryPhone
            << ' ' << ptr->spis[i].city << ' ' << ptr->spis[i].country << ' ' << int(ptr->spis[i].isFav) << endl;
        }
    }
    if (ptr->right != nullptr) {
        printFav(ptr->right);
    }
}