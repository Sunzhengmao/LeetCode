#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
#include <set>
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
                i++;

                if (i<vec.size()) 
                {
                    if(vec[i]!="null") 
                    {
                        right = new TreeNode(stoi(vec[i]));
                        copyFatherNode.push_back(right);
                        fatherNode[j]->right = right;
                    }                    
                }
                else break;
                i++;                
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

//==============================================================================================================
    //236、给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
    //(1)先找出所有的路径，再找符合条件的
    TreeNode* _236_lowestCommonAncestor_allPath(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if(!root) return NULL;
        vector<vector<TreeNode*> > path = binaryTreePaths(root);
        vector<vector<TreeNode*> > pq={};
        bool ifbreak = false;
        for (int i = 0; i < path.size(); i++)
        {
            for (int j = 0; j < path[i].size(); j++)
            {
                if (path[i][j]->val == p->val || path[i][j]->val == q->val)
                {
                    vector<TreeNode*> tmp(path[i].begin(), path[i].begin()+j+1);
                    if (pq.empty())
                    {
                        pq.push_back(tmp);
                    }
                    else if((*(pq[0].end()-1))->val!=tmp[tmp.size()-1]->val)
                    {
                        pq.push_back(tmp);
                        ifbreak=true;
                        break;
                    }
                }
            }
            if(ifbreak) break;
        }
        int i=0,j=0;
        while (pq[0][i]->val==pq[1][j]->val)
        {
            i++;
            j++;
        }
        return pq[0][i-1];
        
    }
    vector<vector<TreeNode*> > binaryTreePaths(TreeNode* root) 
    {
        if (root==NULL) return {};
        if (!root->left && !root->right) return {{root}};

        vector<vector<TreeNode*> > result={};
        vector<vector<TreeNode*> > left = binaryTreePaths(root->left);
        vector<vector<TreeNode*> > right = binaryTreePaths(root->right);

        for (int i = 0; i < left.size(); i++)
        {
            left[i].insert(left[i].begin(), root);
            result.push_back(left[i]);
        }
        for (int j = 0; j < right.size(); j++)
        {
            right[j].insert(right[j].begin(), root);
            result.push_back(right[j]);
        }

        return result;      
    }

    //(2)用递归的思想会更简单一些
    TreeNode* _236_lowestCommonAncestor_digui(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (!root) return nullptr;
        if (root==p || root==q) return root;
        TreeNode* left = _236_lowestCommonAncestor_digui(root->left, p, q);
        TreeNode* right= _236_lowestCommonAncestor_digui(root->right, p, q);
        //如果left为空，则返回右边；
        //如果left不为空，则返回(right == nullptr? left : root)
        //                      right为空则返回left
        //                      right不为空，则返回root
        return left == nullptr? right : (right == nullptr? left : root); 
    }

//===========================================================================================
    //94、二叉树的中序遍历
    vector<int> _94_midOrder(TreeNode* root)
    {
        if(!root) return {};
        return _94_midOrder(root->left);
        cout<<root->val<<endl;
        return _94_midOrder(root->right);
    }

//===========================================================================================
    //337、计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。
    int _337_rob(TreeNode* root) 
    {
        //感觉我这里一大部分在处理只有两层时候的情况
        if(!root) return 0;
        if(!root->left && !root->right) return root->val;//左右子树都没有             
        if(root->right && root->left)//如果左右子树有值，但左右子树的子树没值
        {
            if((!root->right->left && !root->right->right) && (!root->left->left && !root->left->right))
            {
                int a = root->left ? root->left->val : 0;
                int b = root->right ? root->right->val : 0;
                return max(root->val, a+b);
            }
        }
        if (root->right && !root->left)
        {
            if(!root->right->left && !root->right->right)
                return max(root->val, root->right->val);            
        }
        if (root->left && !root->right)
        {
            if(!root->left->left && !root->left->right)
                return max(root->val, root->left->val);
        }      

        //这里才是递归的核心嘛，然后要注意隔着一层进行取的时候要判断隔的那一层是不是NULL
        int tmp1 = root->left? (_337_rob(root->left->left) + _337_rob(root->left->right)) : 0;
        int tmp2 = root->right? (_337_rob(root->right->left) + _337_rob(root->right->right)) : 0;
        int num1 = root->val + tmp1 + tmp2;
        int num2 = _337_rob(root->left) + _337_rob(root->right);
        return max(num1, num2);
    }

//==========================================================================================================
    //114、给定一个二叉树，原地将它展开为链表。
    void _114_flatten(TreeNode* root) 
    {
        if(!root) return ;
        
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

    //test 236
    vector<string> vec_236 = {"3","5","1","6","2","0","8","null","null","7","4"};
    vector<string> p_236 = {"5","6","2","null","null","7","4"};
    vector<string> q_236 = {"1","0","8"};
    TreeNode* root_236 = solution->initialTreeNode(vec_236);
    TreeNode* p_tree = solution->initialTreeNode(p_236);
    TreeNode* q_tree = solution->initialTreeNode(q_236);
    TreeNode* result_236 = solution->_236_lowestCommonAncestor_allPath(root_236, p_tree, q_tree);

    //test 94
    vector<string> vec_94 = {"1", "null", "2", "3"};
    TreeNode* root_94 = solution->initialTreeNode(vec_94);
    vector<int> result_94 = solution->_94_midOrder(root_94);

    //test 337
    vector<string> vec_337 = {"2","1","3","null","4"};
    TreeNode* root_337 = solution->initialTreeNode(vec_337);
    int result_337 = solution->_337_rob(root_337);


    return 1;
}