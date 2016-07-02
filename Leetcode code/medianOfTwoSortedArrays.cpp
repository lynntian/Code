/*
Median of two sorted arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

*/

// Solution1 merge and count
/*
class Solution {
public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        auto l1 = nums1.size();
        auto l2 = nums2.size();
        if(l1 ==0 ||l2 ==0) return -1;

        int medianIndex = (l1+l2 -1) / 2;
        bool even = ((l1+l2) % 2) == 0;
        int m1 = -1;
        int m2 = -1;
        cout << "median index: " << medianIndex << " isEven: " << even << endl;

        int a = 0; int b = 0;
        for(int i = 0; i < l1 + l2; i++)
        {
            auto cur = 0;
            if(a < l1 || b < l2)
            {
                cur = nums1[a] <= nums2[b] ? nums1[a++] : nums2[b++];
            }
            else if(a == l1)
            {
                cur = nums2[b++];
            }
            else if(b == l2)
            {
                cur = nums1[a++];
            }

            if(i == medianIndex)
            {
                m1 = cur;
            }
            if(even && i == medianIndex +1 )
            {
                m2 = cur;
            }
        }
        return even ? ((m1+ m2)/2.0) : m1;
    }
};
*/

//solution 2 
//find median for each array, depending on the result of median recursively look for sub array median

