#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include<cstring>
#include<algorithm>

using namespace std;

list<pair<int,int>> adjList[2001];
int weight_g_h;

int n, m, t, s, g, h;


void add_edge(int u, int v, int d){
    adjList[u].push_back(make_pair(v,d));
    adjList[v].push_back(make_pair(u,d));
}

vector<int> dijkstra(int start){
    vector<int> dist(n, 0x3fffffff);
    for(int i = 0; i <= 2001; i++){
        dist.push_back(0x3fffffff);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0,start));
    dist[start] = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        for(auto i : adjList[u]){
            int v = i.first;
            int weight = i.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v],v));
            }
        }
    }
    return dist;
}

int main(){
    int tests;
    cin >> tests;
    
    vector<int> answers; 
    vector<vector<int>> result;
    for(int test = 0; test < tests; test++){
        weight_g_h = 0;
        cin >> n >> m >> t;
        cin >> s >> g >> h;

        for(int i = 0; i < m; i++){
            int a, b, d;
            cin >> a >> b >> d;
            add_edge(a, b, d);
        }
        vector<int> destinations(t);
        
        for(int k = 0; k < t; k++){
            cin >> destinations[k];
        }
            vector<int> distS = dijkstra(s);
            vector<int> distG = dijkstra(g);
            vector<int> distH = dijkstra(h);
            int gToh = distH[g]; 
            int hTog = distG[h];
            
            for(int l = 0; l < destinations.size(); l++){
                if((distS[destinations[l]] == hTog + distS[h] + distG[destinations[l]]) || (distS[destinations[l]] == gToh + distS[g] + distH[destinations[l]])){
                    answers.push_back(destinations[l]); // push back this path to dest
                }
            }
           
        sort(answers.begin(), answers.end());
        result.push_back(answers);
        answers.clear();
        for(int p = 0; p < 2001; p++){
            adjList[p].clear();
            adjList[p].resize(0);
        }
    }
    for(auto x : result){
        for(auto y : x){
            cout << y << " ";
        }
    cout << endl;
}

    return 0;
}