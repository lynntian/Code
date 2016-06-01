class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        auto size = nums.size();
        if(size < 3) return false;

        auto tempMin = INT_MAX;
        auto secondMin = INT_MAX;
        for(int i=0; i< size; i++)
        {
            if(tempMin >= nums[i])
            {
                tempMin = nums[i];
            }
            else if(secondMin >= nums[i])
            {
                secondMin = nums[i];
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};