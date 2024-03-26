#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

bool does_overlap(const tuple<int, int, int, int>& story1, const tuple<int, int, int, int>& story2) {
    int w1, h1, x1, y1;
    tie(w1, h1, x1, y1) = story1;

    int w2, h2, x2, y2;
    tie(w2, h2, x2, y2) = story2;

    if (x1 + w1 <= x2) {
        return false;
    } 
    if (x2 + w2 <= x1) {
        return false;
    }
    if (y1 + h1 <= y2) {
        return false;
    }
    if (y2 + h2 <= y1) {
        return false;
    }

    return true;
}

int max_area(const vector<tuple<int, int, int, int>>& stories, vector<int>& selected, int index, int current_area) {
    if (index == stories.size()) {
        return current_area;
    }

    int o1 = max_area(stories, selected, index + 1, current_area);

    bool overlap = false;
    for (int s : selected) {
        if (does_overlap(stories[s], stories[index])) {
            overlap = true;
            break;
        }
    }

    int o2 = 0;
    if (!overlap) {
        selected.push_back(index);
        o2 = max_area(stories, selected, index + 1, current_area + get<0>(stories[index]) * get<1>(stories[index]));
        selected.pop_back();
    }

    return max(o1, o2);
}

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;

        vector<tuple<int, int, int, int>> stories;
        for (int i = 0; i < n; i++) {
            int w, h, x, y;
            cin >> w >> h >> x >> y;
            stories.emplace_back(w, h, x, y);
        }

        vector<int> selected;
        int ans = max_area(stories, selected, 0, 0);
        cout << ans << endl;
    }

    return 0;
}
