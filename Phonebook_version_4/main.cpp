/***********************************************************************************************************************
 *
 * Allie Fairweather
 *
 * CS2308
 *
 * Assignment 4
 *
 *
 *
 *
***********************************************************************************************************************/

#include "Contact.h"

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

void displayContacts(Contact*[], int*, bool);
void addContact(Contact**&, int*);
void searchContacts(Contact*[], int*);
void deleteContact(Contact**&, int*);
void loadDatabase(Contact**&, int*);
void saveToDatabase(Contact*[], int*);

string phoneNumberToString(long);
bool isEqual(Contact*, Contact*);

void sortContacts(Contact*[], int*);
void contactsMatchingSearchTerm(Contact*[], int*, string, Contact**&, int*);
void swap(Contact*&, Contact*&);
string toLower(string);
int indexOfContactInArray(Contact*[], int*, Contact*);
void addContactToArray(Contact*, Contact**&, int*);
void deleteContactFromArrayAtIndex(Contact**&, int*, int);

static const string DATABASE_TXT_FILE = "database.txt";
static const char DELIMITER = '~';

int main() {

    int* numberOfContacts = new int(0);
    Contact** contacts = new Contact*[*numberOfContacts];

    loadDatabase(contacts, numberOfContacts);

    int mainMenuChoice = 0;

    while (mainMenuChoice != 5) {

        cout << "\nSelect an operation...\n"
             << "1. Display all contacts.\n"
             << "2. Add new contact.\n"
             << "3. Search for contact.\n"
             << "4. Delete a contact.\n"
             << "5. Exit.\n\n";

        cin >> mainMenuChoice;

        switch (mainMenuChoice) {

            case 1:
                displayContacts(contacts, numberOfContacts, false);
                break;

            case 2:
                addContact(contacts, numberOfContacts);
                break;

            case 3:
                searchContacts(contacts, numberOfContacts);
                break;

            case 4:
                deleteContact(contacts, numberOfContacts);
                break;

            case 5:
                saveToDatabase(contacts, numberOfContacts);
                break;

        }
    }

    return 0;
}

void displayContacts(Contact* contacts[], int* numberOfContacts, bool isNumbered) {

    for (int i = 0; i < *numberOfContacts; i++) {

        Contact* contact = contacts[i];

        string phoneTypeString;

        switch (contact->setPhoneType(phoneType)) {
            case CELL:
                phoneTypeString = "Cell";
                break;
            case HOME:
                phoneTypeString = "Home";
                break;
            case WORK:
                phoneTypeString = "Work";
                break;
        }

        string listNumber;
        if (isNumbered) {
            listNumber = to_string(i + 1) + ". ";
        } else {
            listNumber = "";
        }

        cout << endl << listNumber
             << contact->getFirstName() << " "
             << contact->getLastName() << ", "
             << phoneTypeString << " "
             << phoneNumberToString(contact->getPhoneNumber());
    }

    cout << endl;
}

