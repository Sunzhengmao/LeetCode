#include <iostream>
#include <list>
#include <vector>
#include <map>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
//=====================================================================================================================
    ListNode *initial(vector<int> nums, ListNode* head)
    {
        // ListNode *root = new ListNode(nums[0]);
        // ListNode *tmp = root->next;
        for (int i = 0; i < nums.size(); i++)
        {
            ListNode* NewNode = new ListNode(nums[i]);
            head->next = NewNode;
            head = head->next;
        }
    }
//=====================================================================================================================
    //206、反转一个单链表。
    ListNode* _206_reverseList(ListNode* head) 
    {
        map<int, int> tmp;
        for (int i = 0; head!=NULL; i++)
        {
            int num = head->val;
            tmp.insert(make_pair(i,num));
            head = head->next;
        }
            
        
        
    }
};




int main()
{
    cout<<"hello world"<<endl;

    Solution* solution;
    vector<int> input = {1,2,3,4,5};
    ListNode* output = new ListNode(0);
    solution->initial(input, output);

    return 1;
}