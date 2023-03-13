#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include <utility>
/*
 * Având dat un graf orientat ponderat și un vârf sursă, calculați costul minim de la vârful sursă până
 * la fiecare vârf accesibil din graf. Implementarea trebuie să fie eficientă din punctul de vedere
 * al memoriei folosite și al timpului de execuție. (Implementați un algoritm de drum minim în graf:
 * Bellman-Ford, Dijkstra.)
 */
using namespace std;

#define MAXVAL INT_MAX/2


ifstream fin("../date.in");
ofstream fout("../date.out");


typedef struct {
    vector<pair<int, int>> adj;
    int val;
    int dist;
    int parent;
}Node;


struct cmp {
    bool operator()(Node* left, Node* right) {
        return left->dist > right->dist;
    }
};


void printResult(Node* list, int nodes) {
    for (int i = 0; i < nodes; i++) {
        if (list[i].dist > MAXVAL / 2) {
            fout << "INF ";
        }
        else {
            fout << list[i].dist << " ";
        }
    }
}


void dijkstra(Node* adjList, int sourceNode, int nodes) {
    adjList[sourceNode].dist = 0;
    adjList[sourceNode].parent = -1;
    vector<bool> visited;
    priority_queue < Node*, vector<Node*>, cmp> pq;
    for (int i = 0; i < nodes; i++) {
        pq.push(&adjList[i]);
        visited.push_back(false);
    }
    while (!pq.empty()) {
        Node* currentNode = pq.top();
        visited[currentNode->val] = true;
        for (pair<int, int> i : adjList[currentNode->val].adj) {
            if (visited[i.first] == false && currentNode->dist + i.second < adjList[i.first].dist) {
                adjList[i.first].dist = currentNode->dist + i.second;
                adjList[i.first].parent = currentNode->val;
            }
        }
        pq.pop();
    }
    printResult(adjList, nodes);
}


int main() {

    int sourceNode, nodes, edges;

    fin >> nodes >> edges >> sourceNode;

    Node* adjList = new Node[nodes];

    for (int i = 0; i < nodes; i++) {
        adjList[i].val = i;
        adjList[i].dist = MAXVAL;
        adjList[i].parent = -2;
    }

    for (int i = 0; i < edges; i++) {
        int start, finish, dist;
        fin >> start >> finish >> dist;
        pair<int, int> p;
        p.first = finish;
        p.second = dist;
        adjList[start].adj.push_back(p);
    }

    dijkstra(adjList, sourceNode, nodes);
    fin.close();
    fout.close();
    return 0;
}
