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
#include <string>
#define TABLESIZE 100

using namespacestd;

//_________________________________________________________________________________________________________________________________________
















//_________________________________________________________________________________________________________________________________________

struct date {                                                                  // This Structure will hold appointment dates, allowing for users to pick available timeslots on those days
	int day;
	int month;
	int year;

	Date(int d, int m, int y) : day(d), month(m), year(y) {}

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

struct PhoneNumber {                                                           // This structure holds name, age, and a user-input phone number
    string name;
    int age;
    string number;
    bool inTable;

    //constructor for our struct
    PhoneNumber(int n, int a, int pN) : name(n), age(a), number(n), inTable(false) {}
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

//director class which will store phone numbers USING a hash table
class PhoneDirector {
private:
    //OUR HASH TABLE is defined by TABLESIZE
    PhoneNumber table[TABLESIZE];

public:

    //insertion to hash table function (updates included numbers)
    void insert(const string& name, const string& number) {
        //current index value is determined by the current name of hashFun
        int index = hashFun(name);

        //while the current index value is within the table-
        while (table[index].inTable) {
            //if the current name within the index is the same as the current index
            if (table[index].name == name) {
                //the current index number will equal the next available number
                table[index].number = number;
                return;
            }

            //index value will then increment by one, and the MODULUS of TABLESIZE with it will then be the next index
            //value
            index = (index + 1) % TABLESIZE;
        }
        table[index].name = name;
        table[index].number = number;
        table[index].inTable = true;
    }

    //prints the director function
    void printDirector() {
        for (int i = 0; i < TABLESIZE; i++) {
            if (table[i].inTable) {
                cout << "hash position: " << (i + 1) << ") " << table[i].name << " " << table[i].number << endl;
            }
        }
    }
};

//_________________________________________________________________________________________________________________________________________

int main() {


};
