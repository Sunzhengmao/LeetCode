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
    // 所以这里是错的，insert一个元素后，整个vector被复制到新的地址，所以end操作注定失效，但iter可以通过赋值来保证其连续性

    //=========================================补充知识===================================================
    //-- 1.当插入一个元素后，end操作返回的迭代器肯定失效
    //-- 2.当插入一个元素后，capacity若和插入之前相比有改变，则需要重新加载正个容器，此时first和end的操作返回的迭代器都会失效，
    //     如果没有重新分配，那么 插入点之前的迭代器有效，插入点之后的iterator失效
    //-- 3.当进行删除操作后，删除点之前的迭代器有效，指向删除点的全部迭代器失效，指向删除点后面元素迭代器也全部会失效
    int _443_compress(vector<char>& chars) 
    {
        stack<char> tmp;
        int num=1;
        vector<char>::iterator end_ = chars.end()-1;
        int t=0;
        vector<char>::iterator iter = chars.begin();
        for (; iter != chars.end(); iter++)
        {
            t++;
            if(tmp.empty())
            {
                tmp.push(*iter);
                continue;
            }   

            if(tmp.top() == (*iter))
            {
                num++;
                iter = chars.erase(iter);
                // iter--;
                continue;
            }
            tmp.pop();
            char num_char = num + '0';
            // iter--;
            iter = chars.insert(iter, num_char);
            num=0;
        }

        return chars.size();
    }
    
    int _443_compress_right(vector<char>& chars)
    {
                int n=chars.size();
        int i=0;
        //cnt记录结果数组的长度
        int cnt=0;
        while(i<n)
        {
            int j=i+1;
            //该循环实现找到第一个和重复字符不等的位置
            while(j<n&&chars[j]==chars[i])
                j++;
            //加入重复字符
            chars[cnt++]=chars[i];
            int dif=j-i;
            //若需要压缩,则压缩
            if(dif>1)
            {
                //这儿用栈实现整数的位数分解,实际上可以直接用to_string方法来获得每一位的数字
                stack<char> st;
                while(dif)
                {
                    st.push(dif%10+'0');
                    dif/=10;
                }
                while(!st.empty())
                {
                    chars[cnt++]=st.top();
                    st.pop();
                }
            }   
            //让i指向j当前的字符
            i=j;
        }
        return cnt;
    }

//============================================================================================================
    //557、给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
    string _557_reverseWords(string s) 
    {
        stack<char> container;
        string tmp;
        for(int i=0; i<s.size(); i++)
        {
            if (s[i] == ' ') //如果是空格
            {
                while (!container.empty())
                {
                    tmp += container.top();
                    container.pop();
                }
                tmp+=' ';
                continue;
            }
            //如果不是空格，就需要往stack里面加东西
            container.push(s[i]);
        }
        while (!container.empty())
        {
            tmp += container.top();
            container.pop();
        }
        return tmp;
    }

//==================================================================================================================
    //43、给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。
    string _43_multiply(string num1, string num2) 
    {
        if (num1=="0" || num2=="0") return 0;
        if(num1.size() > num2.size()) swap(num1, num2);
        int pow_big = 0;
        vector<string> S_;
        for (int i = num1.size()-1; i >= 0; i--)
        {
            int tmp = 0;
            int shiwei = 0;
            string s_ = "";
            for (int j = num2.size()-1; j >= 0; j--)
            {
                int gewei = (num1[i]-'0') * (num2[j]-'0');
                tmp = gewei % 10 + shiwei;
                shiwei = gewei/10;
                s_.insert(s_.begin(), tmp+'0');
            }
            if(shiwei) s_.insert(s_.begin(), shiwei+'0');
            for(int k=0; k<pow_big; k++)
            {
                s_ += (0 + '0');
            }    
            S_.push_back(s_);   
            pow_big++;
        }
        string result = "";
        int jinwei = 0;
        for (int i = 1; i <= (num1.size()+num2.size()); i++)     
        {   
            int tmp = 0;
            for(auto s : S_)
            {
                int kao = s[s.size()-i]-'0';
                if(kao>=0 && kao<=9)
                    tmp += kao;
            }
            result.insert(result.begin(), (jinwei+tmp)%10 + '0');
            jinwei = (jinwei+tmp)/10;
        }
        if(jinwei) result.insert(result.begin(), jinwei);  
        if(result[0]=='0') 
            result.erase(result.begin());    
        return result;
    }

    string _43_multiply_others(string num1, string num2)
    {
        int n1=num1.size();
        int n2=num2.size();
        string res(n1+n2,'0');
        for(int i=n2-1;i>=0;i--)
        {
            for(int j=n1-1;j>=0;j--)
            {
                int temp=(res[i+j+1]-'0')+(num1[j]-'0')*(num2[i]-'0');
                res[i+j+1]=temp%10+'0';//当前位
                res[i+j]+=temp/10; //前一位加上进位，res[i+j]已经初始化为'0'，加上int类型自动转化为char，所以此处不加'0'
            }
        }
        
        //去除首位'0'
        for(int i=0;i<n1+n2;i++)
        {
            if(res[i]!='0')
                return res.substr(i);
        }
        return "0";
    }

//==================================================================================================================
    //1047、给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
    string _1047_removeDuplicates(string S) 
    {
        int i=0;  // i:lower
        int j=i+1;// j:faster
        for (; i < S.size(); i++)
        {
            j=i+1;
            if(S[i]!=S[j]) continue;
            while(S[i]==S[j])
                j++;
            
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

    //test 443
    vector<char> test443 = {'1','2','3','4','5','6','7','8','9'};
    // for (vector<char>::iterator iter = test443.begin(); iter != test443.end(); iter++)
    // {
    //     iter = test443.erase(iter);
    //     cout<<*iter<<endl;        
    //     cout<<*(test443.end()-1)<<endl;
    //     // iter = test443.insert(iter, ((num++) + '0'));
    //     // iter++;
    //     // cout<<*iter<<endl;        
    //     // cout<<*(test443.end()-1)<<endl;
    // }
    vector<char> chars = {'a','b','c','d','e','f'};
    int size_ = solution->_443_compress(chars);

    // test 557
    string test557 = "Let's take LeetCode contest";
    string output557 = solution->_557_reverseWords(test557);
    int i=1;

    //test 43
    string num1_43 = "999";
    string num2_43 = "999";
    string result43 = solution->_43_multiply(num1_43, num2_43);



    int lastOne = 1;
    return 1;
}