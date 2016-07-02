//Game of life

//class Solution{
//public: 
    // extra space count neighbours for each cell, record next state
    // 
//    void gameOfLife(vector<vector<int>>& board)
//    {

//    }
//};

// TODO test
// follow up how to hanld this case if board has bo boundary.
// ?? use queue to keep edge?
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

void printBoard(vector<vector<int>>& board)
{
    for(auto r : board)
    {
        for(auto c : r)
        {
            cout << c << " ";
        }
        cout <<endl;
    }
}

int countLiveNeighbors(vector<vector<int>>& board, int a, int b, int m, int n, vector<bool>& map)
{
    int ret = 0;
    if(a >= m || a < 0 || b >= n || b < 0) return ret;

    auto shift = {-1, 0, 1};
    for(auto s : shift)
    {
        if(a+s >= 0 && a+s < m)
        {
            for(auto p : shift)
            {
                if(s == 0 && p == 0) continue;
                if(b + p >= 0 && b +p < n)
                {
                    (board[a+s][b+p] == 1  && !map[(a+s) * n + b +p]) ||
                    (board[a+s][b+p] == 0  && map[(a+s) * n + b +p]) ? ret++ : 0;
                }
            }
        }
    }
    return ret;

}

// 1. extra space count neighbours for each cell, record next state
// inplace -> have a hash map to keep track of the change in this cell
void gameOfLife(vector<vector<int>>& board)
{
    auto m = board.size();
    if(m == 0) return;
    auto n = board[0].size();
    if(n == 0) return;

    auto map = vector<bool>(m*n, false); // key = a * n + b 

    for(int a = 0; a < m; a++)
    {
        for(int b = 0; b < n; b++)
        {
            auto count = countLiveNeighbors(board, a, b, m, n, map);
            auto& cur = board[a][b];
            if(count < 2) 
            {
                map[a *n +b] = cur != 0; // under population
                cur = 0;
            }
            else if(count == 3)
            {
                map[a*n+b] = cur == 0; // reproduction
                cur = 1;
            }
            else if(count > 3) // over population
            {
                map[a*n +b] = cur == 1;
                cur = 0;
            }
            //else count == 2 no change
        }
    }

}


int main()
{
    // m * n 3 * 3
    int m = 3;
    int n = 3;
    auto board = vector<vector<int>>(m, vector<int>(n, 0));
    board[0] = {0, 1, 1};
    board[1] = {0, 0, 1};
    board[2] = {1, 1, 1};
    cout << "board: " << endl;
    printBoard(board);

    //cout << "count live: 0, 0 " << countLiveNeighbors(board, 0, 0, m,n) << endl;
    //cout << "count live: 1, 1 " << countLiveNeighbors(board, 1, 1, m,n) << endl;

    gameOfLife(board);
    cout << "after: " << endl;
    printBoard(board);
    return 0;
}


[
    [1,1,0,0,1], 
    [1,0,0,0,1], 
    [0,0,0,1,0], 
    [1,1,1,1,1],
    [0,0,1,1,0]
]



