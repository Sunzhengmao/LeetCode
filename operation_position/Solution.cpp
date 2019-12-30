#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//========================================================================================================
    //136、给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
    int _136_singleNumber_lowest(vector<int>& nums) 
    {
        if(nums.size()==1) return nums[0];
        vector<int> something = {};
        for (int i = 0; i < nums.size(); i++)
        {
            if (something.empty())
            {
                something.push_back(nums[i]);
                continue;
            }
            
            for (int j = 0; j < something.size(); j++)
            {
                if(nums[i]==something[j])//相等就证明要删除
                {
                    something.erase(something.begin()+j);
                }
            }
        }
        return something[0];       
    }
     
    
    //尼玛，位操作简直神了
    int _136_singleNumber_yihuo(vector<int> & nums)
    {
        int ret = 0;
        int len = nums.size();
        for (int i = 0; i < len; i++)
        {
            ret = nums[i]^ret;
        }
        return ret;
    }

//======================================================================================================
    //169、给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
    int _169_majorityElement_1(vector<int>& nums) 
    {
        map<int, int> count={};
        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
            if(count[nums[i]]>nums.size()/2)
                return nums[i];
        }        
        return 0;
    }

    int _169_majorityElement_2(vector<int>& nums) 
    {
        map<int, int> count={};
        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
        }        
        for (map<int, int>::iterator it = count.begin(); it != count.end(); it++)
        {
            if (it->second > nums.size()/2)
            {
                return it->first;
            }
        }
        return 0;
    }
};

int main()
{
    Solution *solution;

    // test 136
    vector<int> nums_136 = {4,1,2,1,2};
    int result_136 = solution->_136_singleNumber_yihuo(nums_136);
    
    // test 169
    vector<int> nums_169 = {3,2,2};
    int result_169 = solution->_169_majorityElement(nums_169);

    return 0;
}
