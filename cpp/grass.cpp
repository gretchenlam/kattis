#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> results;

struct Sprinkler{
    double left;
    double right;
};


int minSprinklers(int n, int l, int w, vector<Sprinkler>& sprinklers){
    vector<Sprinkler> valid;
    int count = 0;
    double coveredArea = 0;
    
    for(const auto& sprinkler : sprinklers){
        double angle = asin((w * 0.5) / sprinkler.right);
        if(isnan(angle)){
            continue;
        }
        double range = sprinkler.right * cos(angle);
        valid.push_back({sprinkler.left - range, sprinkler.left + range});
    }
    
    sort(valid.begin(), valid.end(), [](const Sprinkler& sprinkler1, const Sprinkler& sprinkler2){
        return sprinkler1.left < sprinkler2.left;
    });

    while(coveredArea < l){
        auto maxSprinkler = find_if(valid.begin(), valid.end(), [coveredArea](const Sprinkler &s){
            return s.left <= coveredArea;
        });
        if(maxSprinkler == valid.end()){
            return -1;
        }
        double rightmost = maxSprinkler->right;
        for(auto it = maxSprinkler + 1; it != valid.end() && it->left <= coveredArea; it++){
            if(it->right > rightmost){
                rightmost = it->right;
                maxSprinkler = it;
            }
        }
    
        if(rightmost <= coveredArea){
            return -1;
        }
    
        count++;
        coveredArea = rightmost;
        
        valid.erase(valid.begin(), maxSprinkler + 1);
    }

    return count;

}

int main(){
    int n;
    int l;
    int w;
    while(cin >> n >> l >> w){
        vector<Sprinkler> sprinklers(n);
        for(int i = 0; i < n; i++){
            cin >> sprinklers[i].left >> sprinklers[i].right;
        }
        int singleAns = minSprinklers(n, l, w, sprinklers);
        cout << singleAns << endl;
    }
    return 0;
}