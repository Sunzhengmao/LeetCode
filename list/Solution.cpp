#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
//=====================================================================================================================
    //创建一个新链表
    ListNode *initial(vector<int> nums)
    {
        ListNode *root = new ListNode(nums[0]);
        for(int i=0; i!=nums.size(); i++)
        {
            root->val = nums[i];
            root = root->next;
        }
    }
//=====================================================================================================================
    //160、编写一个程序，找到两个单链表相交的起始节点。
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        map<int, int> temp;
        int i = 0;
        while (headA)
        {
            temp.insert(i, headA->val);
            headA = headA->next;
        }
        return headA;       
        
    }
};

int main()
{
    Solution solution;
    //test 160
    ListNode input160 
}

 