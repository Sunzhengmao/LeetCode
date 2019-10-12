 #include <vector>
 #include<iostream>
 #include<queue>
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
    bool isBalanced(TreeNode* root) 
    {
        if(root==NULL) return true;
        if(root->left==NULL && root->right==NULL) return true;
        if(root->left==NULL || root->right==NULL) return getHeight(root)<=2;
        return (abs(getHeight(root->right) - getHeight(root->left))<=1)&&isBalanced(root->left)&&isBalanced(root->right);        
    }
    int getHeight(TreeNode* root)
    {
        int height = 0;
        queue<TreeNode*> currNode, nextNode;
        currNode.push(root);
        while (!currNode.empty())
        {
            bfs(currNode, nextNode, height);
        }
        return height;
        
    }

    void bfs(queue<TreeNode*>& currN, queue<TreeNode*>& nextN, int& height)
    {
        if (!currN.empty()) height++;
        while (!currN.empty())
        {
            TreeNode* tmp = currN.front();
            if(tmp->left) nextN.push(tmp->left);
            if(tmp->right) nextN.push(tmp->right);
            currN.pop();
        }
        swap(currN, nextN);
        queue<TreeNode*> empty;
        swap(nextN, empty);        
    }
};