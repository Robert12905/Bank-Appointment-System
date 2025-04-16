//Project of the group consisting of: Robert, Esmir, Henry, and Alex

//This Project is going to mimic a high-level appointment system using different instances of data-structures and algorithms
// 
// 
// 
//In order to start, we will need to give the user a choice of what to view:
//
//To begin we will need to provide the user an option between SCHEDULED appointments,
// 
// and the option to SCHEDULE appointments themselves
//
//Dates in the form of dd/mm/yyyy, should be used in these provisions
//_________________________________________________________________________________________________________________________________________

#include <iostream>
#include <vector>
#include <string>
#include <map>

//timer libraries:
#include <chrono>
#include <thread>

//_________________________________________________________________________________________________________________________________________


#define TABLESIZE 100

using namespace std;


//_________________________________________________________________________________________________________________________________________

//delay code for switch statements

void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}



//_________________________________________________________________________________________________________________________________________

struct Date {                                                                  // This Structure will hold appointment dates, allowing for users to pick available timeslots on those days
    int day;
    int month;
    int year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool operator == (const Date& other) const {                              //'operator==' is a function which directly compares 2 variables when used
        return year == other.year && month == other.month && day == other.day; // so when a date that is input is directly equal to an already included value -> return true
    }

};

struct Time {                                                                  // This Structure will hold appointment time, allowing for users to input their desired time if available
    int hour;
};

struct Appointment {
    int hour;
    Date date;
    Time time;
    string AppDescription;
};

struct AppointmentNode {                                                       // This Structure will become a node in the linked list assigned alongside 'Client'
    Appointment appt;
    AppointmentNode* next;
};

struct Client {                                                                // This Structure will become the head nodes assigned alongside the AppointmentNode(s)
    string name;
    string PhoneNumber;
    AppointmentNode* head = nullptr;
};
//_________________________________________________________________________________________________________________________________________

class AppointmentSystem {
private: vector<Client> clients;

public:

    void addAppointment() {

    }

    void viewAppointments() {

    }

    void viewSortedClients() {

    }

    void searchClients() {

    }

};

//_________________________________________________________________________________________________________________________________________
//This code is our saved HASH assignment:

//creating a hash function that will take the input of a name/phone number and accordingly hash it with a key
//into a functioning table//

//--Design a class to store and retrieve phone numbers by names--//

//Open Addressing--//
//In open addressing, all elements are stored in the hash table itself. Each table entry contains either a
//record or NIL. When searching for an element, we examine the table slots one by one until the desired element is
//found or it is clear that the element is not in the table.

//struct PhoneNumber holds our record--
//that being a name and associated number


struct PhoneNumber {                                                           // This structure holds name, age, and a user-input phone number, 
    // Good use in an overall client list
    string name;
    int age;
    string number;
    bool inTable;

    //constructor for our struct
    PhoneNumber(string n, int a, string pn) : name(n), age(a), number(pn), inTable(false) {}
};



//function to find each names ASCII value
int hashFun(const string& key) {                                //named hashFun, because of underlying error with 'hash'
    //ASCII Value Variable
    int ASCII = 0;

    //for EACH character, that character IS the key, ASCII will then continue to add the key's value to our
    //total, being ASCII
    for (char ch : key) {
        ASCII += (int)ch;
    }
    //will return our total ASCII value of the current string
    return ASCII % TABLESIZE;

}

//_________________________________________________________________________________________________________________________________________

class ContactNumber {
private:
    map<string, string > phoneNumbers;
public:

    void addContact(const string& name, const string& phoneBook) {
        phoneNumbers[name] = phoneBook;
    }

    string getPhoneNumber(const string& name) {
        auto it = phoneNumbers.find(name);
        if (it != phoneNumbers.end()) {
            return it->second;
        }
        else {
            return "Contact not found";
        }
    }

    void removeContact(const string& name) {
        phoneNumbers.erase(name);
    }


};

//_________________________________________________________________________________________________________________________________________

