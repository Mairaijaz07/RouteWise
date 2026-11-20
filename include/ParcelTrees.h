#ifndef PARCELTREES_H
#define PARCELTREES_H

#include <iostream>
#include "Parcel.h"
using namespace std;

class ParcelTrees
{
private:

    // BST Node
    struct BSTNode
    {
        Parcel* parcel;
        BSTNode* left;
        BSTNode* right;

        BSTNode(Parcel* p)
        {
            parcel = p;
            left = nullptr;
            right = nullptr;
        }
    };

    // AVL Node
    struct AVLNode
    {
        Parcel* parcel;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(Parcel* p)
        {
            parcel = p;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    BSTNode* bstRoot;
    AVLNode* avlRoot;

    // BST Functions
    BSTNode* insertBST(BSTNode* root, Parcel* parcel);
    BSTNode* searchBSTNode(BSTNode* root, string trackingID);
    void displayBSTInOrder(BSTNode* root);
    void deleteBST(BSTNode* root);

    // AVL Functions
    AVLNode* insertAVL(AVLNode* root, Parcel* parcel);
    AVLNode* searchAVLNode(AVLNode* root, string trackingID);

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    int maxValue(int a, int b);

    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);

    void displayAVLInOrder(AVLNode* root);
    void deleteAVL(AVLNode* root);

public:

    ParcelTrees();

    void insert(Parcel* parcel);

    Parcel* searchBST(string trackingID);
    Parcel* searchAVL(string trackingID);

    void displayBST();
    void displayAVL();

    ~ParcelTrees();
};

#endif