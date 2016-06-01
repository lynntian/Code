//Consider more than 2 duplicates
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        auto len = nums.size();
        if(!len) return false;

        unordered_map<int, vector<int>> map; // key -> nums value, value-> vector of indexes
        for(int i=0; i< len; i++)
        {
            auto& vec = map[nums[i]];
            if(vec.size())
            {
                int vl = vec.size();
                for(auto v : vec)
                {
                    if(abs(v-i) <=k) return true;
                }
            }
            vec.push_back(i);
        }
        return false;
    }
};

//Improved efficiency
//Consider more than 2 duplicates
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        auto len = nums.size();
        if(!len) return false;

        unordered_map<int, int> map; // key -> nums value, value-> vector of indexes
        int i=0;
        for(auto num : nums)
        {
            if(map.count(num) && map[num] >= i-k)
                return true;
            map[num] = i++;
        }
        return false;
    }
};