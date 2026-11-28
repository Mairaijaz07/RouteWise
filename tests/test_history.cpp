
#include <iostream>
#include "../include/DeliveryHistory.h"

using namespace std;

int main()
{
    Parcel p1("RW101", 1, "Faisalabad", "Lahore", 2.5, 2, "Pending");

    DeliveryHistory history;

    cout << "Initial Status: "
        << p1.getDeliveryStatus() << endl;

    history.recordStatusChange(&p1, "Processing");

    cout << "\nCurrent Status: "
        << p1.getDeliveryStatus() << endl;

    history.recordStatusChange(&p1, "Delivered");

    cout << "\nCurrent Status: "
        << p1.getDeliveryStatus() << endl;

    cout << "\nDelivery History:\n";
    history.displayHistory();

    cout << "\nUndoing Last Change...\n";
    history.undoLastChange();

    cout << "\nCurrent Status: "
        << p1.getDeliveryStatus() << endl;

    cout << "\nUpdated Delivery History:\n";
    history.displayHistory();

    return 0;
}
