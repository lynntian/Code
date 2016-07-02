#include <iostream>
#include <cmath>
using namespace std;
    
bool isPowerOfFour(int num) {
    if(num <= 0) return false;
    return (num > 0) && ((num & (num-1)) == 0) && (num & 0x55555555);
}


int main()
{
    while(true)
    {
        cout << "Input number: " ;
        int in;
        cin >> in;
        cout << "power of 4 ? " << isPowerOfFour(in) << endl; 
    }

    return 0;
}

// 4^0 = 1 -> 1
// 4^1 = 4 -> 100
// 4^2 = 16 -> 10000
// 4^3 = 64 -> 1000000