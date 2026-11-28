
#ifndef DELIVERYQUEUE_H
#define DELIVERYQUEUE_H

#include "Parcel.h"

class DeliveryQueue
{
private:
    struct Node
    {
        Parcel* parcel;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    DeliveryQueue();
    ~DeliveryQueue();

    bool isEmpty();
void enqueueFront(Parcel* parcel);
bool remove(Parcel* parcel);
    void enqueue(Parcel* parcel);
    Parcel* dequeue();

    void display();
};

#endif
