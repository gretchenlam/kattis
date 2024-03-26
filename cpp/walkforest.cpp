#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1001;
const int INF = 0x3f;
int adjM[MAXN][MAXN];
int dist[MAXN];
int paths[MAXN];
int n, m;
vector<int> countArr;

// node struct
struct Node{
    int index;
    int distance;
    Node(int index, int distance) : index(index), distance(distance){}
    bool operator<(const Node& rhs) const{
        return distance > rhs.distance;
    }
};

void dijkstra(){
    priority_queue<Node> pq;
    pq.push(Node(2, 0));
    memset(dist, INF, sizeof(dist));
    dist[2] = 0; 
    while(!pq.empty()){
        Node curr = pq.top(); 
        pq.pop();
        for(int i = 1; i <= n; i++){
            if(curr.distance + adjM[i][curr.index] < dist[i] && adjM[i][curr.index] != 0){
                pq.push(Node(i, curr.distance + adjM[i][curr.index]));
                dist[i] = curr.distance + adjM[i][curr.index];
            }
        }
    }
}
int increment(int x){
    int inc = 0;
    if(dist[x] == 0){
        return 1;
    }
    if(paths[x] != -1){
        return paths[x];
    }
    for(int i = 1; i <= n; i++){
        if(adjM[x][i] != 0 && dist[i] < dist[x]){
            inc += increment(i);
        }
    }
    paths[x] = inc;
    return paths[x];
}

int main(){
    while(cin >> n && n != 0){
        cin >> m;
        memset(adjM, 0, sizeof(adjM));
        for(int i = 0; i < m; i++){
            int a, b, d;
            cin >> a >> b >> d;
            adjM[a][b] = d;
            adjM[b][a] = d;
        }
        
        dijkstra();
        
        memset(paths, -1, sizeof(paths));
        int count = increment(1);
        countArr.push_back(count);
    }
    
    for(int i = 0; i < countArr.size(); i++){
        cout << countArr[i] << endl;
    }
    return 0;
}