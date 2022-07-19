//
// Created by Allie Fairweather on 2019-04-15.
//

#ifndef ASSIGNMENT4_H_CONTACT_H
#define ASSIGNMENT4_H_CONTACT_H

#include <string>
using namespace std;

enum PhoneType {
    CELL,
    HOME,
    WORK,
    UNKNOWN
};

class Contact {

private:
    string firstName;
    string lastName;
    string phoneNumber;
    PhoneType phoneType;

public:
    Contact(string firstName, string lastName);
    void setFirstName(string firstName);
    string getFirstName();
    void setLastName(string lastName);
    string getLastName();
    bool setPhoneNumber(string phoneNumber);
    string getPhoneNumber();
    void setPhoneType(PhoneType phoneType);
    PhoneType getPhoneType();
};


#endif //ASSIGNMENT4_H_CONTACT_H