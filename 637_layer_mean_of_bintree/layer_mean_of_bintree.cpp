#include <vector>
#include <iostream>
#include <queue>
using namespace std;

 // Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution
{
    public:
    queue<TreeNode*> empty;
    vector<double> averageOfLevels(TreeNode* root) 
    {
        queue<TreeNode*> currentNode,nextNode;
        currentNode.push(root);
        vector<double> average;
        while (!currentNode.empty())
        {
            bfs(currentNode, nextNode, average);
        }
        return average;    
    }
    private:
    void bfs(queue<TreeNode*>& currentN, queue<TreeNode*>& nextN, vector<double>& result)
    {
        double sum = 0;
        int num = 0;
        while (!currentN.empty())
        {
            num++;//进行一次就加一
            TreeNode* element = currentN.front();
            sum += element->val;//get the first element to sum
            if (element->left)  nextN.push(element->left);
            if (element->right) nextN.push(element->right);
            currentN.pop();//delete the first element
        }
        result.push_back(sum / num);
        currentN = nextN;
        swap(nextN, empty);
    }
};

int main()
{
    double sum=0.0;
    int num=2.0;
    cout<<(sum+29)/num<<endl;
    return 1;
}