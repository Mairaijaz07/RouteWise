#include <iostream>
#include "UrgentHeap.h"

using namespace std;

UrgentHeap::UrgentHeap(int maxCapacity)
{
    capacity = maxCapacity;
    size = 0;
    nextArrivalOrder = 1;

    heap = new HeapNode[capacity];
}

UrgentHeap::~UrgentHeap()
{
    delete[] heap;
}

bool UrgentHeap::isEmpty()
{
    return size == 0;
}

bool UrgentHeap::isFull()
{
    return size == capacity;
}

bool UrgentHeap::hasHigherPriority(int first, int second)
{
    if (heap[first].parcel->getPriority() >
        heap[second].parcel->getPriority())
    {
        return true;
    }

    if (heap[first].parcel->getPriority() ==
        heap[second].parcel->getPriority())
    {
        return heap[first].arrivalOrder <
            heap[second].arrivalOrder;
    }

    return false;
}


void UrgentHeap::insert(Parcel* parcel)
{
    insert(parcel, nextArrivalOrder);
}

void UrgentHeap::insert(Parcel* parcel, int arrivalOrder)
{
    if (parcel == NULL || isFull())
    {
        cout << "Urgent delivery heap is full.\n";
        return;
    }

    int index = size;

    heap[index].parcel = parcel;
    heap[index].arrivalOrder = arrivalOrder;

    size++;

    if (arrivalOrder >= nextArrivalOrder)
        nextArrivalOrder = arrivalOrder + 1;

    heapifyUp(index);
}

void UrgentHeap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (hasHigherPriority(index, parent))
        {
            HeapNode temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            index = parent;
        }
        else
        {
            break;
        }
    }
}


void UrgentHeap::heapifyDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int best = index;

        if (left < size && hasHigherPriority(left, best))
            best = left;

        if (right < size && hasHigherPriority(right, best))
            best = right;

        if (best == index)
            break;

        HeapNode temp = heap[index];
        heap[index] = heap[best];
        heap[best] = temp;

        index = best;
    }
}

Parcel* UrgentHeap::extractMax()
{
    int arrivalOrder;
    return extractMax(arrivalOrder);
}

Parcel* UrgentHeap::extractMax(int& arrivalOrder)
{
    if (isEmpty())
    {
        cout << "No urgent parcels are available.\n";
        return NULL;
    }

    Parcel* removedParcel = heap[0].parcel;

    arrivalOrder = heap[0].arrivalOrder;

    heap[0] = heap[size - 1];

    size--;

    if (!isEmpty())
        heapifyDown(0);

    return removedParcel;
}

bool UrgentHeap::remove(Parcel* parcel)
{
    if (parcel == NULL)
        return false;

    int index = -1;

    for (int i = 0; i < size; i++)
    {
        if (heap[i].parcel == parcel)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return false;

    heap[index] = heap[size - 1];
    size--;

    if (index < size)
    {
        if (index > 0 &&
            hasHigherPriority(index, (index - 1) / 2))
        {
            heapifyUp(index);
        }
        else
        {
            heapifyDown(index);
        }
    }

    return true;
}


void UrgentHeap::display()
{
    if (isEmpty())
    {
        cout << "\nNo urgent parcels are waiting for dispatch.\n";
        return;
    }

    cout << "\nURGENT DELIVERY SCHEDULE\n";
    cout << "Parcels arranged by delivery priority:\n\n";

    for (int i = 0; i < size; i++)
    {
        cout << "Parcel " << i + 1 << endl;

        cout << "Tracking ID      : "
            << heap[i].parcel->getTrackingID() << endl;

        cout << "Priority         : "
            << heap[i].parcel->getPriority() << endl;

        cout << "Delivery Status  : "
            << heap[i].parcel->getDeliveryStatus() << endl;

        cout << endl;
    }

    cout << "Total urgent parcels: " << size << endl;
}