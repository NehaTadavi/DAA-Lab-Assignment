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


#include <bits/stdc++.h>
using namespace std;

struct Item {
    int id;
    int weight;
    int utility;
    bool perishable;
};

void boostPerishableUtility(vector<Item>& items) {
    for (auto& it : items) {
        if (it.perishable) {
            it.utility = static_cast<int>(it.utility * 1.2);
        }
    }
}

void displaySelectedItems(vector<vector<int>>& dp, vector<Item>& items, int capacity) {
    int i = items.size();
    int w = capacity;
    int totalWeight = 0;

    cout << "\nItems loaded in the truck:" << endl;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << items[i - 1].id
                 << " | Weight: " << items[i - 1].weight
                 << " | Utility: " << items[i - 1].utility
                 << " | Perishable: " << (items[i - 1].perishable ? "Yes" : "No")
                 << endl;
            totalWeight += items[i - 1].weight;
            w -= items[i - 1].weight;
        }
        --i;
    }
    cout << "Total Weight Loaded: " << totalWeight << " kg" << endl;
}

int knapsackDP(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    items[i - 1].utility + dp[i - 1][w - items[i - 1].weight],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    displaySelectedItems(dp, items, capacity);
    return dp[n][capacity];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "SwiftCargo - Truck Loading Optimization (Knapsack with Perishables)" << endl;

    vector<Item> items = {
        {1, 10, 60, true},
        {2, 20, 100, false},
        {3, 30, 120, true},
        {4, 25, 90, false},
        {5, 15, 75, true}
    };

    int truckCapacity = 50;

    boostPerishableUtility(items);
    int maxUtility = knapsackDP(items, truckCapacity);

    cout << "\nMaximum Total Utility (using DP): " << maxUtility << endl;
    return 0;

}

