#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//===============================================================================================================
    //20、给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
    bool _20_isValid_szm(string s) 
    {
        if(s.empty()) return true;
        stack<char> tmp;
        for(int i=0; i<s.size(); i++)
        {
            if(tmp.empty())
            {
                tmp.push(s[i]);
                continue;
            }
            char cha = tmp.top();
            int match = Matching(cha,s[i]);
            if(match==1)
                {tmp.pop();continue;}
            if(match==2)
                {tmp.push(s[i]);continue;}
            if(match==3)
                return false;
        }
        if(tmp.empty())
            return true;
        else 
            return false;
    }

    int Matching(char a, char b)
    {
        if((a=='(')&&(b==')') || (a=='[')&&(b==']') || (a=='{')&&(b=='}'))//刚好配对
            return 1;
        else
        {
            if((a=='(')&&((b=='}')||(b==']')) || (a=='[')&&((b==')')||(b=='}')) || (a=='{')&&((b==')')||(b==']')))//反向不匹配
                return 3;
            else //同向不匹配
                return 2;
        }
    }

//=============================================================================================================
    //20、我试一下陈子昊的想法
    bool _20_isValid_czh(string s)
    {
        if(s.empty()) return true;
        stack<char> tmp;
        for(int i=0; i<s.size(); i++)
        {
            if(tmp.empty())
            {
                tmp.push(s[i]);
                continue;
            }
            char a = tmp.top();
            if((a=='(')&&(s[i]==')') || (a=='[')&&(s[i]==']') || (a=='{')&&(s[i]=='}'))//刚好匹配
                tmp.pop();
            else 
                tmp.push(s[i]);
        }
        if(tmp.empty())
            return true;
        else 
            return false;
    }

//============================================================================================================
    //70、爬楼梯，感觉这不是栈的想法，而是递归或者别的
    int _70_climbStairs(int n) 
    {
        vector<int> tmp(n,1);
        if(n<=2) return n;
        tmp[1]=2;
        for(int i=2; i<n; i++)
            tmp[i]=tmp[i-1]+tmp[i-2];
        return tmp[n-1];        
    }
};

int main()
{
    Solution* solution;

    //test 20
    string s("()()()");
    bool isRight = solution->_20_isValid_czh(s);

    //test 70
    int output70 = solution->_70_climbStairs(6);


    return 1;
}
