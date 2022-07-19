/*
Allison Fairweather

Assignment 1

02-15-2019

*/

//This program adds and displays contacts in a phone book.
#include <iostream>
#include<fstream>
#include<string>
#include <algorithm>

using namespace std;

enum PhoneType {
    CELL,
    HOME,
    WORK
};

struct Contact {
    string firstName;
    string lastName;
    long phoneNumber;
    PhoneType phoneType;
};

void displayList(Contact phoneBook[], int friends, int position, bool caseSearch);
void enterContact(Contact phoneBook[], int &friends);
void bubbleSort(Contact phoneBook[], int &friends);
int binarySearch(Contact phoneBook[], int &friends, string value);
void exitFile(fstream&, Contact phoneBook[], int &friends);
string toLower(string);
void deleteContact(Contact phoneBook[], int &friends);
int main() {

    string decoy1;
    int decoy2;

    fstream fin;
    fin.open("database.txt",ios::in);

    const int MAX_CONTACTS = 50;
    Contact phoneBook[MAX_CONTACTS];

    if (!fin) {
        cout << "File did not open." << endl;

        exit(1);
    }

    int friends = 0;

    while (!fin.eof()) {
        getline(fin, phoneBook[friends].firstName, '~');
        getline(fin, phoneBook[friends].lastName, '~');
        getline(fin, decoy1, '~');
        phoneBook[friends].phoneNumber = stol(decoy1);
        getline(fin, decoy1);
        decoy2 = stoi(decoy1);
        phoneBook[friends].phoneType = static_cast <PhoneType>(decoy2);
        friends++;
    }
    fin.close();
    int choice;
    string value;
    int results;
    bool menuLoop = true, caseSearch;


    while (menuLoop) {
        results = 0;
        caseSearch = false;
        cout << "1. Display list of all contacts." << endl;
        cout << "2. Add	a new contact." << endl;
        cout << "3. Search for a contact given the contact’s first or last name or part ";
        cout << "of the contact’s first or last name." << endl;
        cout << "4. Delete a contact." << endl;
        cout << "5. Exit program.\n" << endl;

        cout << "Enter a choice" << endl;
        cin >> choice;


        switch (choice) {
            case 1:
                displayList(phoneBook, friends, results, caseSearch);
                break;
            case 2:
                enterContact(phoneBook, friends);
                break;
            case 3:
                caseSearch = true;
                cout << "Enter the Last name of the person you would like to search for " << endl;
                cin >> value;

               results = binarySearch(phoneBook, friends, value);


                if(results == -1)
                    cout << "That Name does not exist." << endl;
                else{
                    cout << "The contact info is  " << endl;
                    displayList(phoneBook, friends, results, caseSearch);

                }
                break;
            case 4:
                deleteContact(phoneBook, friends);
                break;
            case 5:
                exitFile(fin, phoneBook, friends);

                menuLoop = false;
            default:
                cout << "Input Invalid: Pick a number 1 - 5 " << endl;
                break;
        }

    }
return 0;

}

string toLower(string a) {
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    return a;
}

void displayList(Contact phoneBook[], int friends, int position, bool caseSearch) {

    bubbleSort(phoneBook, friends);
    if(caseSearch)
        friends = position+1;

    for (int i = position; i < friends; i++) {

        string pstring = to_string(phoneBook[i].phoneNumber);
        string p1(pstring, 0, 3);
        string p2(pstring, 3, 3);
        string p3(pstring, 6, 4);
        string p4;

        if (phoneBook[i].phoneType == HOME) {
            p4 = "HOME";
        }
        if (phoneBook[i].phoneType == CELL) {
            p4 = "CELL";
        }
        if (phoneBook[i].phoneType == WORK) {
            p4 = "WORK";
        }

        cout << phoneBook[i].firstName << " " << phoneBook[i].lastName << ", " << p4;
        cout << ", (" << p1 << ")" << p2 << "-" << p3 << endl;
    }
    cout << endl;
}

void enterContact(Contact phoneBook[], int &friends) {
    int phone1;
    long phoneNum;
    bool isValidPhoneNumber = false;
    bool isValidPhoneType = false;

    cout << "Enter first Name" << endl;
    cin >> phoneBook[friends].firstName;
    cout << "Enter Last Name" << endl;
    cin >> phoneBook[friends].lastName;
    while(!isValidPhoneNumber) {
        cout << "Please enter the Phone Number in the format '1234567890' " << endl;
        cin >> phoneNum; //phoneBook[friends].phoneNumber;

        if (phoneNum > 999999999 && phoneNum < 10000000000) {
            phoneBook[friends].phoneNumber = phoneNum;
            isValidPhoneNumber = true;
        } else {
            cin.fail();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "set number failed " << endl;
        }
    };

    while(!isValidPhoneType) {
        cout << "Enter the Phone Type: 0 - Cell, 1 - Home, 2 - Work" << endl;
        cin >> phone1;
        if (phone1 >= 0 && phone1 <= 2) {
            phoneBook[friends].phoneType = static_cast <PhoneType>(phone1);
            isValidPhoneType = true;
        } if(phone1 <= -1 || phone1 >= 3) {
            cin.fail();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a valid phone type " << endl;
        }
    }
    friends++;

    bubbleSort(phoneBook, friends);
}


void bubbleSort(Contact phoneBook[], int &friends)
{
    bool swap;
    Contact temp;

    do{
        swap = false;
        for(int count = 0; count < (friends - 1); count++){
            string x = toLower(phoneBook[count].lastName);
            string y = toLower(phoneBook[count +1].lastName);

            int z = x.compare(y);

            if(z > 0){
                temp = phoneBook[count];
                phoneBook[count]  =  phoneBook[count+1];
                phoneBook[count+1] = temp;
                swap = true;

            }
        }
    }while(swap);

}


int binarySearch(Contact phoneBook[], int &friends, string value){

    bubbleSort(phoneBook, friends);

    int first = 0;
    int last = friends - 1;
    int middle;
    int position = -1;

    bool found = false;

    while(!found && first <= last){
        middle = (first+last)/2;
        if(phoneBook[middle].lastName == value){
            found = true;
            position = middle;
        }
        else if(phoneBook[middle].lastName > value)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return position;
}

void exitFile(fstream& fin, Contact phoneBook[], int &friends){

    fin.open("database.txt", ios::out);

    cout << "Terminate the program" << endl;

    for(int i = 0; i < friends; i++){
        fin << phoneBook[i].firstName << "~";
        fin << phoneBook[i].lastName << "~";
        fin << phoneBook[i].phoneNumber << "~";
        fin << phoneBook[i].phoneType << endl;
    }
    fin.close();

}
/*void deleteContact(Contact phoneBook[], int &friends){

    string deleteName;
    Contact temp;


    cout << "Enter the Last Name to delete a contact" << endl;
    cin >> deleteName;

    int element = binarySearch(phoneBook, friends, deleteName);
    if(element + 1 != friends) {

        for (int i = element; i < friends - 1; i++) {
            temp = phoneBook[i + 1];
            phoneBook[i] = temp;
            if(i + 1== friends-1)
                phoneBook[i] = 0;



*/

void deleteContact(Contact phoneBook[], int &friends){

    string deleteName;
    Contact temp;

    cout << "Enter the Last Name to delete a contact" << endl;
    cin >> deleteName;

    int element = binarySearch(phoneBook, friends, deleteName);

    if(element + 1 != friends) {

        for (int i = element; i < friends - 1; i++) {
            temp = phoneBook[i + 1];
            phoneBook[i] = temp;
        }
        friends--;
    }
    else
        friends--;

}