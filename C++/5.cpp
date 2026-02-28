#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> cost;
vector<int> dp;

int solve(int mask) {
    if (mask == (1 << N) - 1) return 0; 

    if (dp[mask] != -1) return dp[mask];

    int ans = INT_MAX;
    int worker = __builtin_popcount(mask); 

    for (int task = 0; task < N; ++task) {
        if (!(mask & (1 << task))) { // task not assigned
            ans = min(ans, cost[worker][task] + solve(mask | (1 << task)));
        }
    }

    return dp[mask] = ans;
}

int main() {
    N = 3;
    cost = {
        {9, 2, 7},
        {6, 4, 3},
        {5, 8, 1}
    };

    dp.assign(1 << N, -1);

    int minCost = solve(0);
    cout << "Minimum cost: " << minCost << endl;

    return 0;
}