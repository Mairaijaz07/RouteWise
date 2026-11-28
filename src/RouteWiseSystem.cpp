#include "RouteWiseSystem.h"
#include <cstdlib>
#include <limits>

// ---------------------------------------------------------------
// File-local helpers (no changes needed in RouteWiseSystem.h)
// ---------------------------------------------------------------

// Maximum number of cities the network can hold
static const int MAX_CITIES = 8;

// Safe integer input.
// Returns false on invalid input and repairs the input stream.
static bool readInt(int& value)
{
    cin >> value;
    if (cin.fail())
    {
        cin.clear();                                          // reset error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard bad input
        return false;
    }
    return true;
}

// Safe float input.
// Returns false on invalid input and repairs the input stream.
static bool readFloat(float& value)
{
    cin >> value;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Reads a full line (including spaces).
// Skips any leftover whitespace/newline from previous input first.
static void readLine(const string& prompt, string& out)
{
    cout << prompt;
    cin >> ws;
    getline(cin, out);
}

// Prints the blue header banner.
// The color is reset (\033[0m) before every newline, so the blue
// background does not stretch across the terminal when it scrolls.
static void printHeader()
{
    const int headerWidth = 40;
    const string title = "ROUTEWISE SYSTEM";
    int leftPadding = (headerWidth - (int)title.length()) / 2;
    int rightPadding = headerWidth - leftPadding - (int)title.length();

    cout << "\n";
    cout << "\033[44;97m" << string(headerWidth, ' ') << "\033[0m\n";
    cout << "\033[44;97m" << string(leftPadding, ' ') << title
         << string(rightPadding, ' ') << "\033[0m\n";
    cout << "\033[44;97m" << string(headerWidth, ' ') << "\033[0m\n";
}

// ---------------------------------------------------------------
// Constructor / Destructor
// ---------------------------------------------------------------

// Initializes the dynamic arrays and the data structures
RouteWiseSystem::RouteWiseSystem()
    : urgentHeap(100), cityNetwork(MAX_CITIES)
{
    customerCapacity = 2;
    parcelCapacity = 2;

    customerCount = 0;
    parcelCount = 0;

    customers = new Customer * [customerCapacity];
    parcels = new Parcel * [parcelCapacity];

    for (int i = 0; i < customerCapacity; i++)
        customers[i] = nullptr;

    for (int i = 0; i < parcelCapacity; i++)
        parcels[i] = nullptr;
}

// Frees all customers and parcels owned by the system
RouteWiseSystem::~RouteWiseSystem()
{
    for (int i = 0; i < customerCount; i++)
        delete customers[i];

    for (int i = 0; i < parcelCount; i++)
        delete parcels[i];

    delete[] customers;
    delete[] parcels;
}
// ---------------------------------------------------------------
// Array expansion
// ---------------------------------------------------------------

// Doubles the capacity of the customer array
void RouteWiseSystem::expandCustomerArray()
{
    int newCapacity = customerCapacity * 2;

    Customer** newArray = new Customer * [newCapacity];

    for (int i = 0; i < customerCount; i++)
        newArray[i] = customers[i];

    for (int i = customerCount; i < newCapacity; i++)
        newArray[i] = nullptr;

    delete[] customers;

    customers = newArray;
    customerCapacity = newCapacity;
}

// Doubles the capacity of the parcel array
void RouteWiseSystem::expandParcelArray()
{
    int newCapacity = parcelCapacity * 2;

    Parcel** newArray = new Parcel * [newCapacity];

    for (int i = 0; i < parcelCount; i++)
        newArray[i] = parcels[i];

    for (int i = parcelCount; i < newCapacity; i++)
        newArray[i] = nullptr;

    delete[] parcels;

    parcels = newArray;
    parcelCapacity = newCapacity;
}

// ---------------------------------------------------------------
// Find functions
// ---------------------------------------------------------------

// Linear search for a customer by ID; returns nullptr if not found
Customer* RouteWiseSystem::findCustomer(int id)
{
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i]->getCustomerID() == id)
        {
            return customers[i];
        }
    }

    return nullptr;
}
// Looks up a parcel by tracking ID using the hash table
Parcel* RouteWiseSystem::findParcel(string trackingID)
{
    return parcelTable.search(trackingID);
}

