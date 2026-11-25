
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    int customerID;
    string name;
    string phoneNumber;
    string address;

public:
    Customer(int id, string n, string phone, string addr);

    int getCustomerID();
    string getName();
    string getPhoneNumber();
    string getAddress();

    void displayCustomer();
};

#endif

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    int customerID;
    string name;
    string phoneNumber;
    string address;

public:
    Customer(int id, string n, string phone, string addr);

    int getCustomerID();
    string getName();
    string getPhoneNumber();
    string getAddress();

    void displayCustomer();
};

#endif
