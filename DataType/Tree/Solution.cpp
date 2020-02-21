#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

//树的结构可以用很多种形式来表示，但是最方便的还是二叉链的形式，但是注意二叉链与二叉树是不一样的
template<typename T>
struct TreeNode
{
    TreeNode(T value_):value(value_),leftChild(NULL), rightSibling(NULL) {};
    T value;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightSibling;
};



class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();
};

Solution::Solution(/* args */)
{
}

Solution::~Solution()
{
}

int main()
{

    return 1;
}