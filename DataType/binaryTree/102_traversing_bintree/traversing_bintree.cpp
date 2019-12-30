#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// Defination of Struct of treenode
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    queue<TreeNode*> empty;
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        queue<TreeNode*> currentNode, nextNode;
        currentNode.push(root);
        vector<vector<int>> result;
        while (!currentNode.empty())
        {
            bfs(currentNode, nextNode, result);
        }
        return result;        
    }
private:
    void bfs(queue<TreeNode*>&currentN, queue<TreeNode*>& nextN, vector<vector<int>>& result)//这里老忘记&
    {
        vector<int> layerNum;
        while (!currentN.empty())
        {
            TreeNode* tmp = currentN.front();
            if(tmp->right) nextN.push(tmp->right);
            if(tmp->left)  nextN.push(tmp->left);
            layerNum.push_back(tmp->val);
            currentN.pop();
        }
        result.push_back(layerNum);
        swap(currentN, nextN);
        swap(nextN, empty);
    }
};
