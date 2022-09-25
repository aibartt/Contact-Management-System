#include "contact.h"

Contact::Contact() {}

Contact::Contact(string &fname, string &lname, string &email, string &primaryPhone, string &city,
                 string &country, bool isFav) :
        fname(fname),
        lname(lname),
        email(email),
        primaryPhone(primaryPhone),
        city(city),
        country(country),
        isFav(isFav)
{
}

std::ostream& operator<<(std::ostream& out, const Contact& obj)
{
    out << obj.fname << " " << obj.lname << ", " << obj.email << ", " << obj.primaryPhone << ", " << obj.city << ", " << obj.country;
    return out;
}

std::istream& operator>>(std::istream& in, Contact& obj)
{
    cout << "Please enter the dails of the contact: " << endl
         << "First Name: "; in >> obj.fname;
    cout << "Last Name: "; in >> obj.lname;
    cout << "Email: "; in >> obj.email;
    cout << "Phone#: "; in >> obj.primaryPhone;
    cout << "City: "; in >> obj.city;
    cout << "Country: "; in >> obj.country;
    cout << "Do you want to add the contact in you favourites (y/n): "; in >> obj.isFav;
    return in;
}

string Contact::give_key() {
    string key = fname;
    key.push_back(' ');
    key.append(lname);
    return key;
}