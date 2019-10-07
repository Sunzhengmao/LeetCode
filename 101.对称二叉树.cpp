/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] 对称二叉树
 */

// @lc code=start
//Definition for a binary tree node.
#include <cstdlib>
#include <cmath>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    bool leftisnull(TreeNode * root) {return (root->left==NULL)&&(root->right!=NULL);}
    bool rightisnull(TreeNode* root) {return (root->left!=NULL)&&(root->right==NULL);}
    bool islastone(TreeNode* root) 
    {
        if (root==NULL) return true;
        if ((root->right==NULL)&&(root->left==NULL)) return true;
        return false;
    }
    bool islasttwo(TreeNode* root) {return islastone(root->left)||islastone(root->right);}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) 
    {// try diedai
        if ((root->left == NULL)||(root->right == NULL))//baseline
        {
            return 
        }
        else//loop
        {
            return isSymmetric(root->left)&&isSymmetric(root->right);
        }
    }

    void change(TreeNode * root)
    {
        if (root->islasttwo)
        {
            TreeNode* tmp = root->left;
            root->left = root->right;
            root->right = tmp;
        }
        else
        {
            change(root->right);
            change(root->left);
        }
        
        
    }
};
// @lc code=end

