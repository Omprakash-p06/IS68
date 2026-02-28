#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], timer;
bool visited[MAXN];
vector<pair<int, int>> bridges;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == parent) continue;

        if (!visited[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(visited, 0, sizeof(visited));
    timer = 0;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    cout << "Critical Links (Bridges):" << endl;
    sort(bridges.begin(), bridges.end());
    for (auto& b : bridges) {
        cout << b.first << " " << b.second << endl;
    }

    return 0;
}