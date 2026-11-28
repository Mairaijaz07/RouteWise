
#include <iostream>
#include "../include/DeliveryQueue.h"
#include "../include/UrgentHeap.h"

using namespace std;

int main()
{
    Parcel p1("RW101", 1, "Faisalabad", "Lahore", 2.5, 2, "Pending");
    Parcel p2("RW102", 2, "Lahore", "Islamabad", 1.5, 3, "Pending");
    Parcel p3("RW103", 3, "Multan", "Karachi", 3.0, 1, "Pending");
    Parcel p4("RW104", 4, "Faisalabad", "Multan", 2.0, 3, "Pending");

    DeliveryQueue normalQueue;

    UrgentHeap urgentHeap(10);

    normalQueue.enqueue(&p1);
    normalQueue.enqueue(&p3);

    urgentHeap.insert(&p2);
    urgentHeap.insert(&p4);

    cout << "\n========== NORMAL DELIVERIES ==========\n";
    normalQueue.display();

    cout << "\n========== URGENT DELIVERIES ==========\n";
    urgentHeap.display();

    cout << "\n========== PROCESSING NORMAL PARCEL ==========\n";

    Parcel* normalParcel = normalQueue.dequeue();

    if (normalParcel != NULL)
    {
        cout << "Processing parcel: "
            << normalParcel->getTrackingID() << endl;
    }

    cout << "\n========== PROCESSING URGENT PARCEL ==========\n";

    Parcel* urgentParcel = urgentHeap.extractMax();

    if (urgentParcel != NULL)
    {
        cout << "Processing parcel: "
            << urgentParcel->getTrackingID() << endl;
    }

    return 0;
}
