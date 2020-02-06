#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Solution
{
private:
    
public:
    Solution(/* args */);
    ~Solution();

// 746. 使用最小花费爬楼梯,爬不需要费体力，停下来需要消耗体力
    int _746_minCostClimbingStairs(vector<int>& cost) 
    {
        if (cost.size() <= 2) return 0;

        const int N = cost.size();
        int result = cost[N-1];

        for (int i = N-2; i >= 1; i--)
        {
            if (cost[i-1] <= cost[i])
            {
                result += cost[i-1];
                i--;
            }
            else
            {
                result += cost[i];
            }
        }
        return result;   
    }

    int _746_minCostClimbingStairs_key(vector<int>& cost)
    {
        int c1 = cost[0];
        int c2 = cost[1];
        int c3 = 0;
        int N = cost.size();
        for (int i = 2; i < N; ++i) 
        {
            c3 = min(c1, c2) + cost[i];
            c1 = c2;
            c2 = c3;
        }
        return min(c1, c2);
    }

//5、给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
    string _5_longestPalindrome(string s) 
    {
        const int N = s.size();
        if(N <= 1) return s;

        int maxLen_ = 0;
        string maxPali = "";

        for (int i = 0; i < N; i++)
        {
            for (int j = N-1; j >= i; j--)
            {
                if (j-i+1 < maxLen_)
                    continue;
                if(isPalindrome(s, i, j))
                {
                    if (j-i+1 > maxLen_)
                    {
                        maxLen_ = j-i+1;
                        maxPali = strcopy(s,i,j+1);  
                    }
                }      
            }
        }
        return maxPali;        
    }

    bool isPalindrome(string& s, int begin, int end)
    {
        if (end < begin)  return false;

        while (end > begin) 
        {
            if (s[begin]!=s[end])
                return false;

            end--;
            begin++;
        }
        return true;
    }
    string strcopy(string& src, int begin, int end)
    {
        if (end < begin) return "";

        string result = "";
        
        for (int i = begin; i < end; i++)
        {
            result.push_back(src[i]);
        }

        return result;
    }
};



int main()
{
    Solution* solution;

    //test 746
    vector<int> cost_746 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    int result_746 = solution->_746_minCostClimbingStairs_key(cost_746);

    string s_5 = "cbbd";
    string result_5 = solution->_5_longestPalindrome(s_5);

    return 1;
}