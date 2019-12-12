#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
using namespace std;

// Definition for a binary tree node.                          
struct TreeNode                                              
{                                                                   
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

    // 从vector中生成一个TreeNode，可以用来自己验证
    TreeNode* initialTreeNode(vector<string> vec)
    {
        TreeNode* root = new TreeNode(std::stoi(vec[0]));
        vector<TreeNode*> fatherNode = {root};
        vector<TreeNode*> copyFatherNode = {};
        for(int i=1; i<vec.size();)
        {
            for (int j = 0; j < fatherNode.size(); j++)
            {
                TreeNode* left=NULL;
                TreeNode* right=NULL;
                if (i < vec.size())
                {
                    if(vec[i]!="null") 
                    {
                        left = new TreeNode(stoi(vec[i]));
                        copyFatherNode.push_back(left);
                        fatherNode[j]->left = left;
                    }                    
                }
                else break;

                if (i+1<vec.size()) 
                {
                    if(vec[i+1]!="null") 
                    {
                        right = new TreeNode(stoi(vec[i+1]));
                        copyFatherNode.push_back(right);
                        fatherNode[j]->right = right;
                    }                    
                }
                else break;
                i=i+2;                
            }
            fatherNode = copyFatherNode;
            copyFatherNode.clear();          
        }
        return root;
    }

//=======================================================================================================
    //257、给定一个二叉树，返回所有从根节点到叶子节点的路径。
    vector<string> _257_binaryTreePaths(TreeNode* root) 
    {
        if (root==NULL) return {};
        if (!root->left && !root->right)
        {
            return {to_string(root->val)};
        }
        vector<string> result={};
        vector<string> left = _257_binaryTreePaths(root->left);
        vector<string> right = _257_binaryTreePaths(root->right);
        for (int i = 0; i < left.size(); i++)
        {
            result.push_back(to_string(root->val) + "->" + left[i]);
        }
        for (int j = 0; j < right.size(); j++)
        {
            result.push_back(to_string(root->val) + "->" + right[j]);
        }
        return result;      
    }
};

int main()
{
    Solution* solution;
    vector<string> test = {"1", "2", "3", "null", "4"};
    TreeNode* test_output = solution->initialTreeNode(test);

    vector<string> vec_257 = {"1","2","3","null","5"};
    TreeNode* root_257 = solution->initialTreeNode(vec_257);
    vector<string> result_257 = solution->_257_binaryTreePaths(root_257);

    return 1;
}