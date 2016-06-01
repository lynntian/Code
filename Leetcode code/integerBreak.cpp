class Solution {
public:
    int integerBreak(int n) {
        if(n == 2) return 1;
        else if(n==3) return 2;
        
        long product = 1;
        auto tmp = n;
        
        while(n > 4)
        {
            product*= 3;
            n -= 3;
        }
        product*=n;
        
        return product;
    }
};

//DP solution
class Solution {
public:
    int integerBreak(int n) {

        auto v = vector<int>(n+1, 0);
        for(int i=2; i < n+1; i++)
        {
            for(int j = 1; j < i; j++)
            {
                v[i] = max(v[i], max(j, v[j]) * max(i-j, v[i-j]));
            }
        }
        return v[n];
    }
};