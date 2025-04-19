#include <iostream>
#include <string>
using namespace std;

class BankCustomer {
private:
    string firstName;
    string lastName;

public:
    // Constructor
    BankCustomer(string fName, string lName) {
        firstName = fName;
        lastName = lName;
    }

    // Friend function declaration
    friend void processCustomer(BankCustomer &c1, BankCustomer &c2);
};

// Friend function definition
void processCustomer(BankCustomer &c1, BankCustomer &c2) {
    // Assigning and Concatenating
    string fullName = c1.firstName + " " + c1.lastName;
    cout << "Full Name: " << fullName << endl;

    // Comparing
    if (c1.firstName == c2.firstName)
        cout << "Customers have the same first name.\n";
    else
        cout << "Customers have different first names.\n";

    // Swapping names
    cout << "Swapping names...\n";
    c1.firstName.swap(c2.firstName);
    cout << "After Swap - Customer 1: " << c1.firstName << ", Customer 2: " << c2.firstName << endl;

    // Extracting substring (first three letters of first name)
    string idPrefix = c1.firstName.substr(0, 3);
    cout << "Customer 1 ID Prefix: " << idPrefix << endl;
}

int main() {
    // Creating customer objects
    BankCustomer cust1("Rahul", "Sharma");
    BankCustomer cust2("Amit", "Verma");

    // Processing customer operations
    processCustomer(cust1, cust2);

    return 0;
}