
#ifndef URGENTHEAP_H
#define URGENTHEAP_H

#include "Parcel.h"

class UrgentHeap
{
private:
    struct HeapNode
    {
        Parcel* parcel;
        int arrivalOrder;
    };

    HeapNode* heap;
    int capacity;
    int size;
    int nextArrivalOrder;

    void heapifyUp(int index);
    void heapifyDown(int index);

    bool hasHigherPriority(int first, int second);

public:
    UrgentHeap(int maxCapacity);
    ~UrgentHeap();

    bool isEmpty();
    bool isFull();

    void insert(Parcel* parcel);
    Parcel* extractMax();

    void display();
};

#endif
