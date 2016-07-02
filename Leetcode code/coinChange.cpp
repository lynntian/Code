/*

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.



//DP 

dp[0] = 0;
dp[1] = 1;
dp[2] = ? 

*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int ret = -1;

        //check coin options and amount
        if(coins.size() == 0 || amount < 0) return ret;

        auto dp = std::vector<int>(amount+1, INT_MAX);

        dp[0] = 0;
/*
//S1 184MS
        for(int i=1; i < amount+1; i++)
        {
            for(auto c: coins)
            {
                if(i - c>=0 && dp[i-c] >= 0 )
                {
                    auto nCount = dp[i-c]+1;
                    if(dp[i] == -1 ||dp[i] > nCount) dp[i] = nCount;
                }
            }
        }
*/
        //S2 116MS
        for(int i = 0; i < coins.size(); i++)
        {
            for(int j = coins[i]; j <= amount; j++)
            {
                auto tmp = (dp[j - coins[i]]+1);
                dp[j] = min(dp[j], ( tmp -1 == INT_MAX) ? INT_MAX : tmp);
            }
        }
        
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};