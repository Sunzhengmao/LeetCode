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

    // map<char, int> count;
    // for (int i = 0; i < s_451.size(); i++)
    // {
    //     count[s_451[i]]++;
    // }

    // vector<pair<char, int>> count_vector(count.begin(), count.end());
    // sort(count_vector.begin(), count_vector.end(), [](pair<char, int>& i, pair<char, int>& j){return (i.second<j.second);});


}