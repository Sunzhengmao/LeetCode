#include <vector>
#include<iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) 
    {
        // if(t1==NULL && t2==NULL)//baseline:如果两个都是空就别
        //     return NULL;
        // if(t1==NULL)//不用再新建一个Node
        //     return t2;
        // if(t2==NULL)
        //     return t1;
        // else
        // {
        //     t1->val += t2->val;
        //     t1->left = mergeTrees(t1->left, t2->left);//直接把新的值进行赋值给t1的下一个，也不用新建
        //     t1->right = mergeTrees(t1->right, t2->right);
        //     return t1;
        // }

        //这次试一下新建Node的方法
        if(t1==NULL && t2==NULL)//如果全为空就返回空
            return NULL;
        if(t1==NULL || t2==NULL)//如果有一个为空没关系，加完之后返回就行
            return t1 ? t1 : t2 ;
        else
        {
            TreeNode* t3 = new TreeNode(t1->val + t2->val);//如果是node指针就需要new一些，如果只是node就直接构造好了
            t3->left = mergeTrees(t1->left, t2->left);
            t3->right = mergeTrees(t1->right, t2->right);
            return t3;
        }
        
        
            
        
        
    }
};