Non-dp, time limit exceeded
class Solution {
public:
    int rob(vector<int>& nums) {
        auto size = nums.size();
        if(size != 0)
        return max(sum(0, true, nums, size), sum(0, false, nums, size));
        return 0;
    }

    int sum(int index, bool r, vector<int>& nums, int size)
    {
        if(index == size -1)
        {
            return r ? nums[index] : 0;
        }
        if(r)
        {
            return sum(index +1 , false, nums, size) + nums[index];
        }
        else
            return max(sum(index + 1, true, nums, size), sum(index+1, false, nums, size));
    }
};
---------------------------
DP formula

- M(k) = money at the kth house
- P(0) = 0
- P(1) = M(1)
- P(k) = max(P(k−2) + M(k), P(k−1))

--------------------------

Since we are not allowed to rob two adjacent houses, we keep two variables pre and cur. During the i-th loop, pre records the maximum profit that we do not rob the i - 1-th house and thus the current house (the i-th house) can be robbed while cur records the profit that we have robbed the i - 1-th house.

The code is as follows.

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size(), pre = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            int temp = max(pre + nums[i], cur);
            pre = cur;
            cur = temp;
        }
        return cur;
    }
};