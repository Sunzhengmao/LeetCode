#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 //Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    int maxDepth(TreeNode* root) 
    {
        //直接暴力递归
        if (root==NULL)
            return 0;
        return max(maxDepth(root->right), maxDepth(root->left))+1;

        //DFS，朝着一个方向遍历到最深处
        if(root==NULL) return 0;
        int L = maxDepth(root->left) + 1;//返回左子树的最大深度，加上1才是深度值
        int R = maxDepth(root->right) + 1;
        return L>R?L:R;         
    }
};