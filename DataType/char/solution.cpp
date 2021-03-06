#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
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

//======================================================================================================
    //415、给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。
    string addStrings(string num1, string num2) 
    {
        int num1Point = num1.size() - 1;
        int num2Point = num2.size() - 1;
        int num= num2Point;//最长的那个有多少个
        string output=num2;//装最长的那个
        if(num1Point >= num2Point)
        {
            num = num1Point;
            output = num1;
        }
        int shiwei = 0;
        int gewei = 0;
        int result = 0;
        while (num>=0)
        {
            result = (num1Point>=0? num1[num1Point]-'0':0) + (num2Point>=0? num2[num2Point]-'0':0) + shiwei;
            gewei = result>9? result%10 : result;
            shiwei= result>9? result/10 : 0;
            output[num] = gewei+'0';
            num1Point--;
            num2Point--;   
            num--;     
        }
        if(shiwei!=0)
            output.insert(0,to_string(shiwei));
        return output;       
    }

//=========================================================================================================================
    //767、给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。若可行，输出任意可行的结果。若不可行，返回空字符串。
    string _767_reorganizeString(string S) 
    {
        int fastPoint = 0;
        // bool fastcanStop = false;
        for (int lowPoint = 0; lowPoint < S.size(); lowPoint++)
        {
            if(S[lowPoint] != S[lowPoint+1])//如果不相等，满足条件
            {
                continue;
            }
            if (lowPoint+2<=S.size())//到了倒数第二个，就不往后走了
            {
                bool fastcanStop = false;
                for (fastPoint = lowPoint+2; fastPoint < S.size(); fastPoint++)
                {
                    
                    if(S[lowPoint] != S[fastPoint])
                    {
                        swap(S[lowPoint+1], S[fastPoint]);
                        fastcanStop = true;
                        break;
                    }                    
                }
                if(fastcanStop==false)//里面遍历完了，没找到不一样的，就证明已经失败了
                    return "";
                
            } 
            else
            {
                // if(S[lowPoint] == S[lowPoint+1])//如果不相等，满足条件
                return "";
            }
              
        }
        return S;
    }
};


int main()
{
    Solution* solution;

    //test 344
    vector<char> s={'h','e','l','l','o'};
    solution->_344_reverseString(s);

    //test 415
    string num1_415="401716832807512840963";
    string num2_415="167141802233061013023557397451289113296441069";
    string output_415 = solution->addStrings(num1_415, num2_415);

    //test 767
    string S = "aaab";
    string output767 = solution->_767_reorganizeString(S);


    return 1;
}