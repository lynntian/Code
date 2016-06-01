class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;

        int currentDuplicateCount = 0;
        int currentNum = nums[0];
        int totalCount = 0;
        auto size = nums.size();
        for(int i=1; i< size; i++)
        {
            if(currentNum == nums[i])
            {
                currentDuplicateCount++;
            }
            else
            {
                if(currentDuplicateCount != 0 )
                {
                    totalCount += currentDuplicateCount;
                    currentDuplicateCount = 0;
                }
                nums[i-totalCount] = nums[i];
            }
            currentNum = nums[i];
        }
        if(currentDuplicateCount)
        {
            totalCount += currentDuplicateCount;
            nums[size - totalCount] = nums[size-1];
        }
        nums.erase(nums.begin() + (size - totalCount), nums.end());
        return nums.size();
    }
};