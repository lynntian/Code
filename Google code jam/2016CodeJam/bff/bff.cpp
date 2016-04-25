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

   static void getinput(string filename, int& t, vector<int>&ns, vector<unordered_map<int, vector<int>>>& als)
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

                getline(inFile, line);
                std::vector<int> v;
                parse(line, n, v);

                auto tmp = unordered_map<int, vector<int>>();
                for(int i=1; i <= n; i++)
                {
                    if(tmp.count(i) == 1)
                    {
                        auto& vec = tmp[i];
                        vec.push_back(v[i-1]);
                    }
                    else
                    {
                        auto vec = vector<int>();
                        vec.push_back(v[i-1]);
                        tmp[i] = vec;
                    }
                }
                als.push_back(tmp);
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

    static void bff(unordered_map<int, vector<int>>& g, int n, int& out)
    {
        cout << "n: " << n << endl;
        cout <<"graph size: " << g.size() << endl;
        for(auto m : g)
        {
            //cout << "from: " << m.first << endl;
            //printArray(m.second);

            auto visited = unordered_map<int, int>(); // 0 if it's not visited

            out= max(dfs(g, m.first, visited), out);
            cout << "out: " << out << endl; 
            if(out == n) return;
        }

    }

    static int findLongestLeg(unordered_map<int, vector<int>>& g, int cur, unordered_map<int, int>& visited)
    {
        if(visited[cur] != 1) return 0;
        auto mv = 0;
        for(auto v: g)
        {
            for(auto x : v.second)
            {
                if(x == cur)
                {
                    visited[x]++;
                    mv = max(findLongestLeg(g, v.first, visited)+1, mv);
                    visited[x]--;
                }
            }
        }
        return mv;
    }

    static int dfs(unordered_map<int, vector<int>>& g, int cur, unordered_map<int, int>& visited)
    {

        //find the close circle then plus the edges
        if(visited[cur] != 0) 
        {
            return findLongestLeg(g, cur, visited);
            //foreach visited node, reverse find the longest leg
            
        }

        auto v = g[cur];
        visited[cur] =1;
        auto ma = 0;
        for(auto vs : v)
        {
            ma = max(dfs(g, vs, visited) + 1, ma);
        }
        return ma;
    }

};

int main(int argc, char const *argv[])
{
    int numofcases = 0;
    auto ns = vector<int>();
    auto als = vector<unordered_map<int, vector<int>>>();
    Solution::getinput("t.txt", numofcases, ns,als);
    int counter = 1;
    auto biggestloop = 0;
    for(auto& s : als)
    {
        int out = 0;
        Solution::bff(s, ns[counter-1], out);
        cout << "Case #" << counter<< ": " << out << endl;
        
        counter++;
    }
    return 0;
}