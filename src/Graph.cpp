#include "Graph.h"
#include <climits>

Graph::Graph(int totalVertices)
{
    vertices = 0;
    capacity = totalVertices;

    if (capacity < 1)
    {
        capacity = 1;
    }

    cities = new string[capacity];

    adjacencyMatrix = new int* [capacity];
    adjacencyList = new Node * [capacity];

    for (int i = 0; i < capacity; i++)
    {
        adjacencyMatrix[i] = new int[capacity];
        adjacencyList[i] = NULL;

        for (int j = 0; j < capacity; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < capacity; i++)
    {
        delete[] adjacencyMatrix[i];

        Node* temp = adjacencyList[i];

        while (temp != NULL)
        {
            Node* current = temp;
            temp = temp->next;
            delete current;
        }
    }

    delete[] adjacencyMatrix;
    delete[] adjacencyList;
    delete[] cities;
}

void Graph::addCity(int index, string city)
{
    if (index < 0 || index > vertices)
    {
        cout << "Invalid city index.\n";
        return;
    }

    if (findCity(city) != -1 && index == vertices)
    {
        cout << "City already exists.\n";
        return;
    }

    if (index == vertices)
    {
        if (vertices == capacity)
        {
            expandGraph();
        }

        cities[vertices] = city;
        vertices++;
    }
    else
    {
        cities[index] = city;
    }
}
void Graph::addCity(string city)
{
    if (findCity(city) != -1)
    {
        cout << "City already exists.\n";
        return;
    }

    addCity(vertices, city);
}


int Graph::findCity(string city)
{
    size_t start = city.find_first_not_of(" \t\r\n");

    if (start == string::npos)
        return -1;

    city = city.substr(start, city.find_last_not_of(" \t\r\n") - start + 1);

    for (int i = 0; i < vertices; i++)
    {
        string storedCity = cities[i];

        size_t first = storedCity.find_first_not_of(" \t\r\n");

        if (first == string::npos)
            continue;

        storedCity = storedCity.substr(first,
            storedCity.find_last_not_of(" \t\r\n") - first + 1);

        if (storedCity == city)
            return i;
    }

    return -1;
}

int Graph::getVertices()
{
    return vertices;
}

int Graph::getCityIndex(string city)
{
    return findCity(city);
}

void Graph::displayCities()
{
    cout << "\nREGISTERED CITIES\n\n";

    if (vertices == 0)
    {
        cout << "No cities registered yet.\n";
        return;
    }

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ". " << cities[i] << endl;
    }
}
void Graph::addEdgeToList(int source, int destination)
{
    Node* temp = adjacencyList[source];

    while (temp != NULL)
    {
        if (temp->vertex == destination)
        {
            return;
        }

        temp = temp->next;
    }

    Node* newNode = new Node;

    newNode->vertex = destination;
    newNode->next = NULL;

    // Add at the end so neighbours stay in the order roads were added
    if (adjacencyList[source] == NULL)
    {
        adjacencyList[source] = newNode;
    }
    else
    {
        Node* last = adjacencyList[source];

        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = newNode;
    }
}

void Graph::addEdge(int source, int destination, int weight)
{
    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices ||
        source == destination || weight <= 0)
    {
        cout << "Invalid edge details.\n";
        return;
    }

    if (adjacencyMatrix[source][destination] != 0)
    {
        cout << "Road already exists between these cities!\n";
        return;
    }

    adjacencyMatrix[source][destination] = weight;
    adjacencyMatrix[destination][source] = weight;

    addEdgeToList(source, destination);
    addEdgeToList(destination, source);

    cout << "Road added successfully!\n";
}
void Graph::displayMatrix()
{
    cout << "\nADJACENCY MATRIX\n\n";

    if (vertices == 0)
    {
        cout << "No cities registered yet.\n";
        return;
    }

    cout << "\t";

    for (int i = 0; i < vertices; i++)
        cout << cities[i] << "\t";

    cout << endl;

    for (int i = 0; i < vertices; i++)
    {
        cout << cities[i] << "\t";

        for (int j = 0; j < vertices; j++)
            cout << adjacencyMatrix[i][j] << "\t";

        cout << endl;
    }
}
void Graph::displayList()
{
    cout << "\nADJACENCY LIST\n\n";
    if (vertices == 0)
    {
        cout << "No cities registered yet.\n";
        return;
    }
    for (int i = 0; i < vertices; i++)
    {
        cout << cities[i] << " -> ";

        Node* temp = adjacencyList[i];

        while (temp != NULL)
        {
            cout << cities[temp->vertex] << " -> ";
            temp = temp->next;
        }

        cout << "NULL\n";
    }
}

void Graph::BFS(int start)
{
    if (start < 0 || start >= vertices)
    {
        cout << "Invalid starting vertex.\n";
        return;
    }

    bool* visited = new bool[vertices];
    int* queue = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false;
    }

    int front = 0;
    int rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    cout << "\nBFS Traversal: ";

    while (front < rear)
    {
        int current = queue[front++];

        cout << cities[current] << " ";

        Node* temp = adjacencyList[current];

        while (temp != NULL)
        {
            int neighbour = temp->vertex;

            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                queue[rear++] = neighbour;
            }

            temp = temp->next;
        }
    }

    cout << endl;

    delete[] visited;
    delete[] queue;
}

