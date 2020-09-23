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
    ListNode *_160_getIntersectionNode_hash(ListNode *headA, ListNode *headB) 
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

    //这个代码是真的简洁啊，直接用?:就可以了，只是内存消耗有点高
    ListNode* _160_getIntersectionNode_doublePointer(ListNode* headA, ListNode* headB)
    {
        if(headA==NULL || headB==NULL) return NULL;
        ListNode* pA = headA;
        ListNode* pB = headB;
        while(pA != pB)
        {
            pA = pA==NULL ? headB : pA->next;
            pB = pB==NULL ? headA : pB->next;
        }
        return pA;
    }

//============================================================================================================
    //203、删除链表中等于给定值 val 的所有节点。
    ListNode* _203_removeElements(ListNode* head, int val) 
    {
        while(head && head->val==val)//删头结点中与val相同的值
            head=head->next;
        ListNode* result=head;
        if(!result) return result;
        while(head->next)
        {
            if(head->next->val==val)//如果相等证明这个head->next要被删除
                head->next=head->next->next;
            else
                head=head->next;
        }
        return result;
    }   

//===========================================================================================================
    //61、给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
    ListNode* _61_rotateRight_nishizhen(ListNode* head, int k) 
    {
        vector<int> tmp;
        ListNode* headTmp=head;
        int num=0;
        long int j = k;
        bool Ucan=true;
        while (headTmp)
        {
            num++;
            headTmp=headTmp->next;

            //num>k大说明在一遍之内就可以完成，不用取余，就算取余了也是0，就别浪费时间了
            //num=k也没关系，会退出的，j=0，
            //num<k小就用取余，num是一个一个加的，如果没加到k就不会执行下面的，就得取余了
            if(num > k)
            {
                Ucan=false;
                break;
            }
        }
        if(Ucan)
            j = k % num;


        //构建两个链表，前j个放到新链表(laterOne)，后面(former)num-j个遍历出最后一个来，把前j个接到最后一个上面，
        ListNode* result = new ListNode(head->val);
        ListNode* laterOne = head;
        ListNode* laterOne_last = NULL; 
        ListNode* former = NULL;
        ListNode* former_last = NULL;
        head=head->next;
        int i=2;
        while(head)
        {
            if(i<=j)
            {
                // ListNode* newNode = new ListNode(head->val);
                // result->next = newNode;
                // result=result->next;
                laterOne_last = head;
                head=head->next;
                i++;
            }
            else
            {
                if(i==j+1)//取出来结果的头指针
                {
                    former=head;
                    i++;
                }    
                former_last=head;//存former指针的最后一个指针，如果是最后一个就直接退出了
                head=head->next;
            }            
        }
        laterOne_last->next=NULL;
        former_last->next = laterOne;
        return former;
    }

//==============================================================================================================
    //61、给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
    ListNode* _61_rotateRight_shunshizhen(ListNode* head, int k) 
    {
        if(!head) return head;
        ListNode* headTmp=head;
        int num=0;
        bool Ucan=true;
        while (headTmp)
        {
            num++;
            headTmp=headTmp->next;

            //num>k大说明在一遍之内就可以完成，不用取余，就算取余了也是0，就别浪费时间了
            //num=k也没关系，会退出的，j=0，
            //num<k小就用取余，num是一个一个加的，如果没加到k就不会执行下面的，就得取余了
            if(num > k)
            {
                Ucan=false;
                break;
            }
        }
        if(Ucan)
            k = k % num;
        ListNode* b=head;
        ListNode* a=head;
        int i=0;
        // while(b)
        // {   
        //     if(k)
        //     {
        //         b=b->next;
        //         k--;
        //         break;
        //     }
        //     a=a->next;
        //     b=b->next;
        // }
        while(b->next)
        {
            b=b->next;
            if(k<=0)
                a=a->next;
            k--;
        }
        b->next=head;
        ListNode* result = a->next;
        a->next=NULL;
        return result;
    }

//==============================================================================================================
    //24、给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。不能单纯改变节点内部的值，而是需要实际的进行节点交换。
    ListNode* _24_swapPairs(ListNode* head) 
    {
        if(!head->next || !head) return head;
        head = swapTwoNode(head);
        ListNode* result = head;
        while (head->next->next)
        {
            head->next->next = swapTwoNode(head->next->next);
            head = head->next->next;
        }
        return nullptr;
    }
    ListNode* swapTwoNode(ListNode* head)
    {
        if(!head || !head->next) return head;
        ListNode* temp = new ListNode(head->val);//当前这个
        ListNode* head2 = head->next;            //下一个
        temp->next = head2->next;
        head2->next = temp;
        return head2;
    }

//=======================================================================================================
    //141、给定一个链表，判断链表中是否有环
    bool _141_hasCycle(ListNode *head) 
    {
        if(!head) return false; 
        ListNode* lowAddr = head;
        ListNode* fastAddr = head->next;
        while(head && lowAddr!=fastAddr)
        {
            head = head->next;
            lowAddr = lowAddr->next;
            fastAddr = fastAddr->next->next;
            if(!lowAddr || !fastAddr) return false;
        }
        if(lowAddr==fastAddr) return true;
        else return false;
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
    ListNode* result = solution->_160_getIntersectionNode_doublePointer(headA, headB);

    //test 203
    vector<int> head_203={1,1,2};
    ListNode* head203 = solution->initial(head_203);
    ListNode* output203 = solution->_203_removeElements(head203, 1);

    //test 61
    vector<int> head_61={1,2,3,4,5};
    ListNode* head61 = solution->initial(head_61);
    ListNode* ouput61 = solution->_61_rotateRight_shunshizhen(head61, 2);
    
    //test 24
    vector<int> head_24={1,2,3,4};
    ListNode* head24 = solution->initial(head_24);
    ListNode* output24 = solution->_24_swapPairs(head24);

    //test 141
    vector<int> head_141 = {1,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4};
    ListNode* head141 = solution->initial(head_141);
    bool output141 = solution->_141_hasCycle(head141);

    return 1;
}