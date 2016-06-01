class Solution {
public:
    int divide(int dividend, int divisor) {
        if(divisor == 0) return dividend > 0 ? INT_MAX : INT_MIN;

        auto negflag = false;
        if(dividend < 0)
        {
            negflag = !negflag;
        }
        unsigned long de = abs((long)dividend);
        if(divisor < 0)
        {
            negflag = !negflag;
        }
        unsigned long di = abs((long)divisor);
        cout << "de " << de <<" : "<<dividend << endl;
        cout << "di " << di <<" : " << divisor << endl;

        unsigned long res = 0;
        int count = 0;
        auto tmpdivisor = di;
        while(true)
        {
            if(de >= tmpdivisor)
            {
                //divisor * 2
                tmpdivisor = tmpdivisor << 1;
                count ++;
            }
            else // dividend <= divisor
            {
                if(count != 0)
                {
                    auto tmp = di << (count - 1);
                    de = de - tmp;
                    res += (1 << (count-1));
                    cout << "count: " << count << " res: " << res<< endl;
                    tmpdivisor = di;
                    count = 0;
                }
                else
                    break;
            }
        }
        if(res > INT_MAX) res = negflag ? INT_MAX+1: INT_MAX;
        return (negflag ? -res : res);
    }
};