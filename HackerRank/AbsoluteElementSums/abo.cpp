#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool binarySearchLastNegative(vector<long long int>& v, int start, int end, int& index, int key) // last index that's lower than key value
{
    //cout << "start: " << start << " end: " << end << endl;
    if(start < 0 || end > v.size() || start > end) return false;
    if(start == end && v[end] < key)
    {
        index = start;
        return true;
    }

    auto mid = start + (end - start) / 2;
    //cout << "mid: " << mid << endl;
    if(v[mid] >= key )
    {
        return binarySearchLastNegative(v, start, mid -1, index, key);
    }
    else
    {
        if(!binarySearchLastNegative(v, mid + 1, end,index, key))
        {
            index = mid;
        }
        return true;
    }
}

bool binarySearchPositive(vector<long long int>& v, int start, int end, int& index, int key) // first index that's larger than key
{
    //cout << "start: " << start << " end: " << end << endl;
    if(start < 0 || end > v.size() || start > end) return false;
    if(start == end && v[end] > key)
    {
        index = start;
        return true;
    }

    auto mid = start + (end - start) / 2;
    //cout << "mid: " << mid << endl;
    if(v[mid] > key )
    {
        if(! binarySearchPositive(v, start, mid -1, index, key))
        {
            index = mid;
        }
        return true;
    }
    else // <= 0
    {
        return binarySearchPositive(v, mid + 1, end,index,key);
    }

}

void prefixSum(vector<long long int>& in, vector<long long int>& out)
{
    long long int tmp = 0;
    out.clear();
    for(auto& i : in)
    {
        tmp += i;
        out.push_back(tmp);
    }
}

void absSum_Improved(vector<long long int>& v, vector<int>& qv, int N )
{
    sort(v.begin(), v.end());
    auto prefixSumV = vector<long long int>();
    prefixSum(v, prefixSumV);

    long long int cumQ = 0;
    long long int newSum = 0;
    for(auto& q : qv)
    {
        cumQ+= q;

        auto pos = lower_bound(v.begin(), v.end(), -cumQ) - v.begin();

        if(pos > 0)
        {
            newSum = prefixSumV[N-1] - prefixSumV[pos -1] + cumQ * (N-pos) - prefixSumV[pos-1] - cumQ * pos;
        }
        else
        {
            newSum = prefixSumV[N-1] + cumQ * N;
        }

        printf("%lld\n", newSum);
    }
}

void absSum(vector<long long int>& v, vector<int>& qv, int N, int Q, long long int sum )
{
    sort(v.begin(), v.end());
    auto countFlipSign = 0;
    long long int diffSum = 0;
    //for each q in qv
    for(auto& q: qv)
    {
        if(q != 0)
        {
            for(auto& n : v)
            {
                if(abs(q) >= abs(n)) 
                {
                    countFlipSign++;
                    diffSum += abs(n+q) - abs(n);
                }
                n += q;

            }
        }
  
        if(q > 0 )
        {
            auto index = 0;
            if(binarySearchLastNegative(v, 0, N, index, 0) )
            {
                sum -= q * (index + 1);
                sum += q * (N - (index+1 + countFlipSign));

            }
            else // all positive
            {
                sum += q * (N - countFlipSign);
            }
            sum += diffSum;
        }
        else if( q < 0)
        {
            auto index = 0;
            if(binarySearchPositive(v, 0, N, index, 0))
            {
                sum += (-q) * (index - countFlipSign);
                sum -= (-q) * (N - index);
            }
            else // all negative
            {
                sum += (-q) * (N-countFlipSign);
            }
            sum += diffSum;
        }

        printf("%lli\n", sum);
        //printf("/n");
        
        countFlipSign = 0;
        diffSum = 0;

    }
}

int main()
{
    int N;
    cin >> N;
    auto v = vector<long long int>(N, 0);
    long long int sum = 0;
    for(int i = 0; i < N; i++)
    {
        scanf( "%lld", &v[i]);
        sum += abs(v[i]);
    }
    int Q;
    cin >> Q;
    auto qv = vector<int>(Q, 0);
    for(int j = 0; j< Q; j++)
    {
        scanf("%d",  &qv[j]);
    }

    absSum_Improved(v, qv, N);

    return 0;
}