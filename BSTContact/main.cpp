#include <iostream>
#include<sstream>
#include "ContactBST.h"

using namespace std;

void help() {
    cout << "---------------------------" << endl
    << "import <path>     :Import contacts from a CSV file"  << endl
    << "export <path>     :Export contacts to a CSV file" << endl
    << "add               :Add a new contact" << endl
    << "edit <key>        :Update a contact's details" << endl
    << "del <key>         :Delete a contact" << endl
    << "searchFor <key>   :Search for a contact" << endl
    << "markfv <key>      :Mark as favourite" << endl
    << "unmarkfv <key>    :Unmark as favourite" << endl
    << "printASC          :Print contacts in ascending order" << endl
    << "printDES          :Print contacts in descending order" << endl
    << "printfv           :Print all favourite contacts" << endl
    << "help              :Display the available commands" << endl
    << "exit              :Exit the program" << endl;
}

int main() {
    ContactBST myBST;
    help();
    string user_input;
    string command;
    string key;

    while(true)
    {
        cout<<">";
        getline(cin,user_input);

        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,key);

        //Node* root = myBST.getRoot();
        cout<<"----------------------------------"<<endl;
        if( command =="import") cout << myBST.importCSV(myBST.getRoot(), key) << endl;
        else if( command =="export")	cout << myBST.exportCSV(myBST.getRoot(), key) << endl;
        else if( command =="add")
        {
            Contact con;
            cin >> con;
            myBST.add_helper(con.give_key(), &con);
        }
        else if( command =="edit")	myBST.update(myBST.getRoot(), key);
        else if( command =="del")
        {
            cout << "check" << endl;
            myBST.remove(myBST.getRoot(), key);
        }
        else if( command =="searchFor")	myBST.search(myBST.getRoot(), key);
        else if( command =="markfv") myBST.markFav(myBST.getRoot(), key);
        else if( command =="unmarkfv")	myBST.unmarkFav(myBST.getRoot(), key);
        else if( command =="printASC")	myBST.printASC(myBST.getRoot());
        else if( command =="printDES") myBST.printDES(myBST.getRoot());
        else if( command == "printfv") myBST.printFav(myBST.getRoot());
        else if( command == "help") help();
        else if( command == "exit") break;
        else cout<< "Invalid command !!!" <<endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;

}

// /Users/levdenisov/Desktop/CLionProjects/Orders/April/AibarTalip/BSTContact/cmake-build-debug/contacts.csv