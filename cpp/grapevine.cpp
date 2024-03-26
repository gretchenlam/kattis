#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

int main(){
    // reading in information
    int people, connections, days;
    cin >> people >> connections >> days;
    
    vector<string> names;
    vector<int> skepticism;
    
    // maps each person's name to index in names and skepticism vecs
    unordered_map<string, int> nameKeys;

    string s;
    int skep;
    for(int i = 0; i < people; i++){
        cin >> s >> skep;
        names.push_back(s);
        skepticism.push_back(skep);
        nameKeys[s] = i;
    }
    
    vector<vector<int>> knowEo(people);
    string s1, s2;
    int s1index, s2index;
    for(int i = 0; i < connections; i++){
        cin >> s1 >> s2;
        s1index = nameKeys[s1];
        s2index = nameKeys[s2];
        knowEo[s1index].push_back(s2index);
        knowEo[s2index].push_back(s1index);
    }
    
    string origin;
    cin >> origin;
    int originindex = nameKeys[origin];
    
    vector<bool> visited(people);
    vector<int> numberHeard(people);

    queue<int> bfsQueue;
    bfsQueue.push(originindex);
    visited[originindex] = true;
    numberHeard[originindex] = 1;
    
    int cnt = 0;
    
    while(days-- && !bfsQueue.empty()){
        int size = bfsQueue.size();
        while(size--){
            int curr = bfsQueue.front();
            bfsQueue.pop();
            for(auto j : knowEo[curr]){
                if(!visited[j]){ 
                    visited[j] = true;
                    numberHeard[j]++;
                    cnt++;
                }
                if(skepticism[j] > 0){ // if still skeptical
                    skepticism[j]--; // skepticism decrements
                    if(skepticism[j] == 0){ // if it decrements to 0, then they believe!
                        bfsQueue.push(j);
                        continue; // and we move on
                    }
                }
            }
        }
    }
    
    // counting who heard rumor
    unordered_set<int> heard;
    for(int i = 0; i < people; i++){
        if(i != originindex && numberHeard[i] > 0){
            heard.insert(i);
        }
    }
    
    cout << heard.size() << endl;
    
    return 0;
}