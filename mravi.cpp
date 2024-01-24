#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    int numNodes; 
    cin >> numNodes;

    unordered_map<int, tuple<int, double, bool>> nodePipeInfo;
    for(int i = 0; i < numNodes - 1; i++){
        int parent;
        int child;
        int superPower;
        double flow;
        cin >> parent >> child >> flow >> superPower;
        nodePipeInfo[child] = make_tuple(parent, flow / 100, superPower == 1);
    }

    vector<int> antLiquid(numNodes);
    for(int i = 0; i < numNodes; i++){
        cin >> antLiquid[i];
    }

    double maxLiquidRequired = 0; // max to feed ants
    
    for(int i = 0; i < numNodes; i++){
        if(antLiquid[i] == -1){ // node not leaf node, move on!
            continue;
        }

        double liquidRequired = (double)antLiquid[i]; // liquid needed at curr node
        int currentNode = i + 1;
        while(currentNode != 1){
            // retrieving info
            int parentNode = get<0>(nodePipeInfo[currentNode]); 
            double pipeFlow = get<1>(nodePipeInfo[currentNode]); 
            bool isSuperPipe = get<2>(nodePipeInfo[currentNode]);

            if(isSuperPipe){ // if super pipe, sqrt of curr liqrequired
        
                liquidRequired = sqrt(liquidRequired);
            }
            liquidRequired /= pipeFlow; // divided by flow of pipe to get liquid required at parent

            currentNode = parentNode;
        }
        maxLiquidRequired = max(maxLiquidRequired, liquidRequired); // update max 
    }
    
    cout << fixed << setprecision(4) << maxLiquidRequired << endl;

    return 0;
}