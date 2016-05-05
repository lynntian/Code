#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>


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

void buildGraph(int& startNode, int& N, UGraph<int>& graph)
{
    string line;
    int m;
    cin >> N >> m;

    for(int i = 0; i < m; i++)
    {
        int node; int connect; int dis;
        cin >> node >> connect >> dis;
        graph.addNode(node, connect, dis);
    }
    cin >> startNode;
}

int main() {
    
    int startNode;
    int N;
    auto graph = UGraph<int>();
    buildGraph(startNode, N, graph);

    cout << "Starting from: " << startNode << endl;
    cout << "N nodes: " << N << endl; 
    cout << "Graph size: " << graph.Size()<<endl;

    graph.printGraph();
    return 0;
}
