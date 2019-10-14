#include<vector>
#include<iostream>
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
    //纪念一下，第一次刚写完就可以跑通的代码，只是没有优化，太垃圾了
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) 
    {
        if(nums.size()>1000 || nums.size()<1) return NULL;

        vector<int> result = getMaxNum(nums);
        int max = result[0], index = result[1];
        vector<int> left,right;
        TreeNode* root = new TreeNode(max);//construct new node
        for(int i=0;i<index;i++) left.push_back(nums[i]);//左边的数组
        for(int j=index+1;j<nums.size();j++) right.push_back(nums[j]);
        root->left=constructMaximumBinaryTree(left);//构建root的左子树
        root->right=constructMaximumBinaryTree(right);
        return root;
    }
    
    vector<int> getMaxNum(vector<int>& nums)
    {
        int max = 0;
        int index = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if(nums[i] > max) 
            {
                max = nums[i];
                index = i;
            }
        }
        vector<int> result={max, index};
        return result;
    }
};

int main()
{
    vector<int> a = {0,1,2,3,4,5,6,7,8,9,10};//size本身包含的容量，capacity是有多少能力来扩大容量，
    a.resize(5);
    for (size_t i = 0; i < a.size(); i++)
    {
        cout<<a[i]<<", ";
    }
    

}