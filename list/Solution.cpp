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
    void initial(vector<int> nums, ListNode* head)
    {
        head->val = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            ListNode* NewNode = new ListNode(nums[i]);
            head->next = NewNode;
            head = head->next;
        }
    }

//====================================================================================================================
    //83、给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
    ListNode* _83_deleteDuplicates(ListNode* head) 
    {
        int tmp = 0;//记录每个head的值
        if(head==NULL || head->next==NULL) return head;

        //想原地修改list的值，发现如果直接修改head，返回的就是修改后的，但是如果修改他的copy版，就没有办法固定到head来，还是要看看别人写的
        //发现我想错了，直接把head的地址赋给copy版，然后对copy版进行修改，最后返回head就行
        for(ListNode* iteration=head; iteration->next!=NULL; )//如果head空，证明head的上一个是最后一个了
        {
            tmp = iteration->val;//把当前的value给tmp
            if(iteration->next->val==tmp)//如果重复了，就删掉head->next
                iteration->next = iteration->next->next;//先把下一个给拿出来，再把下一个的下一个给了head的下一个，就把head的下一个给删掉了
            else
                iteration = iteration->next;
        }
        return head;

        /*那我试一下新建一个list
        int tmp=head->val;//放每个listnode的value
        ListNode* result;
        vector<int> something={tmp};
        for(int num=1; head->next!=NULL; num++)//顺便num为计数工具
        {
            head = head->next;
            if(tmp!=head->val)//如果不同的话，tmp才会更新，同时被放入something
            {
                tmp = head->val;
                something.push_back(tmp);
            }
        }
        initial(something, result);
        return result;*/
    }

//===================================================================================================================
    //206、反转一个单链表
    ListNode* _206_reverseList(ListNode* head) 
    {
        vector<int> something;//放head的每个元素吧
        ListNode* result;
        int num=0;
        for(; head!=NULL; num++)
        {
            something.insert(something.begin(), head->val);
            head=head->next;
        }
        initial(something, result);
    }
};




int main()
{
    cout<<"hello world"<<endl;

    Solution* solution;
    vector<int> input = {1,1,1,2};
    ListNode* output = new ListNode(1);
    solution->initial(input, output);

    //test 83
    ListNode* output83 = solution->_83_deleteDuplicates(output);

    //test 206
    vector<int> input206_ = {1,2,3,4,5};
    ListNode* input206;
    solution->initial(input206_, input206);
    ListNode* output206 = solution->_206_reverseList(input206);

    return 1;
}