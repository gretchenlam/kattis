#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
const ll INF = numeric_limits<ll>::max();

ll calc_dist(pair<int,int> p1, pair<int,int> p2) {
    return pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2);
}

vector<int> dijkstra(int n, vector<vector<pair<int, ll>>>& graph, int start, int end) {
    vector<ll> distances(n + 2, INF);
    distances[start] = 0;

    vector<int> previous(n + 2, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(start, 0));

    while (!pq.empty()) {
        int curr_node = pq.top().first;
        ll curr_dist = pq.top().second;
        pq.pop();

        if (curr_dist > distances[curr_node]) {
            continue;
        }

        if (curr_node == end) {
            break;
        }
        
        for (auto& edge : graph[curr_node]) {
            int neighbor = edge.first;
            ll weight = edge.second;
            if (distances[curr_node] + weight < distances[neighbor]) {
                distances[neighbor] = distances[curr_node] + weight;
                previous[neighbor] = curr_node;
                pq.push(make_pair(neighbor, distances[neighbor]));
            }
        }
    }

    vector<int> path;
    for (int at = end; at != start; at = previous[at]) {
        if (at == -1){
            return {};
        }
        path.push_back(at);
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> spots(n + 2);
    for (int i = 0; i < n + 2; ++i) {
        cin >> spots[i].first >> spots[i].second;
    }

    vector<vector<pair<int, ll>>> graph(n + 2);
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < n + 2; ++j) {
            if (i != j) {
                graph[i].push_back(make_pair(j, calc_dist(spots[i], spots[j])));
            }
        }
    }

    vector<int> path = dijkstra(n, graph, n, n + 1);
    if (path.size() <= 2) { // no shady
        cout << "-" << endl;
    } else {
        for (int i = 0; i < path.size() - 1; i++) {
            cout << path[i] << endl;
        }
    }

    return 0;
}
