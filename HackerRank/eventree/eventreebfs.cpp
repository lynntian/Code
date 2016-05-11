#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

template <class T>
class UGraph
{
public:
    UGraph()
    {

    }

    void addNode(T node, T connect, int dis)
    {
        //check if this edge already exists // do not keep duplicate edges
        if(graph.count(node) == 1)
        {
            auto exists = false;
            for(auto& alis : graph[node])
            {
                if(alis.first == connect && dis < alis.second)
                {
                    exists = true;
                    alis.second = dis;
                }
            }
            if(!exists)
            {
                graph[node].push_back(make_pair(connect, dis));
            }
        }
        else
        {
            graph[node] = vector<pair<T, int>>();
            graph[node].push_back(make_pair(connect, dis));
        }
        if(graph.count(connect) == 1)
        {
            auto exists = false;
            for(auto& alis : graph[connect])
            {
                if(alis.first == node && dis < alis.second)
                {
                    exists = true;
                    alis.second = dis;
                }
            }
            if(!exists)
            {
                graph[connect].push_back(make_pair(node, dis));
            }
        }
        else
        {
            graph[connect] = vector<pair<T, int>>();
            graph[connect].push_back(make_pair(node, dis));
        }
    }

    ~UGraph() { graph.clear(); }

    vector<pair<T, int>>& operator[](T node)
    {
        return graph[node];
    }

    typename unordered_map<T, vector<pair<T, int>>>::iterator begin()
    {
        return graph.begin();
    }

    typename unordered_map<T, vector<pair<T, int>>>::iterator end()
    {
        return graph.end();
    }

    int Size()
    {
        return graph.size();
    }

    void printGraph()
    {
        for(auto& g : graph)
        {
            cout << "Node: " << g.first << " " << endl;
            cout << "Alist: ";
            for(auto& al : g.second)
            {
                cout <<  al.first << " : " << al.second << ", ";
            }
            cout << endl;
        }
    }
private:
    unordered_map<T, vector<pair<T, int>>> graph; 
};

void buildGraph(int& N, UGraph<int>& graph)
{
    string line;
    int m;
    cin >> N >> m;

    for(int i = 0; i < m; i++)
    {
        int node; int connect;
        cin >> node >> connect ;
        graph.addNode(node, connect, 0);
    }
}

void markEdge(UGraph<int>& graph, int node, int next)
{
    for(auto& n : graph[node])
    {
        if(n.first == next)
        {
            n.second = 1;
        }
    }
    for(auto& m : graph[next])
    {
        if(m.first == node)
        {
            m.second = 1;
        }
    }
}

void evenTree(UGraph<int>& graph, int N)
{
    auto disvec = vector<int>(N+1, 0);
    auto q = queue<int>();
    for(auto& n: graph)
    {
        if(n.second.size() == 1)
        {
            //add leaf to queue first
            //cout << "leaf: " << n.first << endl;
            q.push(n.first);
        }
    }

    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();
        //cout << "Current: " << cur << endl;

        auto count = 0;
        auto next = -1;
        auto children = 0;
        for(auto &n : graph[cur])
        {
            if(n.second != 1)
            {
                count++;
                next = n.first;
            }
            else
            {
                children += disvec[n.first];
            }
        }
        if(count == 1) // only process node if it have one edge going out (indicating that it's children nodes have been counted)
        {
            //cout << "Push next: "<< next << endl;
            q.push(next);
            disvec[cur] += children + 1;
            markEdge(graph, cur, next);
            //cout << "Current children: " << children+1 << endl;
        }
    }

    int c = 0;
    for(int i = 1; i<= N; i++)
    {
        //cout << "Index: " << i << " , children: " << disvec[i] << endl;
        if(disvec[i] > 0 && disvec[i] % 2 == 0) // count the number of even childrens, exclude root node (which will be 0)
        {
            c++;
        }
    }
    cout << c << endl;

}



int main() {
    int N; 
    auto graph = UGraph<int>();
    buildGraph(N, graph);
    //graph.printGraph();

    evenTree(graph, N);
    return 0;
}