"""Sliding Window Maximum using Deque (O(n))"""

from collections import deque

def sliding_window_max(nums, k):
    result = []
    dq = deque()  # stores indices of potential max elements

    for i, val in enumerate(nums):
        # Remove index that fell out of the window
        if dq and dq[0] == i - k:
            dq.popleft()
        # Remove smaller elements from the back
        while dq and nums[dq[-1]] <= val:
            dq.pop()
        dq.append(i)
        # Start recording once the first window is complete
        if i >= k - 1:
            result.append(nums[dq[0]])

    return result

if __name__ == "__main__":
    latencies = [1, 3, -1, -3, 5, 3, 6, 7]
    k = 3
    max_latencies = sliding_window_max(latencies, k)
    print(f"Maximum latencies for each window of size {k}:")
    print(*max_latencies)
