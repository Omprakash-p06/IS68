"""Find Bridges (Critical Links) in an Undirected Graph — Tarjan's Algorithm"""

import sys
sys.setrecursionlimit(200000)

def find_bridges(V, adj):
    disc = [0] * V
    low = [0] * V
    visited = [False] * V
    bridges = []
    timer = [0]

    def dfs(u, parent):
        visited[u] = True
        timer[0] += 1
        disc[u] = low[u] = timer[0]

        for v in adj[u]:
            if v == parent:
                continue
            if not visited[v]:
                dfs(v, u)
                low[u] = min(low[u], low[v])
                if low[v] > disc[u]:
                    bridges.append((min(u, v), max(u, v)))
            else:
                low[u] = min(low[u], disc[v])

    for i in range(V):
        if not visited[i]:
            dfs(i, -1)

    bridges.sort()
    return bridges

if __name__ == "__main__":
    V, E = map(int, input("Enter number of vertices and edges: ").split())
    adj = [[] for _ in range(V)]

    for _ in range(E):
        u, v = map(int, input().split())
        adj[u].append(v)
        adj[v].append(u)

    bridges = find_bridges(V, adj)
    print("Critical Links (Bridges):")
    for u, v in bridges:
        print(u, v)
