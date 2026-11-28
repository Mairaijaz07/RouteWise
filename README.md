# RouteWise – Smart Delivery and Route Optimization System

## Project Overview

RouteWise is a console-based C++ application developed for a courier company to manage customers, parcels, delivery requests, and city road networks.

The system uses custom data structures and algorithms to manage normal and urgent deliveries, search parcel records, maintain delivery history, and calculate efficient delivery routes.

This project is developed as a semester project for **CL2001 – Data Structures Lab** at **FAST-NUCES**.

## Key Features

- Customer registration and management
- Parcel registration with tracking IDs
- Parcel searching using a custom hash table
- Normal delivery processing using a queue
- Urgent delivery scheduling using a priority heap
- Delivery history and undo functionality
- Parcel indexing using BST and AVL trees
- City registration and road management
- Graph representation using adjacency matrix and adjacency list
- BFS and DFS network traversal
- Shortest route calculation using Dijkstra's Algorithm
- Minimum Spanning Tree generation using Prim's Algorithm
- BST and AVL height comparison
- System statistics

## Data Structures and Algorithms Used

| Data Structure / Algorithm | Purpose |
|---|---|
| Dynamic Arrays | Store customer and parcel records |
| Hash Table with Linear Probing | Fast parcel lookup using tracking ID |
| Singly Linked List | Delivery history and queue nodes |
| Queue | Normal delivery processing |
| Max Heap | Urgent delivery scheduling |
| Stack | Undo recent status changes |
| Binary Search Tree (BST) | Ordered parcel indexing |
| AVL Tree | Balanced parcel indexing |
| Graph – Adjacency Matrix | Represent city connections and road weights |
| Graph – Adjacency List | Store connected cities |
| BFS | Network traversal |
| DFS | Network traversal |
| Dijkstra's Algorithm | Find shortest delivery route |
| Prim's Algorithm | Generate Minimum Spanning Tree |

## Project Structure

```text
RouteWise/
│
├── include/
│   ├── Customer.h
│   ├── Parcel.h
│   ├── HashTable.h
│   ├── ParcelTrees.h
│   ├── DeliveryQueue.h
│   ├── UrgentHeap.h
│   ├── DeliveryHistory.h
│   ├── Graph.h
│   └── RouteWiseSystem.h
│
├── src/
│   ├── Customer.cpp
│   ├── Parcel.cpp
│   ├── HashTable.cpp
│   ├── ParcelTrees.cpp
│   ├── DeliveryQueue.cpp
│   ├── UrgentHeap.cpp
│   ├── DeliveryHistory.cpp
│   ├── Graph.cpp
│   └── RouteWiseSystem.cpp
│
├── tests/
│   ├── test_delivery.cpp
│   └── test_history.cpp
│
├── main.cpp
├── README.md
└── .gitignore
```

## Application Menu

The integrated application provides the following options:

1. Register Customer
2. Register Parcel
3. Search Parcel
4. Add Normal Delivery Request
5. Add Urgent Delivery Request
6. Process Next Delivery
7. Mark Parcel as Delivered
8. Undo Last Operation
9. Display Pending Deliveries
10. Display Parcel Records
11. Display City Network
12. BFS Network Traversal
13. DFS Network Traversal
14. Find Shortest Delivery Route
15. Generate Minimum Delivery Network
16. Compare BST and AVL Performance
17. Display System Statistics
18. Register City
19. Add Road Between Cities
20. Exit

## Requirements

- Windows operating system
- C++ compiler (Microsoft Visual C++ recommended)
- Microsoft Visual Studio

## Compilation and Execution

Open the project folder in Visual Studio using Folder View.

Open the Visual Studio Developer Terminal and navigate to the project directory:

```cmd
cd C:\Users\Fatima\Desktop\Project_DSA
```

Compile the complete project using:

```cmd
cl /EHsc /I include main.cpp src\Customer.cpp src\Parcel.cpp src\HashTable.cpp src\ParcelTrees.cpp src\DeliveryQueue.cpp src\UrgentHeap.cpp src\DeliveryHistory.cpp src\Graph.cpp src\RouteWiseSystem.cpp /Fe:RouteWise.exe
```

Run the application:

**PowerShell:**

```powershell
.\RouteWise.exe
```

**Command Prompt:**

```cmd
RouteWise.exe
```

## Sample City Network

The system allows users to register cities and connect them through weighted roads.

Example locations:

- Warehouse
- City Center
- University
- Hospital
- Airport
- Railway Station
- Industrial Area
- Residential Area

Users can add roads and assign positive distances between connected cities.

## Time Complexity Analysis

| Operation | Time Complexity |
|---|---|
| Customer search | O(n) |
| Parcel lookup – Hash Table | Average O(1), Worst O(n) |
| Normal queue insertion | O(1) |
| Normal queue removal | O(1) |
| Urgent heap insertion | O(log n) |
| Urgent heap removal | O(log n) |
| Delivery history insertion | O(1) |
| Undo operation | O(1) |
| BST insertion/search | Average O(log n), Worst O(n) |
| AVL insertion/search | O(log n) |
| BFS traversal | O(V + E) |
| DFS traversal | O(V + E) |
| Dijkstra's Algorithm (matrix implementation) | O(V²) |
| Prim's Algorithm (matrix implementation) | O(V²) |

Where:
- **n** = number of records
- **V** = number of graph vertices (cities)
- **E** = number of graph edges (roads)

## Testing

The project includes separate test files for delivery structures and delivery history.

The integrated application can also be demonstrated through its menu by registering customers and parcels, processing deliveries, performing searches, and exploring the city network.

## Team Contributions

| Team Member | Responsibilities |
|---|---|
| Member A | Customer, Parcel, Hash Table, BST and AVL Trees |
| Member B | Delivery Queue, Urgent Heap, Delivery History and Graph |
| Member C | [Add assigned modules and responsibilities] |

## Project Restrictions

The required data structures are implemented using custom C++ classes and dynamic memory allocation.

STL containers such as `vector`, `list`, `queue`, `stack`, `map`, and `priority_queue` are not used as replacements for the required custom implementations.

## Conclusion

RouteWise demonstrates how fundamental data structures and algorithms can be integrated into a practical delivery management and route optimization application. It combines parcel management, priority-based scheduling, efficient searching, delivery history, and graph-based route planning in one console-based system.
