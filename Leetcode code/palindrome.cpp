#include <iostream>
#include <vector>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    static bool isPalindrome(ListNode* head) {
        if(!head) return true;
        auto tmp = head;
        int len=0;
        while(tmp)
        {
            tmp = tmp->next;
            len++;
        }
        tmp = head;
        ListNode* last = nullptr;
        bool isEven = len % 2 == 0;
        
        for( int i = 0; i< len/2; i++)
        {
            auto next = tmp->next;
            tmp->next = last;
            last = tmp;
            tmp = next;
        }
        auto newHead = tmp;
        tmp = last;
        if(!isEven)
        {
            newHead = newHead->next;
            
            cout << "New head: " << newHead->val << endl;
        }

        while(newHead && tmp)
        {
            cout << "New head: " << newHead->val << endl;
            cout << "Tmp : " << tmp->val << endl;
            if(newHead->val != tmp->val)
            {
                return false;
            }
            newHead = newHead->next;
            tmp = tmp->next;
        }
        return true;
    }

    static ListNode* buildLL(vector<int> arr)
    {
        auto head = new ListNode(arr[0]);
        auto tmp = head;
        auto len = arr.size();
        for(int i =1 ; i< len; i++)
        {
            tmp->next = new ListNode(arr[i]);
            tmp = tmp->next;
        }
        return head;
    }

};

int main()
{
    vector<int> arr2 = {2,1};
    auto head = Solution::buildLL(arr2);
    cout << "Result: " << Solution::isPalindrome(head) << endl;
    cout << endl;
    vector<int> arr = {0,1,2,3};
    head = Solution::buildLL(arr);
    cout << "Result: " << Solution::isPalindrome(head) << endl;
    cout << endl;
    vector<int> arr1 = {1,2,2,1};
    head = Solution::buildLL(arr1);
    cout << "Result: " << Solution::isPalindrome(head) << endl;

    return 1;
}