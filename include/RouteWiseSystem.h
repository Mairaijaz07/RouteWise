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


enum UndoAction
{
    ADD_NORMAL,
    ADD_URGENT,
    PROCESS_NORMAL,
    PROCESS_URGENT,
    MARK_DELIVERED
};

struct SystemUndoNode
{
    Parcel* parcel;
    UndoAction action;
    int arrivalOrder;
    SystemUndoNode* next;
};

SystemUndoNode* systemUndoTop;

void pushSystemUndo(
    Parcel* parcel,
    UndoAction action,
    int arrivalOrder = -1
);

bool undoLastSystemOperation();

public:
    RouteWiseSystem();
    ~RouteWiseSystem();
    void run();
};

#endif
