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
#include <algorithm>

//timer libraries:
#include <chrono>
#include <thread>

//_________________________________________________________________________________________________________________________________________


#define TABLESIZE 100

using namespace std;

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
                                                 
class AppointmentSystem {
private: vector<Client> clients;

public:

    // Function to add a new appointment for a client
    void addAppointment(ContactNumber& contact) {
        string name, phone, desc;
        int day, month, year, hour;

        // Prompt user for client information and appointment details
        cout << "Enter client's name: ";
        cin.ignore(); // Clears leftover newline in input buffer before getline
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

         // Add contact to the contact book (presumably a phonebook or database)
        contact.addContact(name, phone);

        cout << "Enter the appointment description: ";
        getline(cin, desc);

        cout << "Enter date (dd mm yyyy): ";
        cin >> day >> month >> year;

        cout << "Enter hour (0-23): ";
        cin >> hour;

       // Initialize pointer to check if the client already exists in the system
        Client* clientPtr = nullptr;

        // Search through existing clients for a match by name and phone number
        for (auto& client : clients) {
            if (client.name == name && client.PhoneNumber == phone) {
                clientPtr = &client;  // Found existing client
                break;
            }
        }

        // If no match was found, create a new client and add them to the list
        if (!clientPtr) {
            Client newClient;
            newClient.name = name;
            newClient.PhoneNumber = phone;
            clients.push_back(newClient); // Add new client to the vector
            // Point clientPtr to the newly added client (which is now at the end)
            clientPtr = &clients.back();

        }

        // Create a new node for the client's appointment linked list
        AppointmentNode* newNode = new AppointmentNode{
            {hour, Date(day, month, year), {hour}, desc}, // Initialize appointment details
            nullptr // Set next to nullptr, as it's going to be last
        };
        newNode->appt.date = Date(day, month, year); // Set date
        newNode->appt.time.hour = hour;              // Set hour
        newNode->appt.AppDescription = desc;         // Set description
        newNode->next = nullptr;                     // No next yet

        // Check if this is the client's first appointment and insert a new appointment node at the end of the client's linked list
        if (!clientPtr->head) {
            clientPtr->head = newNode; // // Set new node as head of the list
        }
        else {
            //Otherwise, traverse the list to the last node
            AppointmentNode* temp = clientPtr->head;
            while (temp->next) {
                temp = temp->next; // Traverse to the end
            }
            temp->next = newNode; // Append the new node to the end of the list
        }
    }

    // Function to view all appointments for all clients
    void viewAppointments() {
        // Loop through each client in the list
        for (const Client& client : clients) {
            cout << "Client: " << client.name << " | Phone: " << client.PhoneNumber << endl;
            AppointmentNode* current = client.head;

            // If the client has no appointments yet
            if (!current) {
                cout << "No appointment.\n" << endl;
                continue;
            }

            // Traverse and display all appointments for this client and if the client has no appointments yet
            while (current) {
                const Appointment& appt = current->appt;
                cout << "Appointment: " << appt.AppDescription << endl;
                cout << "Date: " << appt.date.day << "/" << appt.date.month << "/" << appt.date.year << endl;
                cout << "Time: " << appt.time.hour << ":00" << endl;
                cout << " -------------------------------------" << endl;
                current = current->next; // Move to the next appointment
            }
            cout << endl;
        }
    }

    // Function to view all clients sorted alphabetically by name
    void viewSortedClients() {
        // Make a copy of the client's list so we don't alter the original order
        vector<Client> sortedClients = clients;

        // Sort the copied vector alphabetically using a lambda expression
        sort(sortedClients.begin(), sortedClients.end(), [](const Client& a, const Client& b) {
            return a.name < b.name;
            });

        cout << "Sorted Clients: \n\n";

        // Display sorted client list
        for (const Client& client : sortedClients) {
            cout << "Name: " << client.name << " Phone: " << client.PhoneNumber << endl;
        }
        cout << endl;
    }
    void searchClients() {

    }

};

//_________________________________________________________________________________________________________________________________________

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

int main() {

    AppointmentSystem Appsystem;
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

            //_________________________________________________________________________________________________________________________________________

                                    //---------------------//Case 1: Appointments Tab//---------------------//
        case 1:

            int appChoice;

            system("cls");

            cout << "Appointments Tab:" << endl << endl;                         //Appointments

            cout << "Please Pick from the following:" << endl;

            cout << "\n1)   Add Appointments by Date:" << endl;                //add appointments (by date)
            cout << "\n2)   View All Appointments: " << endl;                  //View all appointments (by date/by name)

            cout << endl;
            cin >> appChoice;

            switch (appChoice) {


                    //---------------------//Appointment Choices//---------------------//


            case 1:
                // User chose to add a new appointment
                cout << "Add Appointments." << endl;

                    Appsystem.addAppointment(contact); // Call the method to add appointment using contact info
                    

                    break;

             case 2:
                // User chose to view all appointments
                 cout << "Viewing Appointments." << endl << endl;
                    
                    Appsystem.viewAppointments(); // Call the method to display all appointments

                    break;
                }

            break; // Exit the outer switch after processing appointment operations
            

            //_________________________________________________________________________________________________________________________________________


                                        //---------------------//Case 2: Clients Tab//---------------------//
        case 2:


            system("cls"); // Clear the console screen for a clean Clients tab display

            int clientChoice; // Variable to store the user's selection in the Clients tab
            
            cout << "Clients Tab :" << endl << endl; // Header for the Clients section
            
            cout << "Please Pick from the following:" << endl;
            
            // Display the list of client management options
            cout << "1. Add Contact" << endl;        // Option to add a new contact
            cout << "2. Get Number" << endl;         // Option to retrieve a contact's phone number
            cout << "3. Remove Contact" << endl;     // Option to delete a contact
            cout << "0. Exit" << endl;               // Option to exit the Clients tab
            
            cout << "Enter your choice: ";
            
            cin >> clientChoice; // Get user's choice
            cin.ignore();        // Clear newline from the input buffer to avoid input issues
            
            cout << endl; // Add spacing before the next output

            //---------------------//Client Choices//---------------------//


            switch (clientChoice) {
            case 1:
                // User wants to add a new contact
                cout << "Enter name: ";
                getline(cin, name); // Read full name (including spaces)
                cout << "Enter phone number: ";
                getline(cin, number); // Read full phone number
                contact.addContact(name, number); // Add contact to the contact system
                cout << "Contact added!" << endl << endl; // Confirmation message

                break;
            case 2:
                // User wants to retrieve a phone number
                cout << "Enter name to search: ";
                getline(cin, name); // Get the name of the contact to search
                cout << "Phone Number: " << contact.getPhoneNumber(name) << endl << endl; // Display result

                break;
            case 3:
                // User wants to remove a contact
                cout << "Enter name to remove: ";
                getline(cin, name); // Get the name of the contact to remove
                contact.removeContact(name); // Remove the contact from the system
                cout << "Contact removed!" << endl << endl; // Confirmation message
                
                break;         
            case 4:
                // Optional feature: View all clients sorted alphabetically
                // Uncomment the line below if the Clients vector is available and initialized
                // cout << "number of clients: " << Clients.size() << endl << endl;
                Appsystem.viewSortedClients();

                break;

            case 0:
                // User wants to exit the program
                cout << "You have exited the program." << endl;
                
                return 0; // Exit the program

            default:
                // Handle invalid input
                cout << "Invalid Choice. Try Again." << endl << endl;
                
                break;
            }

            break;

        case 3:

           return 0; // Redundant exit option from a higher-level menu
        }
    }

    return 0;
    //_________________________________________________________________________________________________________________________________________
};
