

//perfect square

/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1,4,9,
16,...) which sum to n.
For example, given n = 12, return 3because 12=4+4+4; given n = 13, return 2because
13=4+9.

*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int numSquares(int n)
{
    auto ret = 0;
    if(n <= 0) return ret;
    else if(n == 1) return 1;
    else if(n==2) return 2;


    return ret;
}

int main()
{
    auto tes = {12, 13};
    //Tests:
    for(auto t : tes)
    {
        cout << "Given number " << t << " result: " << numSquares(t) << endl; 
    }
    return 0;
}