#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

//https://www.hackerrank.com/challenges/bfsshortreach
class Solution
{
public:

static void parseStringWithSpace(string in, long& outN, long & outM)
{
    auto index = in.find(' ');
    outN = stol(in.substr(0, index));
    outM = stol(in.substr(index+1, in.length()));
}

static void parseInput(int& numOfCases, vector<pair<long, long>>& nms, vector<long>& start, vector<unordered_map<long,vector<long>>>& adlists)
{
    string inString;
    string filename = "t5.txt";
    ifstream inFile(filename);
    if(inFile.is_open())
    {
        //cout << "Number of cases: " ;
        getline(inFile, inString);
        numOfCases = stoi(inString);
        
        //cout<< "Number of cases: " << numOfCases << endl;
        for(int i= 0; i < numOfCases; i++)
        {
            auto tmpMap = unordered_map<long,vector<long>>();
            auto m = 0L; auto n = 0L;
            //get N and M
            //cout << "N and M separated by space: " ;
            getline(inFile, inString);
            parseStringWithSpace(inString, n, m);
            nms.push_back(make_pair(n,m));
            cout <<"N: " << n << " M: " << m << endl;

            for(long j = 0; j< m; j++)
            {
                getline(inFile, inString);
                auto ns = 0L;
                auto nd = 0L;
                parseStringWithSpace(inString,ns, nd);
                if(tmpMap.count(ns) == 1 )
                {
                    auto& v = tmpMap[ns];
                    v.push_back(nd);
                    //cout <<"pushback1: "<<nd << endl;
                }
                else
                {
                    auto v = vector<long>();
                    v.push_back(nd);
                    tmpMap[ns] = v;
                    //cout <<"pushback2: "<<nd<< endl;
                }
                if(tmpMap.count(nd) == 1 )
                {
                    auto& v = tmpMap[nd];
                    v.push_back(ns);
                }
                else
                {
                    auto v = vector<long>();
                    v.push_back(ns);
                    tmpMap[nd] = v;
                }
            }
            adlists.push_back(tmpMap);

            getline(inFile, inString);

            start.push_back(stoi(inString));
        }
    }
}

static void printList(vector<long> d, long skip)
{
    if(d.size() >= 2) cout << d[1];
    for(long i = 2; i<d.size(); i++)
    {
        if(i == skip) continue;
        cout <<" " << d[i];
    }
    cout << endl;
}

static void bfsDistance(unordered_map<long,vector<long>>& graph, long start, long n)
{
    auto dist = vector<long>(n+1, -1);
    dist[start] = 0;

    auto q = queue<long>();
    q.push(start);
    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();

        if(dist[cur] == -1) continue;

        auto v = graph[cur];
        for(auto& l : v)
        {
            if(dist[l] == -1 || ( dist[l] > dist[cur] + 6))
            {
                if(dist[l] == -1)  q.push(l);
                dist[l] = dist[cur] + 6;
            }
        }
    }
    printList(dist, start);

}

};



int main() {
    auto cases = 0;
    auto nms = vector<pair<long, long>>();
    auto vmaps = vector<unordered_map<long,vector<long>>>();
    auto vstart = vector<long>();
    Solution::parseInput(cases, nms, vstart, vmaps);

    //check nums correct:
    if(cases == nms.size() && cases == vmaps.size())
    {
        for (int i = 0; i < cases; ++i)
        {
            Solution::bfsDistance(vmaps[i], vstart[i], nms[i].first);
        }
    }

    return 0;
}