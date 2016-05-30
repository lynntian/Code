class Solution {
public:

    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        auto res = vector<int>();
        auto map = unordered_map<int, int>();
        for(auto n : nums)
        {
            map[n]++;
        }
        auto comp = [](const pair<int, int>& a, const pair<int, int>& b){
            return a.second < b.second;
        };   
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp); 
        for(auto& m : map)
        {
            q.push(m);
        }
        
        for(int i = 0; i < k; i++)
        {
            res.push_back(q.top().first);
            q.pop();
        }
        return res;
    }
};