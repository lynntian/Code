#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution{
    public:
        static int countPrimes(int n) {
        std::vector<bool> map(n-1, false);
        map[0] = true;
        int currentIndex = 2-1;
        int upBound = sqrt(n)+1;
        cout<< "Up bound " << upBound << endl;
        while( currentIndex <= upBound)
        {
            cout<< "Current Index " << currentIndex << endl;
            if(map[currentIndex]) {
                currentIndex++;
                cout << "Continued" << endl;
                continue;
            }
            int temploop = currentIndex*2 +1;
            while(temploop < n-1 )
            {
                cout<< "Temp loop " << temploop << endl;
                map[temploop] = true;
                temploop += currentIndex+1;           
            }
            currentIndex++;
        }
        int count = 0;
        int i = 0;
        while(i < n-1)
        {
            if(!map[i])
            {
                count++;
            }
            i++;
        }
        return count;
    }


};

int main()
{
    cout << "Result " << Solution::countPrimes(13) << endl;

    return 0;
}


