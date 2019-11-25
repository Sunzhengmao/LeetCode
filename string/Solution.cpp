#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <stack>
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

//======================================================================================================
    //1221、给出一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。
    int _1221_balancedStringSplit(string s) 
    {
        if(s.size()<=1) return 0;
        stack<char> tmp;
        int result=0;
        for (int i = 0; i < s.size(); i++)
        {
            if(tmp.empty())
            {
                result++;
                tmp.push(s[i]);
                continue;
            }
            char some = tmp.top();
            if((some=='L'&&s[i]=='R') || (some=='R'&&s[i]=='L'))//如果匹配上
                tmp.pop();
            else
                tmp.push(s[i]);
        }
        return result;        
    }

//=============================================================================================================
    //394、编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
    string _394_decodeString(string s) 
    {
        int len = s.size();
        int num = 0;
        stack<int> numstack;
        stack<string> strstack;
        string cur = "";
        string result = "";
        for(int i=0; i<len; ++i)
        {
            if(s[i]>='0' && s[i]<='9')
            {
                num = 10*num + s[i] - '0';
            }
            else if(s[i] == '[')
            {
                numstack.push(num);
                strstack.push(cur);
                num = 0;
                cur.clear();
            }
            else if((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'))
                cur += s[i];
            else if(s[i] == ']')
            {
                int k = numstack.top();
                numstack.pop();
                for(int j=0; j<k; ++j)
                    strstack.top() += cur;
                cur = strstack.top();
                strstack.pop();
            }
        }
        result = result + cur;
        return result;     
    }

//========================================================================================================
    //443、给定一组字符，使用原地算法将其压缩。
    int _443_compress(vector<char>& chars) 
    {
        stack<char> tmp;
        int num=0;
        for (vector<char>::iterator iter = chars.begin(); iter != chars.end(); iter++)
        {
            if(tmp.empty())
            {
                tmp.push(*iter);
                continue;
            }   

            if(tmp.top() == (*iter))
            {
                num++;
                iter = chars.erase(iter);
                continue;
            }
            char num_char = num + '0';
            chars.insert(iter, num_char);
            num=0;
        }
        
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

    //test 1221
    string s1221 = "LRLRLR";
    int output1221 = solution->_1221_balancedStringSplit(s1221);

    //test 394
    string tack = "hhh";
    string t = "sss";
    string a = tack + t[0];
    string s394 = "3[a]2[bc]";
    string s394_inner = "3[ab2[cd2[e]]]mm";
    string output394 = solution->_394_decodeString(s394_inner);


    return 1;
}