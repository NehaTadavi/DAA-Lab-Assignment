//Neha Tadavi
//PRN:124B2F006
// assignment description 
// A massive earthquake has struck a remote region, and a relief organization is transporting
// essential supplies to the affected area. The organization has a limited-capacity relief truck that
// can carry a maximum weight of W kg. They have N different types of essential items, each
// with a specific weight and an associated utility value (importance in saving lives and meeting
// urgent needs).
// Since the truck has limited capacity, you must decide which items to include to maximize the
// total utility value while ensuring the total weight does not exceed the truck's limit.
// Your Task as a Logistics Coordinator:
// 1. Model this problem using the 0/1 Knapsack approach, where each item can either be
// included in the truck (1) or not (0).
// 2. Implement an algorithm to find the optimal set of items that maximizes utility while
// staying within the weight constraint.
// 3. Analyze the performance of different approaches (e.g., Brute Force, Dynamic
// Programming, and Greedy Algorithms) for solving this problem efficiently.
// 4. Optimize for real-world constraints, such as perishable items (medicines, food) having
// priority over less critical supplies.
// Extend the model to consider multiple trucks or real-time decision-making for dynamic supply
// chain management.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void greedyColoring(vector<vector<int>>& graph, int V) {
    vector<int> result(V, -1);
    vector<bool> available(V, false);


    result[0] = 0;


    for (int u = 1; u < V; u++) {
        fill(available.begin(), available.end(), false);
        for (int i = 0; i < V; i++) {
            if (graph[u][i] && result[i] != -1)
                available[result[i]] = true;
        }

        int cr;
        for (cr = 0; cr < V; cr++) {
            if (!available[cr])
                break;
        }

        result[u] = cr;
    }


    cout << "\nExam Schedule (Course : Time Slot)\n";
    cout << "----------------------------------\n";
    for (int u = 0; u < V; u++)
        cout << "Course " << u + 1 << " --> Slot " << result[u] + 1 << endl;

    int totalSlots = *max_element(result.begin(), result.end()) + 1;
    cout << "\nMinimum number of time slots required: " << totalSlots << endl;
}

int main() {
    int V, E;
    cout << "Enter number of courses (vertices): ";
    cin >> V;


    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Enter number of student conflicts (edges): ";
    cin >> E;

    cout << "Enter each conflict as: course1 course2\n";
    cout << "(Means these two courses share students and cannot have same slot)\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u - 1][v - 1] = 1;
        graph[v - 1][u - 1] = 1;
    }

    greedyColoring(graph, V);

    return 0;

}

