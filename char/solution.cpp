#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//=======================================================================================================
    //344、编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 char[] 的形式给出。且必须原地修改
    void _344_reverseString(vector<char>& s) 
    {
        if(s.size()<=1) return;
        int left=0;
        int right=s.size()-1;
        while (left<right)
        {
            swap(s[left], s[right]);
            left++;
            right--;
        }       
    }
};


int main()
{
    Solution* solution;

    //test 344
    vector<char> s={'h','e','l','l','o'};
    solution->_344_reverseString(s);


    return 1;
}