// ---------------------------------------------------------------
// Customer / Parcel registration
// ---------------------------------------------------------------

// Registers a new customer after validating the input
void RouteWiseSystem::registerCustomer()
{
    int id;
    string name, phone, address;

    cout << "\nEnter Customer ID: ";
    if (!readInt(id) || id <= 0)
    {
        cout << "Invalid Customer ID! Please enter a positive number.\n";
        return;
    }

    if (findCustomer(id) != nullptr)
    {
        cout << "Customer ID already exists!\n";
        return;
    }

    readLine("Enter Customer Name: ", name);
    readLine("Enter Phone Number: ", phone);
    readLine("Enter Address: ", address);

    if (name.empty())
    {
        cout << "Customer name cannot be empty!\n";
        return;
    }

    // Expand the array only when space is actually needed
    if (customerCount == customerCapacity)
    {
        expandCustomerArray();
    }

    customers[customerCount] = new Customer(id, name, phone, address);
    customerCount++;

    cout << "\nCustomer registered successfully!\n";
}

// Registers a new parcel after validating customer, cities, weight and priority
void RouteWiseSystem::registerParcel()
{
    string trackingID, source, destination;
    int customerID, priority;
    float weight;

    cout << "\nEnter Tracking ID: ";
    cin >> trackingID;

    if (findParcel(trackingID) != nullptr)
    {
        cout << "Tracking ID already exists!\n";
        return;
    }

    cout << "Enter Customer ID: ";
    if (!readInt(customerID))
    {
        cout << "Invalid Customer ID!\n";
        return;
    }

    if (findCustomer(customerID) == nullptr)
    {
        cout << "Customer does not exist!\n";
        return;
    }

    readLine("Enter Source City: ", source);
    readLine("Enter Destination City: ", destination);

    // Both cities must already be registered in the city network
    if (cityNetwork.getCityIndex(source) == -1 ||
        cityNetwork.getCityIndex(destination) == -1)
    {
        cout << "Source or destination city is not registered! "
                "Please register the city first (option 18).\n";
        return;
    }
cout << "Enter Weight: ";
    if (!readFloat(weight))
    {
        cout << "Invalid weight!\n";
        return;
    }

    cout << "Enter Priority (1=Low, 2=Normal, 3=High): ";
    if (!readInt(priority))
    {
        cout << "Invalid priority!\n";
        return;
    }

    if (weight <= 0 || priority < 1 || priority > 3)
    {
        cout << "Invalid weight or priority!\n";
        return;
    }

    // Expand the array only after all validation has passed
    if (parcelCount == parcelCapacity)
    {
        expandParcelArray();
    }

    parcels[parcelCount] =
        new Parcel(trackingID, customerID, source,
            destination, weight, priority, "Pending");

    // If hash table insertion fails, clean up the new parcel
    if (!parcelTable.insert(parcels[parcelCount]))
    {
        delete parcels[parcelCount];
        parcels[parcelCount] = nullptr;
        cout << "Parcel registration failed!\n";
        return;
    }

    parcelTrees.insert(parcels[parcelCount]);

    parcelCount++;

    cout << "\nParcel registered successfully!\n";
}

// ---------------------------------------------------------------
// Delivery requests
// ---------------------------------------------------------------

// Adds a pending parcel to the normal delivery queue
void RouteWiseSystem::addNormalDeliveryRequest()
{
    string trackingID;

    cout << "\nEnter Tracking ID: ";
    cin >> trackingID;
 Parcel* parcel = findParcel(trackingID);

    if (parcel == nullptr)
    {
        cout << "Parcel not found!\n";
        return;
    }

    if (parcel->getDeliveryStatus() != "Pending")
    {
        cout << "Parcel is not available for queueing!\n";
        return;
    }

    normalQueue.enqueue(parcel);
    history.recordStatusChange(parcel, "Queued");

    cout << "\nNormal delivery request added successfully!\n";
}

