#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool canBeRearranged(vector<string>& in, int a, int b, int N, char& c)
{
    if(a < 0 || b < 0 || a >= N || b >= N)
    {
        return true;
    }

    auto tmp = in[a].at(b);
    //cout << "Current a, b, c: " << a << ", " << b << ", " << tmp << endl; 
    if( tmp < c) return false;
    
    return canBeRearranged(in, a+1, b, N, tmp);  //&& canBeRearranged(in, a+1, b, N, tmp);
}

bool helper(vector<string>& in, int N)
{
    for(int i =0; i < N; i++)
    {
        if (! canBeRearranged(in, 0, i, N, in[0].at(i)))
            return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;

    for(int i = 0; i < T; i ++)
    {
        int N;
        cin >> N;
        auto in =  vector<string>(N, "");
        for(int j = 0; j < N; j++)
        {
            string tmp;
            cin >> tmp;
            sort(tmp.begin(), tmp.end());
            in[j] = tmp;
        }

        if(helper(in, N))
        {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }  
    return 0;
}
