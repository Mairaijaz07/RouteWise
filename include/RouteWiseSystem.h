#ifndef ROUTEWISESYSTEM_H
#define ROUTEWISESYSTEM_H

#include "Customer.h"
#include "Parcel.h"
#include "HashTable.h"
#include "ParcelTrees.h"
#include "DeliveryQueue.h"
#include "UrgentHeap.h"
#include "DeliveryHistory.h"
#include "Graph.h"

class RouteWiseSystem
{
private:
    Customer** customers;
    Parcel** parcels;

    int customerCount;
    int parcelCount;

    int customerCapacity;
    int parcelCapacity;

    HashTable parcelTable;
    ParcelTrees parcelTrees;
    DeliveryQueue normalQueue;
    UrgentHeap urgentHeap;
    DeliveryHistory history;
    Graph cityNetwork;

    void expandCustomerArray();
    void expandParcelArray();

    Customer* findCustomer(int id);
    Parcel* findParcel(string trackingID);

    void registerCustomer();
    void registerParcel();
    void addNormalDeliveryRequest();
    void addUrgentDeliveryRequest();
    void processNextDelivery();
    void markParcelDelivered();
    void registerCity();
    void addRoad();
public:
    RouteWiseSystem();
    ~RouteWiseSystem();
    void run();
};

#endif#pragma once
