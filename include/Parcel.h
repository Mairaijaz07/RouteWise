
#ifndef PARCEL_H
#define PARCEL_H

#include <iostream>
#include <string>
using namespace std;

class Parcel
{
private:
    string trackingID;
    int customerID;
    string source;
    string destination;
    float weight;
    int priority;
    string deliveryStatus;

public:
    Parcel(string trackID, int custID, string src,
           string dest, float w, int p, string status);

    string getTrackingID();
    int getCustomerID();
    string getSource();
    string getDestination();
    float getWeight();
    int getPriority();
    string getDeliveryStatus();

    void setDeliveryStatus(string status);

    void displayParcel();
};

#endif
