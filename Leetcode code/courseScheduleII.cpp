#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool dfs(vector<vector<int>>& map, vector<bool>& visited, int node, vector<pair<int,int>>& markedList, vector<int>& res)
    {
        //temporarily mark the node with true
        visited[node] = true;

        //for each dependency in the map[node]
        for(auto m : map[node])
        {
            cout << "dfs, loop m: " << m << endl;
            //if node already visited, there is a circular dependency
            if(visited[m]) return true;
            //do a dfs on this node and check for circular denpendecy
            if(dfs(map, visited, m, markedList,res)) return true;
        }
        //mark the visited node as false
        visited[node] = false;
        //remove this node from the list
        for(auto it = markedList.begin(); it != markedList.end(); it++)
        {
            if((*it).first == node)
            {
                markedList.erase(it);
                break;
            }
        }
        auto it = find(res.begin(), res.end(), node);
        if(it == res.end())
            res.push_back(node);
        return false;
    }

    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        auto res = vector<int>();
        cout << "pre size: " << prerequisites.size()<< endl;
        if(numCourses == 0)
            return res;

        auto visited = vector<bool>(numCourses, false);

        auto map = vector<vector<int>>(numCourses, vector<int>());

        auto findStart = unordered_map<int, int>();
        for(int i=0; i< numCourses; i++)
        {
            findStart[i] = 0;
        }
        for(auto p : prerequisites)
        {
            map[p.second].push_back(p.first);
            findStart[p.first]++;
        }

        vector<pair<int, int>> markedList;
        for (auto f : findStart)
        {
            cout << "pair: " << f.first << ", " << f.second << endl;
            markedList.push_back(make_pair(f.first, f.second));
        }

        sort(markedList.begin(), markedList.end(), [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
            return a.second < b.second;
        });

        while(!markedList.empty())
        {
            auto node = (*(markedList.begin())).first;
            cout << "started with: " << node << endl;
            if(dfs(map, visited, node, markedList, res)) return vector<int>();
        }
        reverse(res.begin(), res.end());
        return res;
    }

};

int main(int argc, char const *argv[])
{
    auto s = new Solution();
    auto pre = vector<pair<int, int>>();
    pre.push_back(make_pair(2,0));
    pre.push_back(make_pair(2,1));
    auto res = s->findOrder(3, pre);
    if(res.size())
    {
        for(auto& r : res)
        {
            cout << r << " ";
        }
        cout << endl;
    }

    pre = vector<pair<int, int>>();
    pre.push_back(make_pair(0,1));
    res = s->findOrder(2, pre);
    if(res.size())
    {
        for(auto& r : res)
        {
            cout << r << " ";
        }
        cout << endl;
    }

    return 0;
}