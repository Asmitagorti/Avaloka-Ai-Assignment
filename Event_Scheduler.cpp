
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Check whether all meetings can be attended
bool can_attend_all(vector<pair<int, int>> events) {
    sort(events.begin(), events.end());

    for (int i = 1; i < events.size(); i++) {
        if (events[i].first < events[i - 1].second) {
            return false;
        }
    }

    return true;
}

// Find the minimum number of rooms required
int min_rooms_required(vector<pair<int, int>> events) {
    sort(events.begin(), events.end());

    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (auto event : events) {
        // Remove meetings that have finished
        while (!minHeap.empty() &&
               minHeap.top() <= event.first) {
            minHeap.pop();
        }

        // Add the current meeting's ending time
        minHeap.push(event.second);
    }

    return minHeap.size();
}

int main() {
    vector<pair<int, int>> events = {
        {9, 10}, {10, 11}, {11, 12}
    };

    cout << boolalpha;
    cout << "Can attend all: "
         << can_attend_all(events) << endl;

    cout << "Minimum rooms required: "
         << min_rooms_required(events) << endl;

    return 0;
}
