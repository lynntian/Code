#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
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

void printArr(int ar_size, int *  ar)
{
   for(int i = 0; i < ar_size; i++)
   {
        cout << ar[i];
        if(i != ar_size -1)
            cout << " ";
   }
   cout << endl;
}

void insertionSort_EXAMPLE(int N, int arr[]) {
    int i,j;
    int value;
    for(i=1;i<N;i++)
    {
        value=arr[i];
        j=i-1;
        while(j>=0 && value<arr[j])
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=value;
    }
    for(j=0;j<N;j++)
    {
        printf("%d",arr[j]);
        printf(" ");
    }
}

void insertionSortPartial(int*  ar, int start, int end, int ar_size) {

    if(end <= start || end <= 0 || start < 0) return;

    auto last = ar[end];
    int lastIndex = end;
    int i = end -1; 

    while(i >= start)
    {
        if(last < ar[i])
        {
            ar[lastIndex] = ar[i];
            lastIndex--;
            //printArr(ar);
        }
        else
        {
            ar[i+1] = last;
            break;
        }

        i--;
    }

    if(i == start -1)
    {
        ar[start] = last;
    }
    printArr(ar_size, ar);

}

void insertionSort(int ar_size, int *  ar) {
    if(ar_size  <= 1 ) return;

    int curIndex = 1;
    auto cur = ar[0];
    while(curIndex <= ar_size -1)
    {
        insertionSortPartial(ar, 0, curIndex, ar_size);
        curIndex ++;
    }

}

int main(void) {
    int _ar_size;
    cin >> _ar_size;
    //scanf("%d", &_ar_size);
    int _ar[_ar_size], _ar_i;
    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
        cin >> _ar[_ar_i];
        //scanf("%d", &_ar[_ar_i]); 
    }

   insertionSort(_ar_size, _ar);
   
   return 0;
}
