#Neha Tadavi
#PRN:124B2F006
// assignment description 
// A smart city is implementing an intelligent traffic management system to assist ambulances
// in reaching hospitals as quickly as possible. The city’s road network is represented as a
// graph, where:
// ● Intersections (junctions) are nodes.
// ● Roads between intersections are edges with weights representing travel time (in minutes)
// considering traffic congestion.
// An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination
// D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road
// segment may change in real time.
// As a transportation engineer, you are assigned to:
// 1. Implement Dijkstra’s algorithm to find the shortest path from the ambulance's current
// location (S) to all possible hospitals.
// 2. Account for dynamic weight updates as traffic conditions change.
// 3. Optimize the system to work efficiently for a large city with thousands of intersections
// and roads.
// 4. Provide a visual representation of the optimal path for navigation.
// Expected Outcome:
// The system should suggest the quickest route for the ambulance, updating dynamically
// based on real-time traffic conditions, ensuring minimal response time to emergencies.


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

void dijkstra(int source, vector<vector<Edge>>& graph, vector<int>& dist, vector<int>& parent) {
    int V = graph.size();
    dist.assign(V, INT_MAX);
    parent.assign(V, -1);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (Edge& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(int node, vector<int>& parent) {
    if (node == -1) return;
    vector<int> path;
    int current = node;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    cout << "Optimal Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter number of intersections (vertices): ";
    cin >> V;
    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<Edge>> graph(V);

    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(Edge(v, w));
        graph[v].push_back(Edge(u, w)); // undirected
    }

    int source;
    cout << "Enter ambulance start location (source): ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;
    vector<int> hospitals(H);
    cout << "Enter hospital nodes:" << endl;
    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    vector<int> dist(V);
    vector<int> parent(V);
    dijkstra(source, graph, dist, parent);

    int minTime = INT_MAX, nearestHospital = -1;
    for (int h : hospitals) {
        if (dist[h] < minTime) {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1) {
        cout << "No hospital reachable." << endl;
    } else {
        cout << "\nNearest hospital is at node " << nearestHospital 
             << " with travel time " << minTime << " minutes." << endl;
        printPath(nearestHospital, parent);
    }

    cout << "\nDo you want to update traffic conditions? (y/n): ";
    char choice;
    cin >> choice;

    while (choice == 'y' || choice == 'Y') {
        cout << "Enter road (u v) and new travel time: ";
        int u, v, newW;
        cin >> u >> v >> newW;

        // Update edge weights
        for (Edge& edge : graph[u]) {
            if (edge.to == v) edge.weight = newW;
        }
        for (Edge& edge : graph[v]) {
            if (edge.to == u) edge.weight = newW;
        }

        // Re-run Dijkstra
        dijkstra(source, graph, dist, parent);

        minTime = INT_MAX;
        nearestHospital = -1;
        for (int h : hospitals) {
            if (dist[h] < minTime) {
                minTime = dist[h];
                nearestHospital = h;
            }
        }

        if (nearestHospital == -1) {
            cout << "No hospital reachable after update." << endl;
        } else {
            cout << "\nAfter traffic update, nearest hospital is at node " << nearestHospital 
                 << " with travel time " << minTime << " minutes." << endl;
            printPath(nearestHospital, parent);
        }

        cout << "\nDo you want to update traffic again? (y/n): ";
        cin >> choice;
    }

    return 0;


}
