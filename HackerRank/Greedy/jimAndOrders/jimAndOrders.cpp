#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

inline bool comp(const pair<int, int>& a, const pair<int, int>& b)
{
    return a.second < b.second;
}

int main() {

    int N;
    cin >> N;

    auto v = vector<pair<int, int>>();
    for(int i=0; i < N; i++)
    {
        auto p = make_pair(0,0);
        int a;
        int b;
        cin >> a;
        cin >> b;
        p.second = a + b;
        p.first = i+1;
        v.push_back(p);
    } 

    stable_sort(v.begin(),v.end(), comp);

    for(auto x: v)
    {
        cout << x.first << " ";
    }
    cout << endl;

    return 0;
}
