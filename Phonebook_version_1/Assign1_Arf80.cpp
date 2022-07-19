#include <iostream>
#include<fstream>
#include<string>

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

void displayList(Contact phoneBook[], int &friends);
void enterContact(Contact phoneBook[], int &friends);

int main() {

    string decoy1;
    int decoy2;

    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("database.txt");


    Contact phoneBook[20];

    if (!inputFile) {
        cout << "File did not open." << endl;

        exit(1);
    }

    int friends = 0;

    while (!inputFile.eof()) {
        getline(inputFile, phoneBook[friends].firstName, '~');
        getline(inputFile, phoneBook[friends].lastName, '~');
        getline(inputFile, decoy1, '~');
        phoneBook[friends].phoneNumber = stol(decoy1);
        getline(inputFile, decoy1);
        decoy2 = stoi(decoy1);
        phoneBook[friends].phoneType = static_cast <PhoneType>(decoy2);
        friends++;
    }

int choice;
    bool menuLoop = true;

    while (menuLoop) {
        cout << "1. Display list of all contacts." << endl;
        cout << "2. Add	a new contact." << endl;
        cout << "3. Search for a contact given the contact’s first or last name or part ";
        cout << "of the contact’s first or last name." << endl;
        cout << "4. Delete a contact." << endl;
        cout << "5. Exit program." << endl;

        cout << "Enter a choice" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                displayList(phoneBook, friends);
                break;
            case 2:
                enterContact(phoneBook, friends);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                cout << "Terminate the program" << endl;
                return 0;
            default:
                cout << "Input Invalid: Pick a number 1 - 5 " << endl;
        }
    }
}


void displayList(Contact phoneBook[], int &friends){

  for(int i = 0; i < friends; i++){
        string splitstring = to_string(phoneBook[i].phoneNumber);
        string part1(splitstring, 0, 3);
        string part2(splitstring, 3, 3);
        string part3(splitstring, 6, 4);
        string part4;

        if(phoneBook[i].phoneType == HOME){
            part4 = "HOME";
        }
        if(phoneBook[i].phoneType == CELL){
            part4 = "CELL";
        }
        if(phoneBook[i].phoneType == WORK){
            part4 = "WORK";
        }

        cout << phoneBook[i].firstName << " " << phoneBook[i].lastName << ", " << part4;
        cout << ", (" << part1 << ")" << part2 << "-" << part3 << endl;
    }
cout << endl;
}

void enterContact(Contact phoneBook[], int &friends){

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


}
/*

void searchContact(ifstream inputFile , struct Contact phoneBook[], int friends){

    string searchName;

    cout << "Enter the first or last name of a contact you would like to search for : " << endl;
    cin >> searchName;

    int index = 0;
    int position = -1;
    bool found = false;

    while(index < friends && !found){
        if (phoneBook[index].firstName == searchName){
            found = true;
            position = index;
        }
        if(phoneBook[index].lastName == searchName){
            found = true;
            position = index;
        }
        index++;
    }
}



void deleteContact(ifstream inputFile , struct Contact phoneBook[], int friends){

    string searcher;
    string searcher2;
    char choice;
    char choice2;
    char choice3;
    char choice4;

    cout << "Enter the first or last name of the contact you would like to delete: " << endl;
    cin >> choice;

    switch (choice){
        case 'L':
            cout << "Enter the Last name of the contact:" << endl;
            cin >> searcher;
            for(int x = 0; x < friends; x++){
                if (searcher == phoneBook[x].lastName){

                    cout << "Are you sure you want to delete the contact?" << endl;
                    cin >> choice;
                    switch(choice2){
                        case 'y':
                            if(x < friends) {
                                for (int j = x; j < friends; j++) {
                                    phoneBook[j].lastName = phoneBook[j + 1];
                                }
                            }
                        else{

                        }

                        friends--;
                        break;
                        case 'n':
                        cout << "Contact not deleted" << endl;
                        break;
                    }

                }

            }

        case 'F':
            cout << "Enter the first name of the contact:";
            cin >> searcher2;
            for(int x = 0; x < friends; x++){
                if (searcher2 == phoneBook[x].firstName){

                    cout << "Are you sure you want to delete the contact?" << endl;
                    cin >> choice3;
                    switch(choice4){
                        case 'y':
                            if(x < friends) {
                                for (int j = x; j < friends; j++) {
                                    phoneBook[j].firstName = phoneBook[j + 1];
                                }
                            }
                            else{

                            }

                            friends--;
                            break;
                        case 'n':
                            cout << "Contact not deleted" << endl;
                            break;
                    }

                }

            }
    }



}

*/
/*
 * for(int i = 0; i < arraySize; i++){
 * if (magToFind == earthquake[i]
 * return i;
 *
 * }
 * return -1;
 *switch (choice) {
case 1:
displayList(phoneBook, friends);
break;
case 2:
enterContact(inputFile, phoneBook, friends);
break;
case 3:
searchContact(inputFile, phoneBook, friends);
break;
case 4:
deleteContact(inputFile, phoneBook, friends);
break;
case 5:
cout << "Terminate the program" << endl;
return 0;
default:
cout << "Input Invalid: Pick a number 1 - 5 " << endl;



*/