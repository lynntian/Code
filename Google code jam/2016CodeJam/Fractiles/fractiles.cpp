#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

#pragma loop(hint_parallel(8))

class Solution{
public:
    static void parseInFile(string filename, int& numbers, std::vector<std::vector<int>>& vec)
    {
        string line;
        ifstream inFile(filename);

        if(inFile.is_open())
        {
            //first line is # of test cases
            getline(inFile, line);
            numbers = stoi(line);

            while(getline(inFile, line))
            {
                auto index = line.find(' ');
                auto v = vector<int>();
                v.push_back(stoi(line.substr(0, index)));
                auto secondindex = line.find(' ', index+1);
                v.push_back(stoi(line.substr(index+1, secondindex)));
                v.push_back(stoi(line.substr(secondindex+1, line.length() -1)));
                vec.push_back(v);

                //cout << "k: " << v[0] <<" c: " << v[1] << " s: " << v[2] << endl;
            }
        }
    }

    //with assumption that k == s always have a solution, check all tiles
    static void fractilesSmall(int k, int c, int s )
    {
        unsigned long long base  = 0ULL;
        for(int j = 1; j < c; j++)
        {
            base += pow(k, c-j);
        }
        //cout << "base: " << base << endl;

        //Find the corresponding tile from original K
        for(int i = 0; i < k; i++)
        {
            unsigned long long tmpIndex = (unsigned long long)(i) * base + (unsigned long long)(i + 1);
            cout << " " <<tmpIndex;
        }
    }
};

int main()
{
    int numOfCases = 0;
    vector<std::vector<int>> vec;
    Solution::parseInFile("D-small-attempt1.in", numOfCases, vec);
    for(int i = 1 ; i <= numOfCases; i++)
    {
        cout << "Case #" << i << ":" ;
        if( vec[i-1][2] < vec[i-1][0])
        {
            cout << " IMPOSSIBLE" << endl;
        }
        else
        {
            Solution::fractilesSmall(vec[i-1][0], vec[i-1][1], vec[i-1][2]);
            cout << endl;
        }
    }    
    return 0;
}
