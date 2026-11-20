#include "Parcel.h"

Parcel::Parcel(string trackID, int custID, string src,
               string dest, float w, int p, string status)
{
    trackingID = trackID;
    customerID = custID;
    source = src;
    destination = dest;
    weight = w;
    priority = p;
    deliveryStatus = status;
}

string Parcel::getTrackingID()
{
    return trackingID;
}

int Parcel::getCustomerID()
{
    return customerID;
}

string Parcel::getSource()
{
    return source;
}

string Parcel::getDestination()
{
    return destination;
}

float Parcel::getWeight()
{
    return weight;
}

int Parcel::getPriority()
{
    return priority;
}

string Parcel::getDeliveryStatus()
{
    return deliveryStatus;
}

void Parcel::setDeliveryStatus(string status)
{
    deliveryStatus = status;
}

void Parcel::displayParcel()
{
    cout << "\nTracking ID: " << trackingID;
    cout << "\nCustomer ID: " << customerID;
    cout << "\nSource: " << source;
    cout << "\nDestination: " << destination;
    cout << "\nWeight: " << weight << " kg";
    cout << "\nPriority: " << priority;
    cout << "\nDelivery Status: " << deliveryStatus << endl;
}