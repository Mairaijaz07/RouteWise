
#include "Customer.h"

Customer::Customer(int id, string n, string phone, string addr)
{
    customerID = id;
    name = n;
    phoneNumber = phone;
    address = addr;
}

int Customer::getCustomerID()
{
    return customerID;
}

string Customer::getName()
{
    return name;
}

string Customer::getPhoneNumber()
{
    return phoneNumber;
}

string Customer::getAddress()
{
    return address;
}

void Customer::displayCustomer()
{
    cout << "\nCustomer ID: " << customerID;
    cout << "\nName: " << name;
    cout << "\nPhone Number: " << phoneNumber;
    cout << "\nAddress: " << address << endl;
}
