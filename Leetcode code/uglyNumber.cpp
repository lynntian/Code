class Solution {
public:
    int primeArr[3] = {2,3,5};
    bool canBeDiv(int num, int& primeNum)
    {
        for(auto& p : primeArr)
        {
            int rem = num % p;
            if( rem == 0)
            {
                primeNum = p;
                return true;
            }
        }
        primeNum = 0;
        return false;
    }
    bool isUgly(int num) {
        if(num < 1) return false;
        bool res = true;
        while(num != 1)
        {
            int outPrime = 0;
            if(canBeDiv(num, outPrime) && outPrime != 0)
            {
                num = num / outPrime;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};