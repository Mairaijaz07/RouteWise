#include "HashTable.h"

HashTable::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i].parcel = nullptr;
        table[i].status = 0;
    }
}

// Hash function
int HashTable::hashFunction(string trackingID)
{
    int sum = 0;

    for (int i = 0; i < trackingID.length(); i++)
    {
        sum = sum + trackingID[i];
    }

    return sum % TABLE_SIZE;
}

// Insert Parcel pointer
bool HashTable::insert(Parcel* parcel)
{
    if (parcel == nullptr)
    {
        return false;
    }

    string trackingID = parcel->getTrackingID();

    int index = hashFunction(trackingID);
    int firstDeleted = -1;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int current = (index + i) % TABLE_SIZE;

        if (table[current].status == 1)
        {
            if (table[current].parcel->getTrackingID() == trackingID)
            {
                cout << "Duplicate Tracking ID!" << endl;
                return false;
            }
        }
        else if (table[current].status == 2)
        {
            if (firstDeleted == -1)
            {
                firstDeleted = current;
            }
        }
        else if (table[current].status == 0)
        {
            if (firstDeleted != -1)
            {
                current = firstDeleted;
            }

            table[current].parcel = parcel;
            table[current].status = 1;

            return true;
        }
    }

    if (firstDeleted != -1)
    {
        table[firstDeleted].parcel = parcel;
        table[firstDeleted].status = 1;

        return true;
    }

    cout << "HashTable is full!" << endl;
    return false;
}

// Search Parcel
Parcel* HashTable::search(string trackingID)
{
    int index = hashFunction(trackingID);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int current = (index + i) % TABLE_SIZE;

        if (table[current].status == 0)
        {
            return nullptr;
        }

        if (table[current].status == 1)
        {
            if (table[current].parcel->getTrackingID() == trackingID)
            {
                return table[current].parcel;
            }
        }
    }

    return nullptr;
}

// Remove Parcel reference
bool HashTable::remove(string trackingID)
{
    int index = hashFunction(trackingID);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int current = (index + i) % TABLE_SIZE;

        if (table[current].status == 0)
        {
            return false;
        }

        if (table[current].status == 1)
        {
            if (table[current].parcel->getTrackingID() == trackingID)
            {
                table[current].parcel = nullptr;
                table[current].status = 2;

                return true;
            }
        }
    }

    return false;
}

// Display all stored Parcels
void HashTable::display()
{
    bool found = false;

    cout << "\n===== HASH TABLE RECORDS =====\n";

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i].status == 1)
        {
            table[i].parcel->displayParcel();
            found = true;
        }
    }

    if (!found)
    {
        cout << "HashTable is empty." << endl;
    }
}