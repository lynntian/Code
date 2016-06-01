class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        //hash
       auto hashTable = std::unordered_map<std::string, std::string>();
       for(auto i : nums)
       {
           auto key = std::to_string(i);
           auto res = hashTable[key];
           if(res.empty())
           {
               hashTable[key] = "true";
           }
           else
           {
               return true;
           }
       }
       return false;
    }
};

//Need optimization
//add sort:
//        std::sort(nums.begin(), nums.end());
//before

//Faster solution:

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        auto size = nums.size();
        for(int i = 0; i< size; i++)
        {
            if(i+1 < size)
            {
                if(nums[i] == nums[i+1])
                {
                    return true;
                }

            }
        }
        return false;
    }
};