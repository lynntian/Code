class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        //DFS
        auto visited = vector<bool>(numCourses, false);
        auto origin = vector<vector<int>>(numCourses);

        //init
        for(auto p : prerequisites)
        {
            origin[p.second].push_back(p.first);
        }

        unordered_set<int> start;
        for(int i=0; i<numCourses; i++)
        {
            start.insert(i);
        }

        while(!start.empty())
        {
            auto node = *(start.begin());

            if(DFS(origin, visited, node, start)) return false;
        }
        return true;
    }

    bool DFS(const vector<vector<int>>& map, vector<bool> &visited, int node, unordered_set<int>& start)
    {
        visited[node] = true;
        for(auto n : map[node])
        {
            if(visited[n]) return true;
            if(DFS(map, visited, n, start)) return true;
        }
        visited[node]=false;
        start.erase(node);
        return false;
    }
};