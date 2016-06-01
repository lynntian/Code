/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

 /**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i >=0; i--)
        {
            s.push(nestedList[i]);
        }
        unwind();
    }
    
    void unwind()
    {
        while(!s.empty() && !s.top().isInteger())
        {
            auto cur = s.top().getList();
            s.pop();
            
            for(int i = cur.size()-1; i >=0; i--)
            {
                s.push(cur[i]);
            }
        }
    }

    int next() {
        auto t = s.top();
        s.pop();
        
        unwind();
        return t.getInteger();
    }

    bool hasNext() {
        return !s.empty();
    }
    
private:
    stack<NestedInteger> s;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

 //--------
 //Init impl


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        s.push(make_pair(0, nestedList));
        tmp.first = false;
        tmp.second = -1;
    }

    int next() {
        if(tmp.first)
        {
            tmp.first = false;
            return tmp.second;
        }
        return -1;
    }

    bool hasNext() {
        if(tmp.first) return tmp.first;
        
        auto status = false;
        while(!s.empty())
        {
            auto p = s.top();
            s.pop();
            
            if(p.first >= p.second.size())
            {
                continue;
            }
            else // index valid
            {
                //inspect element
                auto cur = p.second[p.first];
                if(cur.isInteger())
                {
                    tmp.first = true;
                    tmp.second = cur.getInteger();
                    
                    s.push(make_pair(p.first+1, p.second));
                    status = true;
                    break;
                }
                else
                {
                    s.push(make_pair(p.first+1, p.second));
                    s.push(make_pair(0, cur.getList()));
                }
            }
        }
        return status;
    }
    
private:
    pair<bool, int> tmp;
    stack<pair<int,vector<NestedInteger>>> s;
};