//director class which will store phone numbers USING a hash table
//class PhoneDirector {
//private:
//    //OUR HASH TABLE is defined by TABLESIZE
//    PhoneNumber table[TABLESIZE];
//
//public:
//
//    //insertion to hash table function (updates included numbers)
//    void insert(const string& name, const string& number) {
//        //current index value is determined by the current name of hashFun
//        int index = hashFun(name);
//
//        //while the current index value is within the table-
//        while (table[index].inTable) {
//            //if the current name within the index is the same as the current index
//            if (table[index].name == name) {
//                //the current index number will equal the next available number
//                table[index].number = number;
//                return;
//            }
//
//            //index value will then increment by one, and the MODULUS of TABLESIZE with it will then be the next index
//            //value
//            index = (index + 1) % TABLESIZE;
//        }
//        table[index].name = name;
//        table[index].number = number;
//        table[index].inTable = true;
//    }
//
//    //prints the director function
//    void printDirector() {
//        for (int i = 0; i < TABLESIZE; i++) {
//            if (table[i].inTable) {
//                cout << "hash position: " << (i + 1) << ") " << table[i].name << " " << table[i].number << endl;
//            }
//        }
//    }
//};

//_________________________________________________________________________________________________________________________________________

int main() {


    ContactNumber contact;

    int seconds;

    string name, number;

    cout << "Welcome to the Appointment Scheduler and Client Database." << endl << endl;

    while (true) {


        cout << "Please choose from the folloing options:" << endl << endl;
        int selection;

        //Here is what we want the choice between:
        cout << "1) Appointment Menu: " << endl << endl << "2) Client Menu: " << endl << endl << "3) Exit Program: " << endl << endl;

        cin >> selection;

        switch (selection) {

            int choice;

//_________________________________________________________________________________________________________________________________________

                        //---------------------//Case 1: Appointments Tab//---------------------//
        case 1:
            system("cls");

            cout << "Appointments Tab:" << endl << endl;                         //Appointments

            cout << "Please Pick from the following:" << endl;

            cout << "\n1)   Add Appointments by Date:" << endl;                //add appointments (by date)
            cout << "\n2)   Search Appointments by Date: " << endl;            //Search appointments by date
            cout << "\n3)   View All Appointments: " << endl;                  //View all appointments (by date/by name)

            cout << endl;
            cin >> choice;



            int finalOption;

            switch (choice) {

                        //---------------------//Appointment Choices//---------------------//

                switch (finalOption) {

                case 1:
                    //add appointments (by date)

                    break;
                case 2:
                    //search appointments (by date/by name)\

                    break;
                case 3:
                    //view appointments

                    break;
                }


            }

//_________________________________________________________________________________________________________________________________________


                            //---------------------//Case 2: Clients Tab//---------------------//
        case 2:


            system("cls");

            cout << "Clients Tab :" << endl << endl;                           //Clients


            cout << "Please Pick from the following:" << endl;

            cout << "1. Add Contact" << endl;
            cout << "2. Get Number" << endl;
            cout << "3. Remove Contact" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";

            cin >> choice;
            cin.ignore(); // Clear newline from buffer

            cout << endl;

                            //---------------------//Client Choices//---------------------//


                switch (choice) {
                    case 1:
                        cout << "Enter name: ";
                        getline(cin, name);
                        cout << "Enter phone number: ";
                        getline(cin, number);
                        contact.addContact(name, number);
                        cout << "Contact added!" << endl << endl;

                       
                        break;
                    case 2:
                        cout << "Enter name to search: ";
                        getline(cin, name);
                        cout << "Phone Number: " << contact.getPhoneNumber(name) << endl << endl;


                        break;
                    case 3:
                        cout << "Enter name to remove: ";
                        getline(cin, name);
                        contact.removeContact(name);
                        cout << "Contact removed!" << endl << endl;
                        break;

                    case 0:
                        cout << "You have exited the program." << endl;
                        return 0;
                    
                    default:

                        cout << "Invalid Choice. Try Again." << endl << endl;
                        break;
                    }

               // case ?:
                    //alphabetical sort
                    //break;
                }
            }


            return 0;
//_________________________________________________________________________________________________________________________________________
        };
    
