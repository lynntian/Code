//Given an array and a value, remove all instances of that value in place and return the new length.

//The order of elements can be changed. It doesn't matter what you leave beyond the new length.
//---------------------

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int rCount = 0;
        auto len = nums.size();
        int j=0;
        for(int i=0; i< len; i++)
        {
            if(nums[i] != val)
            {
                //if(rCount != 0)
                {
                    j = i-rCount;
                    //move element
                    nums[j] = nums[i];
                }
            }
            else if( nums[i] == val)
            {
                rCount++;
            }
        }
        if(rCount !=0)
        {
            nums.erase(nums.begin() + (len - rCount), nums.end());
        }
        return nums.size();
    }
};