// Adds a high-priority pending parcel to the urgent delivery heap
void RouteWiseSystem::addUrgentDeliveryRequest()
{
    string trackingID;

    cout << "\nEnter Tracking ID: ";
    cin >> trackingID;

    Parcel* parcel = findParcel(trackingID);

    if (parcel == nullptr)
    {
        cout << "Parcel not found!\n";
        return;
    }

    if (parcel->getDeliveryStatus() != "Pending")
    {
        cout << "Parcel is not available for queueing!\n";
        return;
    }

    if (parcel->getPriority() != 3)
    {
        cout << "Only high-priority parcels can enter urgent delivery!\n";
        return;
    }

    if (urgentHeap.isFull())
    {
        cout << "Urgent delivery heap is full!\n";
        return;
    }

    urgentHeap.insert(parcel);
    history.recordStatusChange(parcel, "Queued");

    cout << "\nUrgent delivery request added successfully!\n";
}
// Picks the next parcel to process: urgent heap first, then normal queue
void RouteWiseSystem::processNextDelivery()
{
    Parcel* parcel = nullptr;

    if (!urgentHeap.isEmpty())
    {
        parcel = urgentHeap.extractMax();
    }
    else if (!normalQueue.isEmpty())
    {
        parcel = normalQueue.dequeue();
    }
    else
    {
        cout << "\nNo pending deliveries available!\n";
        return;
    }

    history.recordStatusChange(parcel, "Processing");

    cout << "\nDelivery selected for processing!\n";
    parcel->displayParcel();
}

// Marks a parcel that is currently processing as delivered
void RouteWiseSystem::markParcelDelivered()
{
    string trackingID;

    cout << "\nEnter Tracking ID: ";
    cin >> trackingID;

    Parcel* parcel = findParcel(trackingID);

    if (parcel == nullptr)
    {
        cout << "\nParcel not found!\n";
        return;
    }

    if (parcel->getDeliveryStatus() != "Processing")
    {
        cout << "\nParcel is not currently processing!\n";
        return;
    }

    history.recordStatusChange(parcel, "Delivered");
cout << "\nParcel marked as delivered successfully!\n";
}

// ---------------------------------------------------------------
// City network
// ---------------------------------------------------------------

// Registers a new city in the network
void RouteWiseSystem::registerCity()
{
    string city;

    if (cityNetwork.getVertices() >= MAX_CITIES)
    {
        cout << "\nCity limit (" << MAX_CITIES << ") has been reached!\n";
        return;
    }

    readLine("\nEnter City Name: ", city);

    if (city.empty())
    {
        cout << "City name cannot be empty!\n";
        return;
    }

    if (cityNetwork.getCityIndex(city) != -1)
    {
        cout << "City is already registered!\n";
        return;
    }

    cityNetwork.addCity(city);
}

// Adds a road (weighted edge) between two registered cities
void RouteWiseSystem::addRoad()
{
    string source, destination;
    int weight;

    if (cityNetwork.getVertices() < 2)
    {
        cout << "\nAt least two cities are required to add a road!\n";
        return;
    }

    cityNetwork.displayCities();

    readLine("\nEnter Source City: ", source);
    readLine("Enter Destination City: ", destination);

    int sourceIndex = cityNetwork.getCityIndex(source);
    int destinationIndex = cityNetwork.getCityIndex(destination);

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        cout << "One or both cities do not exist!\n";
        return;
    }

    if (sourceIndex == destinationIndex)
    {
        cout << "Source and destination cannot be the same!\n";
        return;
    }
     cout << "Enter Road Distance (km): ";
    if (!readInt(weight) || weight <= 0)
    {
        cout << "Invalid distance! Please enter a positive number.\n";
        return;
    }

    cityNetwork.addEdge(sourceIndex, destinationIndex, weight);
}

