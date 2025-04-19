#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a){
        name=n;
        age=a;
    }

    void displayPersonDetails() {
        cout << "Name: " << name << "\nAge: " << age << endl;
    }
};

class Employee : public Person {
protected:
    int employeeId;
public:
    Employee(string n, int a, int id) : Person(n, a), employeeId(id) {}
void displayEmployeeDetails() {
        displayPersonDetails();
        cout << "Employee ID: " << employeeId << endl;
    }
};

class Manager : public Employee {
private:
    string department;
public:
    Manager(string n, int a, int id, string dept) : Employee(n, a, id), department(dept) {}

    void displayManagerDetails() {
        displayEmployeeDetails();
        cout << "Department: " << department << endl;
    }
};
int main() {
    Manager manager1("Rutvi", 18, 101, "IT");
    Manager manager2("Poojan", 14, 102, "HR");

    manager1.displayManagerDetails();
    cout << endl;
    manager2.displayManagerDetails();

    return 0;
}