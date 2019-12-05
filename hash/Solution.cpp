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

    return 1;
}