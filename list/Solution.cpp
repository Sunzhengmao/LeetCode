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
        // head->val = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            ListNode* NewNode = new ListNode(nums[i]);
            head->next = NewNode;
            head = head->next;
        }
    }

    //在有了指针的理解后重新写一个initial的函数
    ListNode* initial(vector<int> nums)
    {
        ListNode* head = new ListNode(nums[0]);
        ListNode* result = head;
        for(int i=1; i!=nums.size(); i++)
        {
            ListNode* tmpNode = new ListNode(nums[i]);
            head->next = tmpNode;
            head = head->next;
        }
        return result;
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
    }

    ListNode* _83_deleteDuplicates_newlist(ListNode* head) 
    {
        //那我试一下新建一个list
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
        return result;
    }

//===================================================================================================================
    //206、反转一个单链表
    ListNode* _206_reverseList(ListNode* head) 
    {
        vector<int> something;//放head的每个元素吧
        while(head)
        {
            something.insert(something.begin(), head->val);
            head=head->next;
        }
        return initial(something);
    }

    //又有一个新想法，我可不可以每次都往list的前面插值
    ListNode* _206_reverseList_insert(ListNode* head)
    {
        ListNode* result = new ListNode(head->val);
        head = head->next;
        while(head)
        {
            ListNode* tmp = new ListNode(head->val);
            tmp->next = result;
            result = tmp;
            head=head->next;
        }
        return result;
    }

//===================================================================================================================
    //160、编写一个程序，找到两个单链表相交的起始节点。
    //先试一下哈希表的方法吧
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        map<int,int> mapA,mapB;
        ListNode* result=NULL;//只要加上这么一个初始化就不会出现result的第一个val瞎搞了
        int numA=0;
        int numB=0;
        while(headA!=NULL)
        {
            numA++;
            mapA[numA]=headA->val;
            headA=headA->next;
        }
        while(headB)
        {
            numB++;
            mapB[numB]=headB->val;
            headB=headB->next;
        }   
        while(mapA[numA]==mapB[numB])//最后返回的是第一个不满足的numA
        {
            ListNode* newNode = new ListNode(mapB[numB]);
            newNode->next = result;
            result=newNode;
            numA--;
            numB--;
        }
        return result;
    }
};


int main()
{
    cout<<"hello world"<<endl;

    Solution* solution;
    // 第一种初始化方法
    vector<int> input = {1,1,1,2};
    ListNode* output = new ListNode(1);
    solution->initial(input, output);

    // 第二种初始化方法
    vector<int> input1 = {1,4,3,2,5};
    ListNode* output1 = solution->initial(input1);

    //test 83
    ListNode* output83 = solution->_83_deleteDuplicates(output);

    //test 206
    vector<int> input206_ = {1,2,3,4,5};
    ListNode* input206 = solution->initial(input206_);
    ListNode* output206 = solution->_206_reverseList(input206);
    ListNode* output206_= solution->_206_reverseList_insert(input206);

    //test 160
    vector<int> headA_ = {4,1,8,4,5};
    vector<int> headB_ = {5,0,1,8,4,5};
    ListNode* headA = solution->initial(headA_);
    ListNode* headB = solution->initial(headB_);
    ListNode* result = solution->getIntersectionNode(headA, headB);

    return 1;
}