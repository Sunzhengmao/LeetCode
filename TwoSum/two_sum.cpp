/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        vector<int> result(2,-1);
        map<int, int> hash;
        for (int i=0; i<nums.size(); i++)
        {
            int value = target - nums[i];
            if(hash.count(value)==0)//not find
            {
                hash[value] = i;
            }
            else
            {
                result[0]=i;
                result.push_back(hash[value]);
                return result;
            }
        }
        return result;        
    }
};

int main()
{
    Solution solution;
    vector<int> nums, output;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(20);
    int target = 9;
    output = solution.twoSum(nums, target);
    cout<<output.at(0)<<","<<output.at(1)<<endl;
    return 0;
}
// @lc code=end

