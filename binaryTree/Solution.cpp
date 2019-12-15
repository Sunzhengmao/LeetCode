#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
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
        if (!root->left && !root->right) return {to_string(root->val)};

        vector<string> result={};
        vector<string> left = _257_binaryTreePaths(root->left);
        vector<string> right = _257_binaryTreePaths(root->right);

        for (int i = 0; i < left.size(); i++)
            result.push_back(to_string(root->val) + "->" + left[i]);
        for (int j = 0; j < right.size(); j++)
            result.push_back(to_string(root->val) + "->" + right[j]);

        return result;      
    }

//============================================================================================================
    //112、给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
    //(1)这样虽然能够实现，但是速度和内存消耗大，不划算
    bool _112_hasPathSum_lower(TreeNode* root, int sum) 
    {
        if (!root) return false;
        vector<int> value = _112_sub(root);
        for (int i = 0; i < value.size(); i++)
        {
            if (sum==value[i]) return true;
        }
        return false;      
    }
    //112题的子程序，可以帮助计算一个vector
    vector<int> _112_sub(TreeNode* root)
    {
        if (!root) return {};
        if (!root->right && !root->left) return {root->val};
        vector<int> result;
        vector<int> left = _112_sub(root->left);
        vector<int> right = _112_sub(root->right);
        for (int i = 0; i < left.size(); i++)
            result.push_back(root->val + left[i]);
        for (int j = 0; j < right.size(); j++)
            result.push_back(root->val + right[j]);
        return result;        
    }

    //(2)试一下有没有别的方法，果然还有更快的
    bool _112_hasPathSum_new(TreeNode* root, int sum) 
    {
        if (!root) return false;
        if (!root->right && !root->left) return sum==root->val;//如果左子树和右子树都没有
        return _112_hasPathSum_new(root->left, sum-root->val) + _112_hasPathSum_new(root->right, sum-root->val);
    }

//====================================================================================================================
    //108、将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。即每个节点的左右两个子树的高度差的绝对值不超过1。
    //(1)这样的方法也算是迭代，但是vector的复制导致时间变长，而且浪费空间
    TreeNode* _108_sortedArrayToBST_low(vector<int>& nums) 
    {
        if(nums.empty()) return NULL;
        if(nums.size()==1) return (new TreeNode(nums[0]));
        int median = nums.size()/2;
        TreeNode* root = new TreeNode(nums[median]);
        vector<int> leftOne(nums.begin(), nums.begin()+median);
        vector<int> rightOne(nums.begin()+median+1, nums.end());
        root->left = _108_sortedArrayToBST_low(leftOne);   
        root->right = _108_sortedArrayToBST_low(rightOne);
        return root;             
    }
    //(2)试试别的大佬的方法
    TreeNode* _108_sortedArrayToBST_fast(vector<int>& nums)
    {
        return helpme(nums, 0, nums.size() - 1);        
    }
    TreeNode* helpme(vector<int>& nums, int left, int right)
    {   
        if (left > right) return NULL;
        int median = left + ((right - left) >> 1);
        TreeNode* root = new TreeNode(nums[median]);
        root->left = helpme(nums, left, median-1);
        root->right = helpme(nums, median+1, right);
        return root;
    }

//============================================================================================================
    //107、给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
    vector<vector<int>> _107_levelOrderBottom(TreeNode* root) 
    {
        if(!root) return {};
        if(!root->left && !root->right) return {{root->val}};//没有子树

        vector<vector<int>> result={};
        vector<int> tmp={};
        vector<TreeNode*> curr={root};
        vector<TreeNode*> next={};
        while(!curr.empty())
        {
            for(int i=0; i<curr.size(); i++)
            {
                tmp.push_back(curr[i]->val);
                if(curr[i]->left) next.push_back(curr[i]->left);//如果curr[i]的左右子树都非空
                if(curr[i]->right) next.push_back(curr[i]->right);
            }
            result.insert(result.begin(), tmp);
            tmp = {};
            curr = next;
            next = {};
        }
        return result;
    }

//===============================================================================================================
    //111、给定一个二叉树，找出其最小深度。
    int _111_minDepth(TreeNode* root) 
    {
        if(!root) return 0;
        if(!root->left && !root->right) return 1;
        return max(_111_minDepth(root->left), _111_minDepth(root->right));
        // return max(1,0);
    }

//===============================================================================================================
    //404、计算给定二叉树的所有左叶子之和。
    int _404_sumOfLeftLeaves(TreeNode* root) 
    {
        if(!root) return 0;
        if(root->left && !root->left->left && !root->left->right) //如果有左叶子，就返回0咯
            return root->left->val + _404_sumOfLeftLeaves(root->left) + _404_sumOfLeftLeaves(root->right);
        return _404_sumOfLeftLeaves(root->right) + _404_sumOfLeftLeaves(root->left);
    }
};

int main()
{
    Solution* solution;
    vector<string> test = {"1", "2", "3", "null", "4"};
    TreeNode* test_output = solution->initialTreeNode(test);

    // test 257
    vector<string> vec_257 = {"1","2","3","null","5"};
    TreeNode* root_257 = solution->initialTreeNode(vec_257);
    vector<string> result_257 = solution->_257_binaryTreePaths(root_257);

    //test 108
    vector<int> vec_108 = {-10,-3,0,5,9};
    TreeNode* root_108 = solution->_108_sortedArrayToBST_fast(vec_108);

    //test 404
    vector<string> vec_404 = {"3","9","20","null","null","15","7"};
    TreeNode* root_404 = solution->initialTreeNode(vec_404);
    int result_404 = solution->_404_sumOfLeftLeaves(root_404);

    return 1;
}