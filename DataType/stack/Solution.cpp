#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
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
        if(n<=2) return n;
        vector<int> tmp(n,1);
        tmp[1]=2;
        for(int i=2; i<n; i++)
            tmp[i]=tmp[i-1]+tmp[i-2];
        return tmp[n-1];        
    }

//===========================================================================================================
    //1249、给你一个由 '('、')' 和小写字母组成的字符串s，你需要从字符串中删除最少数目的 '(' 或者 ')' 
    //      可以删除任意位置的括号，使得剩下的「括号字符串」有效。
    string _1249_minRemoveToMakeValid(string s) 
    {
        stack<char> sign = {};
        stack<int> location = {};
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                sign.push(s[i]);
                location.push(i);
                continue;
            }
                
            if (s[i] == ')')
            {
                if (!sign.empty())//若非空，证明里面有东西，所以不用动
                {
                     sign.pop();
                     location.pop();
                }
                else //里面没东西，需要删除
                {
                    s.erase(s.begin()+i);
                    i--;
                }
            }
        }
        while (!sign.empty())
        {
            s.erase(s.begin()+location.top());
            location.pop();
        }
        return s;
    }

//======================================================================================================================
    //1190、请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。注意，您的结果中 不应 包含任何括号。
    string _1190_reverseParentheses(string s) 
    {
        stack<int> start = {};
        stack<int> need_deleted = {};
        for (int i = 0; i < s.size(); i++)
        {
            if(s[i] == '(')
            {
                start.push(i);
                need_deleted.push(i);
            }
            if(s[i] == ')')
            {
                reverse(s.begin()+start.top()+1, s.begin()+i);
                start.pop();
                s.erase(s.begin()+i);
                s.erase(s.begin()+need_deleted.top());
                need_deleted.pop();
                i = i - 2;
            }
        }
        return s;
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

    //test 1249
    string s_1249 = "lee(t(c)o)de)";
    string output_1249 = solution->_1249_minRemoveToMakeValid(s_1249);

    //test 1190
    string s_1190 = "(abcd)";
    string s_1190_2 = "(ed(et(oc))el)";
    string output_1190 = solution->_1190_reverseParentheses(s_1190_2);


    return 1;
}
