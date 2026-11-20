#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Parcel.h"
using namespace std;

class HashTable
{
private:
    static const int TABLE_SIZE = 101;

    struct Entry
    {
        Parcel* parcel;
        int status;
        // 0 = Empty
        // 1 = Occupied
        // 2 = Deleted
    };

    Entry table[TABLE_SIZE];

    int hashFunction(string trackingID);

public:
    HashTable();

    bool insert(Parcel* parcel);
    Parcel* search(string trackingID);
    bool remove(string trackingID);
    void display();
};

#endif