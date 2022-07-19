//
// Created by Allie Fairweather on 2019-04-15.
//

#include "Contact.h"

Contact::Contact(string firstName, string lastName){
    this->firstName = firstName;
    this->lastName = lastName;
    this->phoneNumber = " ";
    this->phoneType = UNKNOWN;

}

void Contact::setFirstName(string firstName) {
    this-> firstName = firstName;
}

string Contact::getFirstName() {
    return firstName;
}

void Contact::setLastName(string lastName) {
    this->lastName = lastName;
}

string Contact::getLastName() {
    return lastName;
}

bool Contact::setPhoneNumber(string phoneNumber) {
    this->phoneNumber = phoneNumber;
    phoneNumber.length();
    return true;

}

string Contact::getPhoneNumber() {
    return phoneNumber;
}

void Contact::setPhoneType(PhoneType phoneType) {
    this->phoneType = phoneType;
}

PhoneType Contact::getPhoneType() {
    return phoneType;
}
