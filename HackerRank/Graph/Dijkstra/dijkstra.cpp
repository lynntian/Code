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
#include <climits>

using namespace std;

class MinHeap
{
private:
    vector<pair<int, int>> heap;
    int size;
public:
    MinHeap()
    {
        heap = vector<pair<int, int>>();
        size = 0;
    }
    ~MinHeap()
    {}

    void insert(int key, int value)
    {
        size++;
        heap.push_back(make_pair(key,value));
        bubbleUp(size -1);
    }

    pair<int, int> getTop()
    {
        return heap[0];
    }

    void deleteMin()
    {
        auto lastElement = heap[heap.size() -1];
        heap[0] = lastElement;
        heap.pop_back();
        size--;
        //if(heap.size()) cout << "after pop, min now: " << heap[0].first << ", " << heap[0].second << endl;
        sink();
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void update(int key, int value)
    {
        int index = 0;
        for(auto& h: heap)
        {
            if(h.first == key)
            {
                h.second = value;
                bubbleUp(index);
                break;
            }
            index ++;
        }
    }

    void sink()
    {
        //starting from index 0
        //left child 2*i +1 
        //right child 2*(i+1)
        auto curIndex = 0;
        while(curIndex < size)
        {
            //cout << "sink loop current: " << curIndex << endl;
            auto left = 2 * curIndex + 1;
            auto right = 2 * curIndex + 2;

            if(left >= size) break;
            if(left < size && right >= size && heap[curIndex].second > heap[left].second)
            {
                swap(curIndex, left);
                curIndex = left;
                break;
            }
            //check both children
            if(heap[curIndex].second > heap[left].second && heap[curIndex].second > heap[right].second)
            {
                auto swapNew = (heap[left].second < heap[right].second ? left : right);
                swap(curIndex, swapNew);
                //cout << "cur: " << heap[swapNew].first << endl;
                curIndex = swapNew;
                
            }
            else if(heap[curIndex].second > heap[left].second || heap[curIndex].second > heap[right].second)
            {
                auto swapNew = (heap[left].second < heap[curIndex].second ? left : right);
                swap(curIndex, swapNew);
                curIndex = swapNew;
            }
            else
                break;
        }
    }

    void bubbleUp(int curIndex)
    {
        //starting from last element
        auto cur = heap[curIndex];

        while(curIndex != 0)
        {
            auto parent = (curIndex-1)/2; // parent (i-1)/2
            if(heap[parent].second > heap[curIndex].second)
            {
                swap(parent, curIndex);
                curIndex = parent;
            }
            else
                break;
        }
    }

    bool hasKey(int key)
    {
        for(auto& h : heap)
        {
            if(h.first == key)
                return true;
        }
        return false;
    }

    void swap(int a, int b)
    {
        //auto tmp = heap[a];
        //heap[a] = heap[b];
        //heap[b] = tmp;
        iter_swap(heap.begin() + a, heap.begin()+b);
    }
};

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
                auto flag = false;
                for(auto& ve : v)
                {
                    if(ve.first == nd && ve.second >= dis) {
                        ve.second = dis;  
                        flag = true;
                        break;
                    }
                }
                if(!flag)
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
                auto flag = false;
                for(auto& ve : v)
                {
                    if(ve.first == ns && ve.second >= dis) {
                        ve.second = dis;  
                        flag = true;
                        break;
                    }
                }
                if(!flag)
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
        if(d[i] == INT_MAX) d[i] = -1;
        cout << d[i] << " ";
    }
    cout << endl;
}

void bfsDistance(unordered_map<int,vector<pair<int, int>>>& graph, int start, int n)
{
    //auto visited = vector<bool>(n+1, false);
    auto dist = vector<int>(n+1, INT_MAX);
    dist[start] = 0;
    
    auto q = new MinHeap(); //need min heap here
    q->insert(start, 0);

    for(auto& node : graph)
    {
        if(node.first == start) continue;
        q->insert(node.first, INT_MAX);
    }
    
    while(!q->isEmpty())
    {
        auto test = q->getTop();
        auto cur = test.first;

        q->deleteMin();
        if(test.second != dist[cur]) cout << "Warning!!!" << endl;

        if(dist[cur] == INT_MAX) continue;
        auto v = graph[cur];

        for(auto& l : v)
        {
            //check to see if l is still in q
            //if(!q->hasKey(l.first)) continue;
            auto dis = dist[cur] + l.second;
            if(dist[l.first] > dis)
            {
                dist[l.first] = dis;
                //update heap value
                q->update(l.first, dis);
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