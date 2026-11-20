
#include "DeliveryQueue.h"

DeliveryQueue::DeliveryQueue()
{
    front = NULL;
    rear = NULL;
}

DeliveryQueue::~DeliveryQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

bool DeliveryQueue::isEmpty()
{
    return front == NULL;
}

void DeliveryQueue::enqueue(Parcel* parcel)
{
    Node* newNode = new Node;

    newNode->parcel = parcel;
    newNode->next = NULL;

    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Parcel added to normal delivery queue.\n";
}

Parcel* DeliveryQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty!\n";
        return NULL;
    }

    Node* temp = front;

    Parcel* removedParcel = temp->parcel;

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    delete temp;

    return removedParcel;
}

void DeliveryQueue::display()
{
    if (isEmpty())
    {
        cout << "\nNo parcels are currently waiting for normal delivery.\n";
        return;
    }

    Node* temp = front;
    int count = 1;

    cout << "\nNORMAL DELIVERY QUEUE\n";
    cout << "Parcels awaiting dispatch:\n\n";

    while (temp != NULL)
    {
        cout << "Parcel " << count << endl;
        cout << "Tracking ID      : "
            << temp->parcel->getTrackingID() << endl;

        cout << "Priority         : "
            << temp->parcel->getPriority() << endl;

        cout << "Delivery Status  : "
            << temp->parcel->getDeliveryStatus() << endl;

        cout << endl;

        temp = temp->next;
        count++;
    }

    cout << "Total pending parcels: " << count - 1 << endl;
}

