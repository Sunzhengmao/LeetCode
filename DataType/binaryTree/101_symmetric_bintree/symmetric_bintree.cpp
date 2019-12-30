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
    // 2019.10.4 我都不想看我自己写的好垃圾哦，不过也是我第一次做二叉树
    // bool isSymmetric(TreeNode* root) 
    // {// try diedai
    //     if ((root->left == NULL)||(root->right == NULL))//baseline
    //     {
    //         return 
    //     }
    //     else//loop
    //     {
    //         return isSymmetric(root->left)&&isSymmetric(root->right);
    //     }
    // }

    // 我的主要失败在：
    // 1、没找好迭代的思路，一开始想着把这左右两边的全部换一下，然后再和原来的对比，
    //    可这本来就是个简单题，搞得很复杂
    // 2、change的时候baseline也没找好，baseline是最简单的情况，只需针对最简单的
    //    情况进行分析就行了
    // void change(TreeNode * root)
    // {
    //     if (root->islasttwo)
    //     {
    //         TreeNode* tmp = root->left;
    //         root->left = root->right;
    //         root->right = tmp;
    //     }
    //     else
    //     {
    //         change(root->right);
    //         change(root->left);
    //     }
    // }

    //参考别人的思路简单的
    //先考虑baseline，最终的结果无非就是N+N，N+number，number+N，number+number，只要有不相等的
    //就直接返回false；有相等的就要考虑下是base case还是recursive cases。全是number就要继续递归，
    //否则就结束。
    bool ismirror(TreeNode* root1, TreeNode* root2)
    {
        if (root1==NULL && root2==NULL)//给出了结束的base case
            return true;
        if (root1==NULL||root2==NULL)//给出了错误的base case
            return false;        
        return (root1->val==root2->val)&&ismirror(root1->left, root2->right)&&ismirror(root1->right, root2->left);
    }
};  