#include "RouteWiseSystem.h"

RouteWiseSystem::RouteWiseSystem()
    : urgentHeap(100), cityNetwork(8)
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

RouteWiseSystem::~RouteWiseSystem()
{
    for (int i = 0; i < customerCount; i++)
        delete customers[i];

    for (int i = 0; i < parcelCount; i++)
        delete parcels[i];

    delete[] customers;
    delete[] parcels;
}
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
void RouteWiseSystem::registerCity()
{
    string city;

    cin.ignore();

    cout << "\nEnter City Name: ";
    getline(cin, city);

    if (city.empty())
    {
        cout << "City name cannot be empty!\n";
        return;
    }

    cityNetwork.addCity(city);
}
void RouteWiseSystem::addRoad()
{
    string source, destination;
    int weight;

    cin.ignore();

    cityNetwork.displayCities();

    cout << "\nEnter Source City: ";
    getline(cin, source);

    cout << "Enter Destination City: ";
    getline(cin, destination);

    int sourceIndex = cityNetwork.getCityIndex(source);
    int destinationIndex = cityNetwork.getCityIndex(destination);

    if (sourceIndex == -1 || destinationIndex == -1)
    {
        cout << "One or both cities do not exist!\n";
        return;
    }

    cout << "Enter Road Distance (km): ";
    cin >> weight;

    cityNetwork.addEdge(sourceIndex, destinationIndex, weight);
}
void RouteWiseSystem::run()
{
    int choice;

    do
    {
        cout << "\n";
        cout << "\033[44;97m";
        cout << "                                      \n";
        cout << "          ROUTEWISE SYSTEM            \n";
        cout << "                                      \n";
        cout << "\033[0m";
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
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerCustomer();
            break;

        case 2:
            registerParcel();
            break;
        case 3:
        {
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
            if (history.isUndoEmpty())
            {
                cout << "\nNothing to undo!\n";
            }
            else
            {
                history.undoLastChange();
                cout << "\nLast status change undone successfully!\n";
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
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }
            string startCity;

            cityNetwork.displayCities();

            cout << "\nEnter starting city: ";
            cin >> ws;
            getline(cin, startCity);

            int start = cityNetwork.getCityIndex(startCity);

            if (start == -1)
            {
                cout << "City not found!\n";
            }
            else
            {
                cityNetwork.BFS(start);
            }

            break;
        }
        case 13:
        {
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }
            string startCity;

            cityNetwork.displayCities();

            cout << "\nEnter starting city: ";
            cin >> ws;
            getline(cin, startCity);

            int start = cityNetwork.getCityIndex(startCity);

            if (start == -1)
            {
                cout << "City not found!\n";
            }
            else
            {
                cityNetwork.DFS(start);
            }

            break;
        }
        case 14:
        {
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
                break;
            }
            string sourceCity, destinationCity;

            cityNetwork.displayCities();

            cout << "\nEnter Source City: ";
            cin >> ws;
            getline(cin, sourceCity);

            cout << "Enter Destination City: ";
            getline(cin, destinationCity);

            int source = cityNetwork.getCityIndex(sourceCity);
            int destination = cityNetwork.getCityIndex(destinationCity);

            if (source == -1 || destination == -1)
            {
                cout << "One or both cities not found!\n";
            }
            else
            {
                cityNetwork.dijkstra(source, destination);
            }

            break;
        }
        case 15:
            if (cityNetwork.getVertices() == 0)
            {
                cout << "\nNo cities registered yet!\n";
            }
            else
            {
                cityNetwork.primMST();
            }
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
            if (choice >= 3 && choice <= 17)
                cout << "\nThis operation will be connected soon.\n";
            else
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 20);
}
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

Parcel* RouteWiseSystem::findParcel(string trackingID)
{
    return parcelTable.search(trackingID);
}
void RouteWiseSystem::registerCustomer()
{
    if (customerCount == customerCapacity)
    {
        expandCustomerArray();
    }

    int id;
    string name, phone, address;

    cout << "\nEnter Customer ID: ";
    cin >> id;

    if (findCustomer(id) != nullptr)
    {
        cout << "Customer ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, name);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Enter Address: ";
    getline(cin, address);

    customers[customerCount] =
        new Customer(id, name, phone, address);

    customerCount++;

    cout << "\nCustomer registered successfully!\n";
}
void RouteWiseSystem::registerParcel()
{
    if (parcelCount == parcelCapacity)
    {
        expandParcelArray();
    }

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
    cin >> customerID;

    if (findCustomer(customerID) == nullptr)
    {
        cout << "Customer does not exist!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Source City: ";
    getline(cin, source);

    cout << "Enter Destination City: ";
    getline(cin, destination);

    cout << "Enter Weight: ";
    cin >> weight;

    cout << "Enter Priority (1=Low, 2=Normal, 3=High): ";
    cin >> priority;

    if (weight <= 0 || priority < 1 || priority > 3)
    {
        cout << "Invalid weight or priority!\n";
        return;
    }

    parcels[parcelCount] =
        new Parcel(trackingID, customerID, source,
            destination, weight, priority, "Pending");

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