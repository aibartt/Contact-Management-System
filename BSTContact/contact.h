#ifndef BSTCONTACT_CONTACT_H
#define BSTCONTACT_CONTACT_H

#include <iostream>

using namespace std;

class Contact
{
private:
    string fname;
    string lname;
    string email;
    string primaryPhone;
    string city;
    string country;
    bool isFav;

public:
    Contact(string &fname, string &lname, string &email, string &primaryPhone, string &city,
            string &country, bool isFav);
    Contact();

    friend class ContactBST;
    friend class Node;
    string give_key();

    friend std::ostream& operator<<(std::ostream& out, const Contact& obj);
    friend std::istream& operator>>(std::istream& in, Contact& obj);
};


#endif //BSTCONTACT_CONTACT_H
