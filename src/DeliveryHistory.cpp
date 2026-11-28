
#include "DeliveryHistory.h"

DeliveryHistory::DeliveryHistory()
{
    head = NULL;
    tail = NULL;
    undoTop = NULL;
}

DeliveryHistory::~DeliveryHistory()
{
    HistoryNode* tempHistory;

    while (head != NULL)
    {
        tempHistory = head;
        head = head->next;
        delete tempHistory;
    }

    UndoNode* tempUndo;

    while (undoTop != NULL)
    {
        tempUndo = undoTop;
        undoTop = undoTop->next;
        delete tempUndo;
    }
}

void DeliveryHistory::addHistoryEntry(Parcel* parcel, string status)
{
    HistoryNode* newNode = new HistoryNode;

    newNode->parcel = parcel;
    newNode->status = status;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void DeliveryHistory::recordStatusChange(Parcel* parcel, string newStatus)
{
    if (parcel == NULL)
    {
        return;
    }

    string previousStatus = parcel->getDeliveryStatus();

    if (previousStatus == newStatus)
    {
        cout << "Parcel already has this status.\n";
        return;
    }

    UndoNode* newUndo = new UndoNode;

    newUndo->parcel = parcel;
    newUndo->previousStatus = previousStatus;
    newUndo->next = undoTop;

    undoTop = newUndo;

    parcel->setDeliveryStatus(newStatus);

    addHistoryEntry(parcel, newStatus);

    cout << "Parcel status updated successfully.\n";
}

bool DeliveryHistory::undoLastChange()
{
    if (undoTop == NULL)
    {
        cout << "No operation available to undo.\n";
        return false;
    }

    UndoNode* temp = undoTop;

    Parcel* parcel = temp->parcel;
    string previousStatus = temp->previousStatus;

    undoTop = undoTop->next;

    parcel->setDeliveryStatus(previousStatus);

    addHistoryEntry(parcel, previousStatus);

    delete temp;

    cout << "Last status change undone successfully.\n";

    return true;
}

void DeliveryHistory::displayHistory()
{
    if (head == NULL)
    {
        cout << "\nNo delivery history available.\n";
        return;
    }

    HistoryNode* temp = head;
    int count = 1;

    cout << "\nDELIVERY HISTORY\n\n";

    while (temp != NULL)
    {
        cout << "Record " << count << endl;

        cout << "Tracking ID     : "
            << temp->parcel->getTrackingID() << endl;

        cout << "Status          : "
            << temp->status << endl;

        cout << endl;

        temp = temp->next;
        count++;
    }

    cout << "Total history records: " << count - 1 << endl;
}

bool DeliveryHistory::isUndoEmpty()
{
    return undoTop == NULL;
}