void Graph::DFS(int start)
{
    if (start < 0 || start >= vertices)
    {
        cout << "Invalid starting vertex.\n";
        return;
    }

    bool* visited = new bool[vertices];
    int* stack = new int[vertices];
    Node** nextNeighbour = new Node*[vertices];

    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false;
        nextNeighbour[i] = adjacencyList[i];
    }

    int top = -1;

    cout << "\nDFS Traversal: ";

    // Visit the start city and push it on the stack
    visited[start] = true;
    cout << cities[start] << " ";
    stack[++top] = start;

    while (top != -1)
    {
        int current = stack[top];
        Node* temp = nextNeighbour[current];

        if (temp == NULL)
        {
            // All neighbours done, go back
            top--;
        }
        else
        {
            nextNeighbour[current] = temp->next;

            if (!visited[temp->vertex])
            {
                // Go deeper immediately
                visited[temp->vertex] = true;
                cout << cities[temp->vertex] << " ";
                stack[++top] = temp->vertex;
            }
        }
    }

    cout << endl;

    delete[] visited;
    delete[] stack;
    delete[] nextNeighbour;
}

bool Graph::isReachable(int source, int destination)
{
    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices)
    {
        return false;
    }

    bool* visited = new bool[vertices];
    int* queue = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false;
    }

    int front = 0;
    int rear = 0;

    visited[source] = true;
    queue[rear++] = source;

    while (front < rear)
    {
        int current = queue[front++];

        if (current == destination)
        {
            delete[] visited;
            delete[] queue;
            return true;
        }

        Node* temp = adjacencyList[current];

        while (temp != NULL)
        {
            int neighbour = temp->vertex;

            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                queue[rear++] = neighbour;
            }

            temp = temp->next;
        }
    }

    delete[] visited;
    delete[] queue;

    return false;
}


void Graph::dijkstra(int source, int destination)
{
    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices)
    {
        cout << "Invalid city index.\n";
        return;
    }

    int* distance = new int[vertices];
    bool* visited = new bool[vertices];
    int* previous = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        previous[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < vertices; count++)
    {
        int minimum = INT_MAX;
        int current = -1;

        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i] && distance[i] < minimum)
            {
                minimum = distance[i];
                current = i;
            }
        }

        if (current == -1)
        {
            break;
        }

        visited[current] = true;

        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[current][j] != 0 &&
                !visited[j] &&
                distance[current] != INT_MAX)
            {
                int newDistance =
                    distance[current] + adjacencyMatrix[current][j];

                if (newDistance < distance[j])
                {
                    distance[j] = newDistance;
                    previous[j] = current;
                }
            }
        }
    }

    cout << "\nSHORTEST ROUTE\n\n";

    cout << "Source: " << cities[source] << endl;
    cout << "Destination: " << cities[destination] << endl;

    if (distance[destination] == INT_MAX)
    {
        cout << "Destination is unreachable.\n";
    }
    else
    {
        int* path = new int[vertices];
        int pathLength = 0;

        int current = destination;

        while (current != -1)
        {
            path[pathLength] = current;
            pathLength++;

            current = previous[current];
        }

        cout << "\nRecommended Route: ";

        for (int i = pathLength - 1; i >= 0; i--)
        {
            cout << cities[path[i]];

            if (i > 0)
            {
                cout << " -> ";
            }
        }

        cout << "\n\nTotal Distance: "
            << distance[destination] << " km\n";

        delete[] path;
    }

    delete[] distance;
    delete[] visited;
    delete[] previous;
}


void Graph::primMST()
{
    if (vertices == 0)
    {
        cout << "Graph is empty.\n";
        return;
    }

    int* parent = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    for (int i = 0; i < vertices; i++)
    {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;

    int count;

    for (count = 0; count < vertices; count++)
    {
        int minimum = INT_MAX;
        int current = -1;

        for (int i = 0; i < vertices; i++)
        {
            if (!inMST[i] && key[i] < minimum)
            {
                minimum = key[i];
                current = i;
            }
        }

        if (current == -1)
        {
            break;
        }

        inMST[current] = true;

        for (int j = 0; j < vertices; j++)
        {
            if (adjacencyMatrix[current][j] != 0 &&
                !inMST[j] &&
                adjacencyMatrix[current][j] < key[j])
            {
                key[j] = adjacencyMatrix[current][j];
                parent[j] = current;
            }
        }
    }

    if (count != vertices)
    {
        cout << "MST cannot be formed. Graph is disconnected.\n";
    }
    else
    {
        int totalWeight = 0;

        cout << "\nMINIMUM SPANNING TREE\n\n";

        for (int i = 1; i < vertices; i++)
        {
            cout << cities[parent[i]] << " - "
                << cities[i] << " : "
                << key[i] << endl;

            totalWeight += key[i];
        }

        cout << "\nTotal MST Weight: "
            << totalWeight << endl;
    }

    delete[] parent;
    delete[] key;
    delete[] inMST;
}
void Graph::expandGraph()
{
    int newCapacity = capacity * 2;

    string* newCities = new string[newCapacity];

    int** newMatrix = new int* [newCapacity];
    Node** newList = new Node * [newCapacity];

    for (int i = 0; i < newCapacity; i++)
    {
        newMatrix[i] = new int[newCapacity];
        newList[i] = NULL;

        for (int j = 0; j < newCapacity; j++)
        {
            newMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        newCities[i] = cities[i];

        for (int j = 0; j < vertices; j++)
        {
            newMatrix[i][j] = adjacencyMatrix[i][j];
        }

        newList[i] = adjacencyList[i];
    }

    for (int i = 0; i < capacity; i++)
    {
        delete[] adjacencyMatrix[i];
    }

    delete[] adjacencyMatrix;
    delete[] adjacencyList;
    delete[] cities;

    cities = newCities;
    adjacencyMatrix = newMatrix;
    adjacencyList = newList;

    capacity = newCapacity;
}