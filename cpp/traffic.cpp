#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int find_collision_time() {
    int initial1, initial2;
    cin >> initial1 >> initial2;

    int n1, n2;
    cin >> n1;

    unordered_set<int> times;
    vector<int> times1(n1);
    for (int i = 0; i < n1; ++i) {
        cin >> times1[i];
        times.insert(times1[i]);
    }

    cin >> n2;

    vector<int> times2(n2);
    for (int i = 0; i < n2; ++i) {
        cin >> times2[i];
        times.insert(times2[i]);
    }

    bool moving1 = false;
    bool moving2 = false;

    for (int second = 0; second < times.size() + 1000000; second++) {
        if (moving1) {
            initial1 += 1;
        }
        if (moving2) {
            initial2 += 1;
        }
        // 1, 3, 5 -> 1 makes car move so erase 1.
        // 3, 5 -> 3 makes car stop so erase 3...
        if (times1.size() > 0 && second == times1[0]) {
            moving1 = !moving1;
            times1.erase(times1.begin());
        }
        if (times2.size() > 0 && second == times2[0]) {
            moving2 = !moving2;
            times2.erase(times2.begin());
        }
        if (abs(initial1 - initial2) <= 4.4) {
            return second;
        }
    }

    return 0;
}

int main() {
    int ans = find_collision_time();
    if (ans != 0) {
        cout << "bumper tap at time " << ans << endl;
    } else {
        cout << "safe and sound" << endl;
    }
    return 0;
}
