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

    void printVec()
    {
        cout << "size: " << heap.size() << endl;
        for(auto&v: heap)
        {
            cout << v.first << " , " << v.second  << " ";
        }
        cout <<endl;
    }
};


int main()
{
    auto heap = new MinHeap();
    vector<int> tv = {13, 10, 4,3,5,1,8,7,9,16};
    for(int i = 0; i < tv.size(); i++)
    {
        heap->insert(i, tv[i]);
        //heap->printVec();
    }

    for(int j = 0; j< tv.size(); j++)
    {
        cout <<"min: " << heap->getTop().first << ", " << heap->getTop().second<<endl;
        heap->deleteMin();
        //heap->printVec();
    }
}