// ---------------------------------------------------------------
// Main menu loop
// ---------------------------------------------------------------
void RouteWiseSystem::run()
{
    int choice = 0;

    // Enables ANSI escape codes on Windows (harmless on other systems)
    system("");

    do
    {
        printHeader();

        cout << "1. Register Customer\n";
        cout << "2. Register Parcel\n";
        cout << "3. Search Parcel\n";
        cout << "4. Add Normal Delivery Request\n";
        cout << "5. Add Urgent Delivery Request\n";
        cout << "6. Process Next Delivery\n";
        cout << "7. Mark Parcel as Delivered\n";
        cout << "8. Undo Last Operation\n";
        cout << "9. Display Pending Deliveries\n";
        cout << "10. Display Parcel Records\n";
        cout << "11. Display City Network\n";
        cout << "12. BFS Network Traversal\n";
        cout << "13. DFS Network Traversal\n";
        cout << "14. Find Shortest Delivery Route\n";
        cout << "15. Generate Minimum Delivery Network\n";
        cout << "16. Compare BST and AVL Performance\n";
        cout << "17. Display System Statistics\n";
        cout << "18. Register City\n";
        cout << "19. Add Road Between Cities\n";
        cout << "20. Exit\n";

        cout << "\nEnter your choice: ";

        // Handle non-numeric menu input without looping forever
        if (!readInt(choice))
        {
            cout << "\nInvalid input! Please enter a number.\n";
            choice = 0;
            continue;
        }

        switch (choice)
        { case 1:
            registerCustomer();
            break;

        case 2:
            registerParcel();
            break;

        case 3:
        {
            // Search a parcel by tracking ID
            string trackingID;

            cout << "\nEnter Tracking ID: ";
            cin >> trackingID;

            Parcel* parcel = findParcel(trackingID);

            if (parcel != nullptr)
            {
                cout << "\nParcel Found!\n";
                parcel->displayParcel();
            }
            else
            {
                cout << "\nParcel not found!\n";
            }

            break;
        }

        case 4:
            addNormalDeliveryRequest();
            break;

        case 5:
            addUrgentDeliveryRequest();
            break;

        case 6:
            processNextDelivery();
            break;

        case 7:
            markParcelDelivered();
            break;

        case 8:
            // Undo the last parcel status change
            if (history.isUndoEmpty())
            {
                cout << "\nNothing to undo!\n";
            }
            else
            {
                cout << endl;
                history.undoLastChange();
            }
            break;

        case 9:
            cout << "\n========== NORMAL DELIVERIES ==========\n";
            normalQueue.display();

            cout << "\n========== URGENT DELIVERIES ==========\n";
            urgentHeap.display();
            break;

        case 10:
            parcelTable.display();
            break;

        case 11:
            cityNetwork.displayCities();
            cityNetwork.displayMatrix();
            cityNetwork.displayList();
            break;
 case 12:
        {
            // Breadth-first traversal from a chosen city
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }

            string startCity;

            cityNetwork.displayCities();
            readLine("\nEnter starting city: ", startCity);

            int start = cityNetwork.getCityIndex(startCity);

            if (start == -1)
                cout << "City not found!\n";
            else
                cityNetwork.BFS(start);

            break;
        }

        case 13:
        {
            // Depth-first traversal from a chosen city
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }

            string startCity;

            cityNetwork.displayCities();
            readLine("\nEnter starting city: ", startCity);

            int start = cityNetwork.getCityIndex(startCity);

            if (start == -1)
                cout << "City not found!\n";
            else
                cityNetwork.DFS(start);

            break;
        }

        case 14:
        {
            // Shortest route between two cities (Dijkstra)
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }

            string sourceCity, destinationCity;

            cityNetwork.displayCities();
            readLine("\nEnter Source City: ", sourceCity);
            readLine("Enter Destination City: ", destinationCity);

            int source = cityNetwork.getCityIndex(sourceCity);
            int destination = cityNetwork.getCityIndex(destinationCity);

            if (source == -1 || destination == -1)
                cout << "One or both cities not found!\n";
            else
                cityNetwork.dijkstra(source, destination);

            break;
        }

        case 15:
            // Minimum delivery network (Prim's MST)
            if (cityNetwork.getVertices() == 0)
                cout << "\nNo cities registered yet!\n";
            else
                cityNetwork.primMST();
            break;

        case 16:
            parcelTrees.compareHeights();
            break;

        case 17:
            cout << "\n========== SYSTEM STATISTICS ==========\n";
            cout << "Total Registered Customers: " << customerCount << endl;
            cout << "Total Registered Parcels: " << parcelCount << endl;

            cout << "Normal Queue: ";
            if (normalQueue.isEmpty())
                cout << "Empty\n";
            else
            cout << "Contains pending deliveries\n";

            cout << "Urgent Heap: ";
            if (urgentHeap.isEmpty())
                cout << "Empty\n";
            else
                cout << "Contains urgent deliveries\n";

            break;

        case 18:
            registerCity();
            break;

        case 19:
            addRoad();
            break;

        case 20:
            cout << "\nExiting RouteWise System...\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 20);
}