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
    int diameterOfBinaryTree(TreeNode* root) 
    {
        if(!root) return 0;
        int result1 = max(diameterOfBinaryTree(root->right), diameterOfBinaryTree(root->left));
        return max(result1, maxDepth(root->left)+maxDepth(root->right));    
    }

    int maxDepth(TreeNode* root) 
    {
        //DFS，朝着一个方向遍历到最深处
        if(root==NULL) return 0;
        int L = maxDepth(root->left) + 1;//返回左子树的最大深度，加上1才是深度值
        int R = maxDepth(root->right) + 1;
        return L>R?L:R;         
    }
};