
#ifndef DELIVERYHISTORY_H
#define DELIVERYHISTORY_H

#include "Parcel.h"
#include <iostream>
#include <string>

using namespace std;

class DeliveryHistory
{
private:

    struct HistoryNode
    {
        Parcel* parcel;
        string status;
        HistoryNode* next;
    };

    struct UndoNode
    {
        Parcel* parcel;
        string previousStatus;
        UndoNode* next;
    };

    HistoryNode* head;
    HistoryNode* tail;
    UndoNode* undoTop;

    void addHistoryEntry(Parcel* parcel, string status);

public:

    DeliveryHistory();
    ~DeliveryHistory();

    void recordStatusChange(Parcel* parcel, string newStatus);

    bool undoLastChange();

    void displayHistory();

    bool isUndoEmpty();
};

#endif
