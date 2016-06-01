class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        auto len = x.size();
        for(int i = 3; i < len; i++)
        {
            //Three cases:
            //case 1
            if(x[i] >= x[i-2] && x[i-3] >= x[i-1]) return true; //example 1

            if(i >=4)
            {
                //case 2
                if(x[i] + x[i-4] >= x[i-2] && x[i-3] == x[i-1])
                    return true;

                //case 3
                //x[i-2]>=x[i-4] && x[i]+x[i-4]>=x[i-2] && x[i-1]<=x[i-3] && x[i-1]+x[i-5]>=x[i-3]
                if( i >=5 && x[i] + x[i-4] >= x[i-2] && x[i-3] <= x[i-5] + x[i-1] && x[i-4] <= x[i-2] && x[i-1] <=x[i-3] )
                    return true;
            }
        }
        return false;
    }
};