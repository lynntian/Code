#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;


void maxSubArray(vector<int>& in, int N, long& cSum, long& ncSum)
{
    if(N <= 0 || in.size() == 0 ) return;

    long maxSoFar = (long)in[0];
    long maxHere = (long)in[0];
    long curMax = LONG_MIN;
    cSum = ncSum = 0;
    for(int a = 0; a < N; a ++)
    {
        long i = in[a];
        curMax = max(curMax, i);

        if(i >= 0)
        {
            ncSum += i;
        }

        if( a != 0)
        {
            maxHere = max(i, maxHere + i);
            maxSoFar = max(maxHere, maxSoFar);
        }

    }

    if(curMax < 0)
    {
        ncSum = curMax;
    }
    cSum = maxSoFar;

}

int main() {
   
    int T;
    cin >> T;
    for(int i=0; i < T; i++)
    {
        int N;
        cin >> N;
        auto v = vector<int>(N, 0);
        for(int j=0; j < N; j++)
        {
            cin >> v[j];
        }
        long cSum;
        long ncSum;

        maxSubArray(v, N, cSum, ncSum);
        cout << cSum << " " << ncSum << endl;

    }
    return 0;
}
