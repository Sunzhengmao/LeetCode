#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//这里完全是参考别人的代码，用的后序遍历法，然后找规律
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        flatten(root->left);
        flatten(root->right);
        if (root->left != nullptr) {
            auto pre = root->left;
            while (pre->right != nullptr) pre = pre->right;
            pre->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        root = root->right;
        return;
    }

    TreeNode* generateBintree(int index, vector<int> nums)
    {
        TreeNode* root = new TreeNode(nums[0]);
        return root;

    }

    void bfs(queue<int> lastLayer, vector<int> thisLayer, int layerNum)
    {
        for(int i = pow(2,))
    }
};