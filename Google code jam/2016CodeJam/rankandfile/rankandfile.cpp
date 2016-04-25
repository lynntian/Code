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
#include <queue>

using namespace std;

#pragma loop(hint_parallel(8))

class Solution
{
public:
    static void getinput(string filename, int& t, vector<int>&ns, vector<vector<vector<int>>>& ss)
    {
        string line;
        ifstream inFile(filename);

        if(inFile.is_open())
        {
            //first line is # of test cases
            getline(inFile, line);
            t = stoi(line);
            for(int j = 0; j < t; j++)
            {
                getline(inFile, line);
                auto n = stoi(line);
                ns.push_back(n);

                auto tms = vector<vector<int>>();
                for(int i=0; i< 2*n -1; i++)
                {
                    getline(inFile, line);
                    //parse line
                    auto vec = vector<int>();
                    parse(line, n,vec);
                    //printArray(vec);
                    tms.push_back(vec);
                }
                //cout << endl;
                ss.push_back(tms);
            }
        }
    }

    static void printArray(vector<int> v)
    {
        for(auto ve : v)
        {
            cout << ve << " ";
        }
        cout << endl;
    }
    static void parse(string line, int n, vector<int>& out)
    {
        int lastIndex = -1;
        for(int i=0; i<n-1; i++)
        {
            auto findSpace = line.find(' ', lastIndex+1);
            out.push_back(stoi(line.substr(lastIndex+1, findSpace)));
            lastIndex = findSpace;

            if(i == n-2)
            {
                out.push_back(stoi(line.substr(lastIndex+1, line.length())));
            }

        }
    }

    static void find(vector<vector<int>>& in, vector<int>& out)
    {
        auto map = unordered_map<int, int>();
        for(auto& row : in)
        {
            for(auto& c : row)
            {
                map[c]++;
            }
        }
        for(auto m : map)
        {
            if(m.second % 2 != 0)
            {
                out.push_back(m.first);
            }
        }
        sort(out.begin(), out.end());
    }
};


int main(int argc, char const *argv[])
{
    int numofcases = 0;
    auto ns = vector<int>();
    auto ss = vector<vector<vector<int>>>();
    Solution::getinput("B-large.in", numofcases, ns,ss);
    int counter = 1;
    for(auto& s : ss)
    {
        auto out = vector<int>();
        Solution::find(s, out);
        cout << "Case #" << counter<< ": ";
        for(int i = 0 ; i<out.size(); i++)
        {
            cout << out[i];
            if(i != out.size()-1) cout << " ";
            else cout << endl;
        }
        counter++;
    }
    return 0;
}