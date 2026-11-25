#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <climits>

using namespace std;

class Graph
{
private:
    int vertices;
    int capacity;
    string* cities;
    int** adjacencyMatrix;

    struct Node
    {
        int vertex;
        Node* next;
    };

    Node** adjacencyList;

    void addEdgeToList(int source, int destination);
    int findCity(string city);
    void expandGraph();
public:
    Graph(int totalVertices);
    ~Graph();

    void addCity(int index, string city);
    int getVertices();
    int getCityIndex(string city);
    void displayCities();

    void addEdge(int source, int destination, int weight);

    void displayMatrix();
    void displayList();

    void BFS(int start);
    void DFS(int start);

    bool isReachable(int source, int destination);

    void dijkstra(int source, int destination);
    void primMST();
    void addCity(string city);
};

#endif
