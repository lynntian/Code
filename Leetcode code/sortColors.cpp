class Solution {
public:
    void sortColors(vector<int>& nums) {
        auto size = nums.size();
        if(!size || size == 1) return;

        //Two pointers
        auto l = 0; auto h = size-1;
        auto m = 0;
        while(m <= h )
        {
            if(nums[m] == 0 )
            {
                nums[m] = nums[l];
                nums[l] = 0;
                l++;
                m++;
            }
            else if(nums[m] == 1) m++;
            else if(nums[m] == 2)
            {
                if(m == h) break;
                nums[m] = nums[h];
                nums[h] = 2;
                h--;
            }
        }

/*
        //Count sort
        auto c0 = 0; auto c1 = 0; auto c2 = 0;
        for(auto& n : nums)
        {
            if(n == 0) c0++;
            else if(n==1) c1++;
            else if(n==2) c2++;
        }

        for(auto& n:nums)
        {
            if(c0) {n = 0; c0--;}
            else if(c1) {n =1; c1--;}
            else if(c2) {n = 2; c2--;}
        }
*/
//        //merge sort
//        auto res = merge(nums, 0, size-1, size);
//        nums = res;
    }

    vector<int> merge(vector<int>&nums, int start, int end, int size)
    {
        auto res = vector<int>();
        if(start <0 || end >= size || end < start) return res;
        if(end == start)
        {
            cout << nums[end] << endl;
            res.push_back(nums[end]);
            return res;
        }
        auto mid = (end - start) / 2 + start;
        auto v1 = merge(nums, start, mid, size);
        auto v2 = merge(nums, mid+1, end, size);

        int i =0; int j =0 ;
        int sv1 = v1.size(); int sv2 = v2.size();
        cout << "sv1 " << sv1 << " sv2 " << sv2 << endl;
        while(i < sv1 || j < sv2)
        {
            if(i < sv1 && j < sv2)
            {
                cout << "v1: " << v1[i] << " i"  << i << endl;
                cout << "v2: " << v2[j] << " j"  << j << endl;
                cout <<"pushback: " << (v1[i] > v2[j] ? v2[j] : v1[i]) << endl;
                res.push_back(v1[i] > v2[j] ? v2[j++] : v1[i++]);
            }
            else if( i< sv1)
            {
                cout << "i: " << v1[i] << endl;
                res.push_back(v1[i++]);
            }
            else if( j< sv2)
            {
                cout << "j: " << v2[j] << endl;
                res.push_back(v2[j++]);
            }
        }
        return res;
    }
};