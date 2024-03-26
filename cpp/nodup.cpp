#include <iostream>
#include <string>
#include <set>
using namespace std;

int main(){
    string input = "";
    getline(cin, input);
    
    for(int i = 0; i < input.length(); i++){
        input[i] = std::tolower(input[i]);
    }
    
    input += " ";
    
    string word = "";
    // set of strings to keep track of words
    set<string> contains;
    
    for(int i = 0; i < input.length(); i++){
        if(input[i] != ' '){
            // if there is no space, then add char to word
            word += input[i];
        }else{
            // if there IS a space (indicating a completed word)
            if(contains.find(word) != contains.end()){
                // if word is in contains already
                cout << "no";
                return 0;
            }else{
                // if word is not in contains yet, add it to contains
                contains.insert(word);
                // reset word
                word = "";
            }
        }
    }
    
    cout << "yes";
    return 0;
}