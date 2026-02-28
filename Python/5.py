"""Optimal Task Assignment using Bitmask DP"""

import sys

def min_cost_assignment(cost):
    n = len(cost)
    full_mask = (1 << n) - 1
    dp = [-1] * (1 << n)

    def solve(mask):
        if mask == full_mask:
            return 0
        if dp[mask] != -1:
            return dp[mask]

        worker = bin(mask).count('1')  # next unassigned worker
        best = sys.maxsize
        for task in range(n):
            if not (mask & (1 << task)):
                best = min(best, cost[worker][task] + solve(mask | (1 << task)))

        dp[mask] = best
        return best

    return solve(0)

if __name__ == "__main__":
    cost = [
        [9, 2, 7],
        [6, 4, 3],
        [5, 8, 1],
    ]
    print(f"Minimum cost: {min_cost_assignment(cost)}")
