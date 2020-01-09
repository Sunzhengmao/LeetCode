#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <list>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//53、给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
    int _53_maxSubArray(vector<int>& nums)//[-2,1,-3,4,-1,2,1,-5,4]
    {
        //初步思路：利用分治，把nums从中间分开，左右采取不同的判断策略，然后考虑到连续，还需要考虑从断开的那里连着最大的情况，一共三种
        if(nums.size()==0) return 0;
        if(nums.size()==1) return nums[0];//写两个基，分治到这种程度就没法再分治了

        int size = nums.size();
        int middle = (size & 1) ? (size-1)/2 : size/2;//是奇数，就是前面，否则是后面
        int sum_right = 0, sum_left = 0;
        int max_right = 0, max_left = 0;
        for (int i = middle+1; i < nums.size(); i++)
        {   
            sum_right += nums[i];
            if(sum_right > max_right)
                max_right = sum_right;
        }
        for (int j = middle-1; j >= 0; j--)
        {
            sum_left += nums[j];
            if(sum_left > max_left)
                max_left = sum_left;            
        }
        int sum = nums[middle] + max(max_left, 0) + max(max_right, 0);
        vector<int> num_left(nums.begin(), nums.begin()+middle);
        vector<int> num_right(nums.begin()+middle+1, nums.end());
        int last_two = max(_53_maxSubArray(num_left), _53_maxSubArray(num_right));
        return max(last_two, sum);
}


};

int main()
{
    Solution* solution;

    //test 53
    vector<int> nums_53 = {-1,-2};
    int result_53 = solution->_53_maxSubArray(nums_53);
    return 1;
}