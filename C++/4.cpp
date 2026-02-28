#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, INT_MIN);
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int idx, int val, int node, int start, int end) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(idx, val, 2 * node + 1, start, mid);
        } else {
            update(idx, val, 2 * node + 2, mid + 1, end);
        }
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    int query(int l, int r, int node, int start, int end) {
        if (r < start || end < l) return INT_MIN;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return max(query(l, r, 2 * node + 1, start, mid),
                   query(l, r, 2 * node + 2, mid + 1, end));
    }

    void build(const vector<int>& arr) {
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, int val) {
        update(idx, val, 0, 0, n - 1);
    }

    int queryMax(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};

int main() {
    int N = 6;
    vector<int> prices = {10, 20, 15, 25, 30, 5};
    SegmentTree st(N);
    st.build(prices);

    cout << "Initial max in range [1,4]: " << st.queryMax(1, 4) << endl; // 20,15,25,30 -> 30

    st.update(2, 35);
    cout << "After update, max in range [1,4]: " << st.queryMax(1, 4) << endl; // 20,35,25,30 -> 35

    st.update(5, 40); 
    cout << "After update, max in range [0,5]: " << st.queryMax(0, 5) << endl; // 10,20,35,25,30,40 -> 40

    return 0;
}