void addContact(Contact**& contacts, int* numberOfContacts) {

    Contact* contact = new Contact;
    string firstName;
    string lastName;

    cout << "\nFirst Name: ";
    cin >> contact->setFirstName(firstName);

    cout << "\nLast Name: ";
    cin >> contact->setLastName(lastN

    ame);

    bool isValidPhoneNumber = false;

    while (!isValidPhoneNumber) {

        string phoneNumber;
        cout << "\n10 Digit Phone Number (digits only): ";
        cin >> phoneNumber;

        isValidPhoneNumber = contact->setPhoneNumber(phoneNumber;)

    int phoneTypeInt = 0;

    while (phoneTypeInt < 1 || phoneTypeInt > 3) {

        cout << "\nSelect phone type...\n"
             << "1. Cell\n"
             << "2. Home\n"
             << "3. Work\n\n";

        cin >> phoneTypeInt;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (phoneTypeInt) {
            case 1:
                contact->setPhoneType(phoneType) = CELL;
                break;
            case 2:
                contact->setPhoneType(phoneType) = HOME;
                break;
            case 3:
                contact->setPhoneType(phoneType) = WORK;
                break;
        }
    }

    addContactToArray(contact, contacts, numberOfContacts);

    cout << "\nContact added.\n";
}

void searchContacts(Contact* contacts[], int* numberOfContacts) {

    cout << "\nEnter the last name of the contact: ";
    string searchTerm;
    cin >> searchTerm;

    int* numberOfMatchingContacts = new int(0);
    Contact** matchingContacts = new Contact*[*numberOfMatchingContacts];

    contactsMatchingSearchTerm(contacts, numberOfContacts, searchTerm, matchingContacts, numberOfMatchingContacts);

    if (*numberOfMatchingContacts > 0) {
        displayContacts(matchingContacts, numberOfMatchingContacts, false);
    } else {
        cout << "\nNo contacts matching the name: " << searchTerm << "." << endl;
    }

    delete[] matchingContacts;
    delete numberOfMatchingContacts;
}

void deleteContact(Contact**& contacts, int* numberOfContacts) {

    cout << "\nEnter the first or last name of the contact: ";
    string searchTerm;
    cin >> searchTerm;

    int* numberOfMatchingContacts = new int(0);
    Contact** matchingContacts = new Contact*[*numberOfMatchingContacts];

    contactsMatchingSearchTerm(contacts, numberOfContacts, searchTerm, matchingContacts, numberOfMatchingContacts);

    if (*numberOfMatchingContacts > 0) {

        cout << "\nSelect contact to delete...\n";
        displayContacts(matchingContacts, numberOfMatchingContacts, true);
        cout << endl;

        int selectionInt;
        cin >> selectionInt;

        Contact* contactSelectedForDelete = matchingContacts[selectionInt - 1];

        int indexToDelete = indexOfContactInArray(contacts, numberOfContacts, contactSelectedForDelete);

        deleteContactFromArrayAtIndex(contacts, numberOfContacts, indexToDelete);

        cout << "\nContact deleted.\n";

    } else {
        cout << "\nNo contacts matching the name: " << searchTerm << "." << endl;
    }

    delete[] matchingContacts;
    delete numberOfMatchingContacts;
}

void loadDatabase(Contact**& contacts, int* numberOfContacts) {

    ifstream fin;
    fin.open(DATABASE_TXT_FILE);

    string firstName;
    string lastName;
    string phoneNumberString;
    string phoneTypeString;

    int index = 0;

    while (getline(fin, firstName, DELIMITER)) {

        getline(fin, lastName, DELIMITER);
        getline(fin, phoneNumberString, DELIMITER);
        getline(fin, phoneTypeString);

        Contact* contact = new Contact;

        contact->firstName = firstName;
        contact->lastName = lastName;
        contact->phoneNumber = stol(phoneNumberString);

        int phoneTypeInt = stoi(phoneTypeString);

        switch (phoneTypeInt) {
            case 0:
                contact->phoneType = CELL;
                break;
            case 1:
                contact->phoneType = HOME;
                break;
            case 2:
                contact->phoneType = WORK;
                break;
        }

        addContactToArray(contact, contacts, numberOfContacts);
        index++;
    }

    fin.close();
}

void saveToDatabase(Contact* contacts[], int* numberOfContacts) {

    ofstream fout;
    fout.open(DATABASE_TXT_FILE);

    for (int i = 0; i <= (*numberOfContacts) - 1; i++) {

        Contact* contact = contacts[i];

        fout << contact->firstName << "~"
             << contact->lastName << "~"
             << contact->phoneNumber << "~"
             << contact->phoneType << endl;
    }

    fout.close();
}

string phoneNumberToString(long phoneNumberLong) {

    string phoneNumberString = to_string(phoneNumberLong);

    string areaCode = phoneNumberString.substr(0, 3);
    string prefix = phoneNumberString.substr(3, 3);
    string suffix = phoneNumberString.substr(6, 4);

    return "(" + areaCode + ")" + prefix + "-" + suffix;
}

bool isEqual(Contact* a, Contact* b) {

    if (a->lastName.compare(b->lastName) != 0) {
        return false;
    }

    if (a->firstName.compare(b->firstName) != 0) {
        return false;
    }

    if (a->phoneNumber != b->phoneNumber) {
        return false;
    }

    if (a->phoneType != b->phoneType) {
        return false;
    }

    return true;
}

void sortContacts(Contact* contacts[], int* numberOfContacts) {

    int maxIndex;
    int index;

    for (maxIndex = (*numberOfContacts) - 1; maxIndex > 0; maxIndex--) {

        for (index = 0; index < maxIndex; index++) {

            if (toLower(contacts[index]->lastName) > toLower(contacts[index + 1]->lastName)) {
                swap(contacts[index], contacts[index + 1]);
            }
        }
    }
}

void contactsMatchingSearchTerm(
        Contact* contacts[],
        int* numberOfContacts,
        string searchTerm,
        Contact**& results,
        int* numberOfResults) {

    *numberOfResults = 0;

    int first = 0;
    int middle;
    int last = (*numberOfContacts) - 1;

    while (first <= last) {

        middle = (first + last) / 2;

        if (toLower(contacts[middle]->lastName) == toLower(searchTerm)) {

            addContactToArray(contacts[middle], results, numberOfResults);

            bool didFind = true;
            int leftIndex = middle - 1;
            while (didFind && leftIndex >= 0) {
                if (toLower(contacts[leftIndex]->lastName) == toLower(searchTerm)) {
                    addContactToArray(contacts[leftIndex], results, numberOfResults);
                    leftIndex--;
                } else {
                    didFind = false;
                }
            }

            didFind = true;
            int rightIndex = middle + 1;
            while (didFind && rightIndex < (*numberOfContacts) - 1) {
                if (toLower(contacts[rightIndex]->lastName) == toLower(searchTerm)) {
                    addContactToArray(contacts[rightIndex], results, numberOfResults);
                    rightIndex++;
                } else {
                    didFind = false;
                }
            }

            return;

        } else if (toLower(searchTerm) > toLower(contacts[middle]->lastName)) {
            first = middle + 1;
        } else {
            last = middle - 1;
        }
    }
}

int indexOfContactInArray(Contact* contacts[], int* numberOfContacts, Contact* contact) {

    int first = 0;
    int middle;
    int last = *numberOfContacts - 1;

    while (first <= last) {

        middle = (first + last) / 2;

        if (isEqual(contacts[middle], contact)) {
            return middle;
        } else if (contact->lastName > contacts[middle]->lastName) {
            first = middle + 1;
        } else {
            last = middle - 1;
        }
    }

    return -1;
}

void swap(Contact*& a, Contact*& b) {
    Contact* temp = a;
    a = b;
    b = temp;
}

string toLower(string a) {
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    return a;
}

void addContactToArray(Contact* contact, Contact**& contacts, int* numberOfContacts) {

    int newNumberOfContacts = *numberOfContacts + 1;
    Contact** newContactsArray = new Contact*[newNumberOfContacts];

    for (int i = 0; i < (*numberOfContacts); i++) {
        newContactsArray[i] = contacts[i];
    }

    delete[] contacts;

    *numberOfContacts = newNumberOfContacts;
    newContactsArray[(*numberOfContacts) - 1] = contact;

    contacts = newContactsArray;

    sortContacts(contacts, numberOfContacts);
}

void deleteContactFromArrayAtIndex(Contact**& contacts, int* numberOfContacts, int indexToDelete) {

    int newNumberOfContacts = (*numberOfContacts) - 1;
    Contact **newContactsArray = new Contact *[newNumberOfContacts];

    int newIndex = 0;
    for (int i = 0; i < *numberOfContacts; i++) {
        if (i != indexToDelete) {
            newContactsArray[newIndex] = contacts[i];
            newIndex++;
        }
    }

    delete contacts[indexToDelete];
    delete[] contacts;
    *numberOfContacts = newNumberOfContacts;
    contacts = newContactsArray;

    sortContacts(contacts, numberOfContacts);
}