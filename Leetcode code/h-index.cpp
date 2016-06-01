class Solution {
public:
    static bool compare(int a, int b)
    {
        return a > b;
    }
    int hIndex(vector<int>& citations) {
        auto l = citations.size();
        if(l == 0) return 0;

        //sort array in reverse order
        sort(citations.begin(), citations.end(), compare);
        int i = 0;
        for(; i<l; i++)
        {
            if(citations[i] < i+1)
                break;
        }
        return i;

    }
};