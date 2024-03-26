#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, int> memo;  // store min moves for each board

vector<string> generateNextBoard(string currBoard, int emptySpace) {
    vector<string> nextBoards;
    int knight_moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    int x = emptySpace / 5; 
    int y = emptySpace % 5;

    for (auto& [shiftX, shiftY] : knight_moves) {
        int newX = x + shiftX;
        int newY = y + shiftY;
        if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
            string nextBoard = currBoard;
            swap(nextBoard[emptySpace], nextBoard[newX * 5 + newY]);
            nextBoards.push_back(nextBoard);  
        }
    }
    return nextBoards;
}

int bfs(string board) {
    if (memo.count(board) != 0) { // if board comp before
        return memo[board];
    }
    string finalBoard = "111110111100 110000100000"; // string rep of board
    queue<string> q;
    unordered_set<string> seen;
    q.push(board);
    memo[board] = 0; // start pos, 0 moves
    seen.insert(board);

    while(!q.empty()) {
        string currBoard = q.front();
        q.pop();
        int moves = memo[currBoard];
        if (currBoard == finalBoard) {
            return moves; 
        }
        if (moves >= 10) { // limit 
            continue;
        }
        int emptySpace = currBoard.find(' ');
        
        for (const auto& nextBoard : generateNextBoard(currBoard, emptySpace)) {
            if (seen.find(nextBoard) == seen.end()) {
                q.push(nextBoard);
                seen.insert(nextBoard); 
                if (memo.find(nextBoard) == memo.end() || memo[nextBoard] > moves + 1) {
                    memo[nextBoard] = moves + 1;
                }
            }
        }
    }

    return -1; 
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); // newline

    while (n) {
        string board = "";
        for (int i = 0; i < 5; i++) {
            string row;
            getline(cin, row);
            board += row;
        }
        memo.clear();
        int result = bfs(board);
        if (result == -1 || result > 10) {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        } else {
            cout << "Solvable in " << result << " move(s)." << endl;
        }
        n--;
    }

    return 0;
}
