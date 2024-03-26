#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <tuple>
#include <deque>
using namespace std;


bool bfs(int source, int sink, vector<int> &pred, vector<int> &pushFlow, vector<vector<int> >& remainingCapacity, const vector<vector<int>>& adj) {
    deque<int> q;
    q.push_back(source);
    vector<bool> visited(adj.size());
    fill(visited.begin(), visited.end(), false);
    visited[source] = true;
    pushFlow[source] = INT_MAX; 

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        for (int v : adj[u]) { // only iterate from available edges
            // if visited or at capacity, next
            if (!visited[v] && remainingCapacity[u][v] > 0) { 
                visited[v] = true;
                pred[v] = u;
                pushFlow[v] = min(pushFlow[u], remainingCapacity[u][v]);
                q.push_back(v);
                if (v == sink) {
                    return true; // path to sink found
                }
            }
        }
    }
    return false; // no path found
}

int calculateMaxFlow(int source, int sink, vector<int> &pred, vector<vector<int> >& remainingCapacity, const vector<vector<int>>& adj) {
    int maxFlow = 0;
    vector<int> pushFlow(remainingCapacity.size(), 0);

    while (bfs(source, sink, pred, pushFlow, remainingCapacity, adj)) {
        int curr = pushFlow[sink]; // flow that can be pushed to sink in this round

        for (int v = sink; v != source; v = pred[v]) {
            int u = pred[v];
            remainingCapacity[u][v] -= curr;
            remainingCapacity[v][u] += curr;
        }
        maxFlow += curr;
    }
    return maxFlow;
}


int main() {
    int nodes, edges, source, sink;
    cin >> nodes >> edges >> source >> sink;
    vector<vector<int> > capacity(nodes, vector<int>(nodes));
    vector<vector<int> > remainingCapacity(nodes, vector<int>(nodes));
    vector<vector<int>> adj(nodes);  // Adjacency list for graph
    for(auto& i : capacity) {
        fill(i.begin(), i.end(), 0); 
    }

    for(auto& i : remainingCapacity) {
        fill(i.begin(), i.end(), 0);
    }

    for (int i = 0; i < edges; i++) {
        int from, to, cap;
        cin >> from >> to >> cap;
        capacity[from][to] = cap;
        remainingCapacity[from][to] = cap;
        adj[from].push_back(to);  
        adj[to].push_back(from);  
    }
    vector<tuple<int, int, int>> flows;

    vector<int> pred(nodes, -1);
    int maxFlow = calculateMaxFlow(source, sink, pred, remainingCapacity, adj);

    int usedEdges = 0;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (capacity[i][j] - remainingCapacity[i][j] > 0) {
                flows.push_back(make_tuple(i, j, capacity[i][j] - remainingCapacity[i][j]));
                usedEdges++;
            }
        }
    }

    cout << nodes << " " << maxFlow << " " << usedEdges << endl;
    for (auto &flow : flows) {
        int u, v, x;
        tie(u, v, x) = flow;
        cout << u << " " << v << " " << x << endl;
    }

    return 0;
}