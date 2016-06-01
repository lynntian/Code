//404 ms
class Solution {
public:
    vector<int> countBits(int num) {
        auto res = vector<int>(num+1, 0);

        res[0] = 0;
        if(num ==0) return res;
        res[1] =1;
        if(num ==1) return res;

        int j = 2;
        for(int i=1; i<=(int)log2(num); i++)
        {
            if(j > num)
                break;
            auto b = pow(2,i);
            for(int m = 0; m < b; m++)
            {
                if(j > num)
                    break;
                res[j] = res[m]+1;
                j++;
            }
        }
        return res;
    }
};