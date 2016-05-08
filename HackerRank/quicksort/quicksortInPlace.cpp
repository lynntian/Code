#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printArr(std::vector<int> vec)
{
    int counter = vec.size();

    for(auto& v : vec)
    {
        cout << v ;
        if(counter != 1)
        {
           cout << " ";
        }
        counter --;
    }
    cout << endl;
}
void swap(vector<int>& arr, int current, int s)
{
    auto tmp = arr[current];
    arr[current] = arr[s];
    arr[s] = tmp;

}

void subroutine(vector<int>& arr, int start, int end, int size)
{
    if(end <= start || end >= size || start < 0 || end <= 0 || start >= size) return ;

    auto firstLarge = -1;
    auto p = arr[end];
    int current = start;
    while(current < end)
    {
        if(arr[current] < p)
        {
            if(firstLarge != -1)
            {
                swap(arr, current, firstLarge);
                firstLarge++;
            }
        }
        else if( arr[current] > p)
        {
            if(firstLarge == -1)
            {
                firstLarge = current;
            }
        }
        current++;
    }

    if(firstLarge!= -1 && firstLarge != end)
    {
        swap(arr, firstLarge, end);
    }
    else
    {
        //all elements smaller than pivot
        firstLarge = end;
    }
    printArr(arr);

    subroutine(arr, start, firstLarge-1, size);
    subroutine(arr, firstLarge+1, end, size);
}

void quicksortInPlace(vector<int>& arr)
{
    auto size = arr.size();
    if(size == 0) return;

    subroutine(arr, 0, size-1, size);
}


int main() {
    int n; 
    cin >> n;
    
    vector<int> arr(n);
    for(int i=0; i < n; i++)
    {
        cin >> arr[i];    
    }
    
    quicksortInPlace(arr);
    
    return 0;
}
