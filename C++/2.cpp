#include <bits/stdc++.h>
using namespace std;

vector<int> slidingWindowMax(const vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; 

    for (int i = 0; i < nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

int main() {
    vector<int> latencies = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> maxLatencies = slidingWindowMax(latencies, k);
    cout << "Maximum latencies for each window of size " << k << ":" << endl;
    for (int maxVal : maxLatencies) {
        cout << maxVal << " ";
    }
    cout << endl;

    return 0;
}