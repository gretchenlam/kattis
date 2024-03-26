#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool distribute(vector<int> &participants, vector<int>& strengths, vector<int>& pairings, int speedFactor, int mid){

    for(int i = 0; i < participants.size(); i++){
        if(participants[i] == 0){
            continue;
        }else{
            participants[i]--;
        }
        for(int j = 0; j < participants.size(); j++){ // now for second person....
                if(participants[j] == 0){
                    continue;
                }else{
                    participants[j]--; // put on kayak
                }
                if((speedFactor * (strengths[i] + strengths[j])) >= mid){ // making sure speed is
                    return true;
                }
            participants[j]++; // if not, put people "back on kayak" for next pairings to be checked
        }
        participants[i]++;
    }
    return false;
}

bool check(vector<int> participants, vector<int> strengths, vector<int> speeds, vector<int> pairings, vector<int> speedFactor, int mid){
    for(int i = 0; i < speedFactor.size(); i++){
        // checking for EVERY speedFactor and pairing for its speed
        if(!distribute(participants, strengths, pairings, speedFactor[i], mid)){
            return false;
        }
    }
    return true;
}

// binary search implementation
int binarySearch(vector<int> participants, vector<int> strengths, vector<int> speeds, vector<int> pairings, vector<int> speedFactor){
    int min = 0;
    int max = 1000000000;
    while(max - min > 1){
        int mid = (max + min) / 2;
        // check if every kayak can reach that speed
        if(check(participants, strengths, speeds, pairings, speedFactor, mid)){
            min = mid;
        }else{
            max = mid;
        }
    }
    return min;
}


int main(){
    int b, n, e;
    int sb, sn, se;
    cin >> b >> n >> e;
    cin >> sb >> sn >> se;
    vector<int> strengths;
    vector<int> speedFactor((b + n + e) / 2);
    vector<int> speeds;
    vector<int> pairings;
    vector<int> participants;

    // loading participants and strengths
    participants.push_back(b);
    participants.push_back(n);
    participants.push_back(e);
    strengths.push_back(sb);
    strengths.push_back(sn);
    strengths.push_back(se);

    // check if pairing is available
    if(b > 0){
        if(b > 1){
            pairings.push_back(sb + sb);
        }
        if(n > 0){
            pairings.push_back(sb + sn);
        }
        if(e > 0){
            pairings.push_back(sb + se);
        }
    }
    if(n > 0){
        if(n > 1){
            pairings.push_back(sn + sn);
        }
        if(e > 0){
            pairings.push_back(sn + se);
        }
    }
    if(e > 1){
        pairings.push_back(se + se);
    }

    // loading speedFactors
    for(int i = 0; i < speedFactor.size(); i++){
        cin >> speedFactor[i];
    }
    sort(speedFactor.begin(), speedFactor.end());

    // loading in possible speeds
    for(int i = 0; i < speedFactor.size(); i++){
        for(int j = 0; j < pairings.size(); j++){
            speeds.push_back(speedFactor[i] * pairings[j]);
        }
    }

    sort(speeds.begin(), speeds.end());

    int ans = binarySearch(participants, strengths, speeds, pairings, speedFactor);
    cout << ans;
    return 0;
}