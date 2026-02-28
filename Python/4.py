"""Segment Tree for Range Maximum Query with Point Updates"""

class SegmentTree:
    def __init__(self, data):
        self.n = len(data)
        self.tree = [float('-inf')] * (4 * self.n)
        self._build(data, 0, 0, self.n - 1)

    def _build(self, arr, node, start, end):
        if start == end:
            self.tree[node] = arr[start]
            return
        mid = (start + end) // 2
        self._build(arr, 2 * node + 1, start, mid)
        self._build(arr, 2 * node + 2, mid + 1, end)
        self.tree[node] = max(self.tree[2 * node + 1], self.tree[2 * node + 2])

    def update(self, idx, val, node=0, start=0, end=None):
        if end is None:
            end = self.n - 1
        if start == end:
            self.tree[node] = val
            return
        mid = (start + end) // 2
        if idx <= mid:
            self.update(idx, val, 2 * node + 1, start, mid)
        else:
            self.update(idx, val, 2 * node + 2, mid + 1, end)
        self.tree[node] = max(self.tree[2 * node + 1], self.tree[2 * node + 2])

    def query_max(self, l, r, node=0, start=0, end=None):
        if end is None:
            end = self.n - 1
        if r < start or end < l:
            return float('-inf')
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        return max(self.query_max(l, r, 2 * node + 1, start, mid),
                   self.query_max(l, r, 2 * node + 2, mid + 1, end))

if __name__ == "__main__":
    prices = [10, 20, 15, 25, 30, 5]
    st = SegmentTree(prices)

    print(f"Initial max in range [1,4]: {st.query_max(1, 4)}")   # 30

    st.update(2, 35)
    print(f"After update, max in range [1,4]: {st.query_max(1, 4)}")  # 35

    st.update(5, 40)
    print(f"After update, max in range [0,5]: {st.query_max(0, 5)}")  # 40
