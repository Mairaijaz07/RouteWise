#include "ParcelTrees.h"

// Constructor
ParcelTrees::ParcelTrees()
{
    bstRoot = nullptr;
    avlRoot = nullptr;
}

// Insert into both trees
void ParcelTrees::insert(Parcel* parcel)
{
    if (parcel == nullptr)
    {
        return;
    }

    string trackingID = parcel->getTrackingID();

    // Avoid duplicate tracking IDs
    if (searchBST(trackingID) != nullptr)
    {
        cout << "Parcel already exists in Trees!" << endl;
        return;
    }

    bstRoot = insertBST(bstRoot, parcel);
    avlRoot = insertAVL(avlRoot, parcel);
}


// ================= BST FUNCTIONS =================
int ParcelTrees::getBSTHeight(BSTNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int leftHeight = getBSTHeight(root->left);
    int rightHeight = getBSTHeight(root->right);

    return 1 + maxValue(leftHeight, rightHeight);
}
// Insert into BST
ParcelTrees::BSTNode* ParcelTrees::insertBST(
    BSTNode* root, Parcel* parcel)
{
    if (root == nullptr)
    {
        return new BSTNode(parcel);
    }

    string newID = parcel->getTrackingID();
    string currentID = root->parcel->getTrackingID();

    if (newID < currentID)
    {
        root->left = insertBST(root->left, parcel);
    }
    else if (newID > currentID)
    {
        root->right = insertBST(root->right, parcel);
    }

    return root;
}

// Search in BST
ParcelTrees::BSTNode* ParcelTrees::searchBSTNode(
    BSTNode* root, string trackingID)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    string currentID = root->parcel->getTrackingID();

    if (trackingID == currentID)
    {
        return root;
    }

    if (trackingID < currentID)
    {
        return searchBSTNode(root->left, trackingID);
    }

    return searchBSTNode(root->right, trackingID);
}

// Public BST search
Parcel* ParcelTrees::searchBST(string trackingID)
{
    BSTNode* result = searchBSTNode(bstRoot, trackingID);

    if (result != nullptr)
    {
        return result->parcel;
    }

    return nullptr;
}

// In-order traversal of BST
void ParcelTrees::displayBSTInOrder(BSTNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    displayBSTInOrder(root->left);
    root->parcel->displayParcel();
    displayBSTInOrder(root->right);
}

// Display BST
void ParcelTrees::displayBST()
{
    cout << "\n===== BST PARCEL RECORDS =====\n";

    if (bstRoot == nullptr)
    {
        cout << "BST is empty." << endl;
        return;
    }

    displayBSTInOrder(bstRoot);
}


// ================= AVL FUNCTIONS =================

// Get height
int ParcelTrees::getHeight(AVLNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return node->height;
}

// Get maximum value
int ParcelTrees::maxValue(int a, int b)
{
    return (a > b) ? a : b;
}

// Calculate balance factor
int ParcelTrees::getBalanceFactor(AVLNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

// Right Rotation
ParcelTrees::AVLNode* ParcelTrees::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxValue(
        getHeight(y->left),
        getHeight(y->right)
    );

    x->height = 1 + maxValue(
        getHeight(x->left),
        getHeight(x->right)
    );

    return x;
}

// Left Rotation
ParcelTrees::AVLNode* ParcelTrees::rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxValue(
        getHeight(x->left),
        getHeight(x->right)
    );

    y->height = 1 + maxValue(
        getHeight(y->left),
        getHeight(y->right)
    );

    return y;
}

// Insert into AVL
ParcelTrees::AVLNode* ParcelTrees::insertAVL(
    AVLNode* root, Parcel* parcel)
{
    if (root == nullptr)
    {
        return new AVLNode(parcel);
    }

    string newID = parcel->getTrackingID();
    string currentID = root->parcel->getTrackingID();

    if (newID < currentID)
    {
        root->left = insertAVL(root->left, parcel);
    }
    else if (newID > currentID)
    {
        root->right = insertAVL(root->right, parcel);
    }
    else
    {
        return root;
    }

    // Update height
    root->height = 1 + maxValue(
        getHeight(root->left),
        getHeight(root->right)
    );

    // Calculate balance factor
    int balance = getBalanceFactor(root);

    // LL Case
    if (balance > 1 &&
        newID < root->left->parcel->getTrackingID())
    {
        return rotateRight(root);
    }

    // RR Case
    if (balance < -1 &&
        newID > root->right->parcel->getTrackingID())
    {
        return rotateLeft(root);
    }

    // LR Case
    if (balance > 1 &&
        newID > root->left->parcel->getTrackingID())
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL Case
    if (balance < -1 &&
        newID < root->right->parcel->getTrackingID())
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Search in AVL
ParcelTrees::AVLNode* ParcelTrees::searchAVLNode(
    AVLNode* root, string trackingID)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    string currentID = root->parcel->getTrackingID();

    if (trackingID == currentID)
    {
        return root;
    }

    if (trackingID < currentID)
    {
        return searchAVLNode(root->left, trackingID);
    }

    return searchAVLNode(root->right, trackingID);
}

// Public AVL search
Parcel* ParcelTrees::searchAVL(string trackingID)
{
    AVLNode* result = searchAVLNode(avlRoot, trackingID);

    if (result != nullptr)
    {
        return result->parcel;
    }

    return nullptr;
}

// In-order traversal of AVL
void ParcelTrees::displayAVLInOrder(AVLNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    displayAVLInOrder(root->left);
    root->parcel->displayParcel();
    displayAVLInOrder(root->right);
}

// Display AVL
void ParcelTrees::displayAVL()
{
    cout << "\n===== AVL PARCEL RECORDS =====\n";

    if (avlRoot == nullptr)
    {
        cout << "AVL Tree is empty." << endl;
        return;
    }

    displayAVLInOrder(avlRoot);
}


// ================= MEMORY MANAGEMENT =================

// Delete BST nodes
void ParcelTrees::deleteBST(BSTNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteBST(root->left);
    deleteBST(root->right);

    delete root;
}

// Delete AVL nodes
void ParcelTrees::deleteAVL(AVLNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteAVL(root->left);
    deleteAVL(root->right);

    delete root;
}
void ParcelTrees::compareHeights()
{
    int bstHeight = getBSTHeight(bstRoot);
    int avlHeight = getHeight(avlRoot);

    cout << "\nBST VS AVL HEIGHT COMPARISON\n\n";

    cout << "BST Height: " << bstHeight << endl;
    cout << "AVL Height: " << avlHeight << endl;

    if (bstHeight > avlHeight)
    {
        cout << "AVL Tree has a smaller height.\n";
    }
    else if (avlHeight > bstHeight)
    {
        cout << "BST has a smaller height.\n";
    }
    else
    {
        cout << "Both trees have equal heights.\n";
    }
}
// Destructor
ParcelTrees::~ParcelTrees()
{
    deleteBST(bstRoot);
    deleteAVL(avlRoot);
}