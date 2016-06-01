/*
in place, move zeros to end of the array while preserving the order of the original numbers
Minimize total number of operations

------------------------------------------------------------
count zeros
size vector
2 Pointers
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        auto size = nums.size();
        for(int i=0, j=0; j < size; j++)
        {
            if(nums[j] == 0)
            {
                //current node is 0
                continue;
            }
            else // nums[j] != 0
            {
                //current node not 0, copy j to i unless i==j
                if(i < j)
                {
                    nums[i] = nums[j];
                    nums[j] =0;
                }
                i++;
            }
        }

    }
};