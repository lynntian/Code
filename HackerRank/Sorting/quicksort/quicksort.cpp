#include <iostream>
#include <vector>

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

void helper(vector<int>& arr)
{
    auto size = arr.size();
    if(size <= 1) return;

    auto p = arr[0];
    auto v1 = vector<int>();
    auto v2 = vector<int>();
    for(int i = 1; i < size; i++)
    {
        if(arr[i] > p) v2.push_back(arr[i]);
        else v1.push_back(arr[i]);
    }
    if(v1.size() > 1)
    {
        helper(v1);
        printArr(v1);
    }
    if(v2.size() > 1) 
    {
        helper(v2);
        printArr(v2);
    }
    
    arr.clear();
    arr.insert(arr.end(), v1.begin(), v1.end());
    arr.push_back(p);
    arr.insert(arr.end(), v2.begin(), v2.end());

}

void quickSort(vector <int> &arr) {

    auto size = arr.size();
    if(size == 0 ) return;
    helper(arr);
    
}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);
    printArr(arr);
    return 0;
}
