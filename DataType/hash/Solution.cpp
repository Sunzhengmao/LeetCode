#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(pair<char, int>& i, pair<char, int>& j);

class Solution
{
private:
    /* data */
public:
    Solution();
    ~Solution();
    
//========================================================================================
    //217、给定一个整数数组，判断是否存在重复元素。
    bool _217_containsDuplicate(vector<int>& nums) 
    {
        map<int, int> count;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i]>=0)
            {               
                count[nums[i]]++;
                if (count[nums[i]]>1) return true;
                continue;
            }          
            count[nums[i]]--;
            if(count[nums[i]]<-1)  return true;
        }
        return false;
    }

//=======================================================================================
    //451、给定一个字符串，请将字符串里的字符按照出现的频率降序排列。
    string _451_frequencySort(string s) 
    {
        map<char, int> count;
        for (int i = 0; i < s.size(); i++)
        {
            count[s[i]]++;
        }

        vector<pair<char, int>> count_vector(count.begin(), count.end());
        sort(count_vector.begin(), count_vector.end(), [](pair<char, int>& i, pair<char, int>& j) {return (i.second>j.second);});

        string result;
        for (int i = 0; i < count_vector.size(); i++)
        {
            while (count_vector[i].second)
            {
                result += count_vector[i].first;
                count_vector[i].second--;
            }
        }
        return result;
    }

//============================================================================================================
    /*1138、我们从一块字母板上的位置 (0, 0) 出发，该坐标对应的字符为 board[0][0]。
            在本题里，字母板为board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"].
            如果方格存在，'U' 意味着将我们的位置上移一行；如果方格存在，'D' 意味着将我们的位置下移一行；
            如果方格存在，'L' 意味着将我们的位置左移一列；如果方格存在，'R' 意味着将我们的位置右移一列；
            '!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。*/
    string _1138_alphabetBoardPath(string target) 
    {
        char tmp = 'a';
        string result="";
        for (int i = 0; i < target.size(); i++)
        {
            if(target[i]=='z' && tmp!='z')
            {
                int rows = (target[i]-'a')/5 - (tmp-'a')/5; // 第几行
                int cols = (target[i]-'a')%5 - (tmp-'a')%5; // 第几列
                while (cols > 0)
                {
                    result+='R';
                    cols--;
                }
                while (cols < 0)
                {
                    result+='L';
                    cols++;
                }
                while (rows > 0)
                {
                    result+='D';
                    rows--;
                }
                while (rows < 0)
                {
                    result+='U';
                    rows++;
                }
            }
            if (target[i]!='z' && tmp=='z')     
            {
                int rows = (target[i]-'a')/5 - (tmp-'a')/5; // 第几行
                int cols = (target[i]-'a')%5 - (tmp-'a')%5; // 第几列
                while (rows > 0)
                {
                    result+='D';
                    rows--;
                }
                while (rows < 0)
                {
                    result+='U';
                    rows++;
                }
                while (cols > 0)
                {
                    result+='R';
                    cols--;
                }
                while (cols < 0)
                {
                    result+='L';
                    cols++;
                }
            }
            if (target[i]!='z' && tmp!='z')
            {
                int rows = (target[i]-'a')/5 - (tmp-'a')/5; // 第几行
                int cols = (target[i]-'a')%5 - (tmp-'a')%5; // 第几列
                while (rows > 0)
                {
                    result+='D';
                    rows--;
                }
                while (rows < 0)
                {
                    result+='U';
                    rows++;
                }
                while (cols > 0)
                {
                    result+='R';
                    cols--;
                }
                while (cols < 0)
                {
                    result+='L';
                    cols++;
                }
            }
            tmp = target[i];
            result+='!';
        }
        return result;
    }

//========================================================================================================================
    //1048、给出一个单词列表，其中每个单词都由小写英文字母组成。从给定单词列表 words 中选择单词组成词链，返回词链的最长可能长度。
    //      这个最后还是没有答对，我是按照
    int _1048_longestStrChain(vector<string>& words) 
    {
        vector<string> curr={}, pre={};
        int string_size = 0;
        for (int i = 0; i < words.size(); i++)
        {
            //先插进来一个
            if(pre.empty())
            {
                curr.push_back(words[i]);
                while (words[i].size()==words[i+1].size())
                {
                    curr.push_back(words[i+1]);
                    i++;
                }                
            }
            else
            {
                for (int j = 0; j < pre.size(); j++)
                {
                    if (str1_in_str2(pre[j], words[i]))
                    {
                        curr.push_back(words[i]);
                        break;
                    }
                }   
                while (words[i].size()==words[i+1].size())//看看下一个是否长度和当前一样，一样就可以继续判断是否可以加进来
                {
                    for (int j = 0; j < pre.size(); j++)
                    {
                        if (str1_in_str2(pre[j], words[i+1]))
                        {
                            curr.push_back(words[i+1]);
                            break;
                        }
                    }    
                    i++;            
                }
            }
            pre = curr;
            curr = {};
            string_size++;
        }
        return string_size;
    }

    // 检测str1是否在str2中
    bool str1_in_str2(string str1, string str2)
    {
        int j = 0;
        int num = 0;
        for (int i = 0; i < str1.size(); i++)
        {
            for (; j < str2.size(); j++)
            {
                if(str1[i]==str2[j])
                {
                    num++;
                    break;
                }
            }
        }
        return (num==str1.size());
    }

};

int main()
{
    Solution* solution;

    // test 217
    vector<int> nums_217 = {-1200000005,-1200000005};
    bool isRight = solution->_217_containsDuplicate(nums_217);

    // test 451
    string s_451 = "tree";
    string output_451 = solution->_451_frequencySort(s_451);

    // test 1138
    string target_1138 = "leet";
    string output_1138 = solution->_1138_alphabetBoardPath(target_1138);

    // test 1048
    vector<string> words_1048 = {"a","b","bac","bcade","abcdef","abcefg","abcdefg"};
    int result_1048 = solution->_1048_longestStrChain(words_1048);

    return 1;
}