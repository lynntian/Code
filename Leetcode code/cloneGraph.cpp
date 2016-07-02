/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

 //DFS

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        auto clone = new UndirectedGraphNode(node->label);

        //dfs
        auto lookup = unordered_map<int, UndirectedGraphNode*>();
        lookup[clone->label] = clone;

        dfs(node, clone, lookup);
        return clone;
    }

    void dfs(UndirectedGraphNode* node , UndirectedGraphNode* clone, unordered_map<int, UndirectedGraphNode*>& lookup)
    {
        for(auto &n : node->neighbors)
        {
            if(lookup.count(n->label) == 1)
            {
                clone->neighbors.push_back(lookup[n->label]);
                continue;
            }
            auto newNode = new UndirectedGraphNode(n->label);
            lookup[n->label] = newNode;
            clone->neighbors.push_back(newNode);
            dfs(n, newNode, lookup);
        }
    }


//bfs
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(!node) return nullptr;
        auto clone = new UndirectedGraphNode(node->label);
        bfs(node, clone);

        return clone;
    }

    void bfs(UndirectedGraphNode* node /*original graph*/, UndirectedGraphNode* clone)
    {
        auto lookup = unordered_map<int, UndirectedGraphNode*>();
        auto q = queue<UndirectedGraphNode*>();
        auto p = queue<UndirectedGraphNode*>();
        p.push(clone);
        q.push(node);
        lookup[clone->label] = clone;

        while(!q.empty() && !p.empty())
        {
            auto tmp = q.front();
            q.pop();
            auto cl = p.front();
            p.pop();

            for(auto& n : tmp->neighbors)
            {
                if(lookup.count(n->label) == 1)
                {
                    cl->neighbors.push_back(lookup[n->label]);
                    continue;
                }
                auto newNode = new UndirectedGraphNode(n->label);
                lookup[n->label] = newNode;
                cl->neighbors.push_back(newNode);
                p.push(newNode);
                q.push(n);
            }
        }

    }

};