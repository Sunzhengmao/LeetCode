//  Definition for a binary tree node.
#include <stdlib.h>
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        if (root==NULL)  return NULL;
        TreeNode* tmp = root->right;
        root->right = root->left;
        root->left = tmp;//把void转换成有返回值的函数，因为if那里需要返回一个东西，然后else写之前void
        invertTree(root->right);//想写的，最后再递归一下，分三个部分了
        invertTree(root->left);       
    }

    // 递归是不能有无返回值的函数的，这样将导致有去无回，所以这样是失败的
    void changeTree(TreeNode* root1, TreeNode* root2)
    {
        if (root1==NULL && root2==NULL)
        {
            
        }
        else
        {
            changeTree(root1->left, root2->right);
            changeTree(root1->right, root2->left);
        }
        
        
    }
};