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

void parseStringWithSpace(string in, int& outN, int & outM)
{
    auto index = in.find(' ');
    outN = stoi(in.substr(0, index));
    outM = stoi(in.substr(index+1, in.length()));
}
void parseStringThree(string in, int& a, int& b, int& dis)
{
    auto index = in.find(' ');
    a = stoi(in.substr(0, index));
    auto secondIndex = in.find(' ', index+1);
    b = stoi(in.substr(index+1, secondIndex));
    dis = stoi(in.substr(secondIndex+1, in.length()));
}

void parseInput(int& numOfCases, vector<pair<int, int>>& nms, vector<int>& start, vector<unordered_map<int,vector<pair<int, int>>>>& adlists)
{
    string inString;
    getline(cin, inString);
    numOfCases = stoi(inString);

    for(int i= 0; i < numOfCases; i++)
    {
        auto tmpMap = unordered_map<int,vector<pair<int,int>>>();
        auto m = 0; auto n = 0;
        //get N and M
        getline(cin, inString);
        parseStringWithSpace(inString, n, m);
        nms.push_back(make_pair(n,m));

        for(int j = 0; j< m; j++)
        {
            getline(cin, inString);
            auto ns = 0;
            auto nd = 0;
            auto dis = 0;
            parseStringThree(inString,ns, nd, dis);
            if(tmpMap.count(ns) == 1 )
            {
                auto& v = tmpMap[ns];
                v.push_back(make_pair(nd, dis));
            }
            else
            {
                auto v = vector<pair<int, int>>();
                v.push_back(make_pair(nd, dis));
                tmpMap[ns] = v;
            }
            if(tmpMap.count(nd) == 1 )
            {
                auto& v = tmpMap[nd];
                v.push_back(make_pair(ns, dis));
            }
            else
            {
                auto v = vector<pair<int, int>>();
                v.push_back(make_pair(ns, dis));
                tmpMap[nd] = v;
            }
        }
        adlists.push_back(tmpMap);

        getline(cin, inString);

        start.push_back(stoi(inString));
    }
}

void printList(vector<int> d, int skip)
{
    for(int i = 1; i<d.size(); i++)
    {
        if(i == skip) continue;
        cout << d[i] << " ";
    }
    cout << endl;
}

void bfsDistance(unordered_map<int,vector<pair<int, int>>>& graph, int start, int n)
{
    //auto visited = vector<bool>(n+1, false);
    auto dist = vector<int>(n+1, -1);
    dist[start] = 0;

    auto q = queue<int>();
    q.push(start);
    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();
        //visited[cur] = true;
        if(dist[cur] == -1) continue;

        auto v = graph[cur];

        for(auto& l : v)
        {
            //if(visited[l]) continue;
            if(dist[l.first] == -1 || (dist[l.first] >= dist[cur] + 6))
            {
                if(dist[l.first] == -1)  q.push(l.first);
                dist[l.first] = dist[cur] + l.second;
            }
        }
    }
    printList(dist, start);

}

int main() {
    auto cases = 0;
    auto nms = vector<pair<int, int>>();
    auto vmaps = vector<unordered_map<int,vector<pair<int, int>>>>();
    auto vstart = vector<int>();
    parseInput(cases, nms, vstart, vmaps);

    //check nums correct:
    if(cases == nms.size() && cases == vmaps.size())
    {
        for (int i = 0; i < cases; ++i)
        {
            bfsDistance(vmaps[i], vstart[i], nms[i].first);
        }
    }
    return 0;
}