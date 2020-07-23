#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <list>
#include <queue>
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

//4、给定两个大小为m和n的有序数组nums1和nums2。请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
    double _4_findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        //还是没有自己想出来答案，找中位数的：分成两个数量相等的子集，且一个子集的所有值都小于另一个子集
        //这里面一个很棒的思想：[2,3,5] -> [#,2,#,3,#,5] ; (1-1)/2=0,1/2=0,怎么着都是2；(4-1)/2=1,4/2=2,这样是2和3之间
        int n = nums1.size();
		int m = nums2.size();

		if (n > m)  //保证数组1一定最短
			return _4_findMedianSortedArrays(nums2, nums1);

		// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
		int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度

		while (lo <= hi)   //二分
		{
			c1 = (lo + hi) / 2;  //c1是二分的结果
			c2 = m + n - c1;

			LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
			RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
			LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
			RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

			if (LMax1 > RMin2)
				hi = c1 - 1;
			else if (LMax2 > RMin1)
				lo = c1 + 1;
			else
				break;
		}
		return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;   
    }

//215、在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
    int _215_findKthLargest_force(vector<int>& nums, int k) 
    {
        //利用暴力解法，分治排序之后，找到第k大的值

    }

    int _215_findKthLargest_steak(vector<int>& nums, int k)
    {        
        //利用堆的方式，大堆顶，得用树的结构
        int result = 0;
        int numSize = nums.size();
        if (numSize==0 || k>numSize)
            return 0;

        priority_queue<int, vector<int>, greater<int>> store;
        //堆中维持k个最大的数      
        for (int i = 0; i < numSize; i++)
        {
            store.push(nums[i]);
            if (store.size() > k)
            {
                store.pop();
            }
        }
        return store.top();
    }

    int _215_findKthLargest_select(vector<int>& nums, int k)
    {
        int result = 0;
        int numsSize = int(nums.size());
        if (numsSize == 0 || k > numsSize)
        {
            return 0;
        }
        //寻找第kMIN小的数
        int kMin = numsSize - k + 1;
        result = select(nums, 0, numsSize - 1, kMin);
        return result;
    }
    //找出来第target小的值
    int select(vector<int>& nums, int left, int right, int target)
    {
        if (left == right)
        {
            return nums[left];
        }
        int cut = partition(nums, left, right);
        //当前第currentResult小的元素
        int cut_index = cut - left + 1;
        if (target == cut_index)
        {
            return nums[cut];
        }
        else if (target < cut_index)
        {
            return select(nums, left, cut - 1, target);
        }
        else
        {
            //寻找接下来第target - currentResult小的数
            return select(nums, cut + 1, right, target - cut_index);
        }
        return 0;
    }
    //以最右边那个值为基准，开始将这个数放到他该去的位置上，左边都是小于他的，右边都是大于他的，返回他现在的位置，以示他是第几小
    int partition(vector<int> &nums, int left, int right)
    {
        int cut = nums[right];
        //i代表大于cut的值，j代表小于cut的值
        //一旦j找到了比cut大的，就把i留在那里，然后j继续去找比cut小的，找到了就和i交换，找不到没关系，反正到最后还要交换
        int i = left;
        for (int j = left; j < right; j++)
        {
            if (nums[j] <= cut)//比cut小的交给i管，然后i++。进行下一个
            {
                exchange(nums[i], nums[j]);
                i++;
            }
        }
        exchange(nums[i], nums[right]);
        return i;
    }
    void exchange(int &a, int &b)
    {
        int tmpInt = a;
        a = b;
        b = tmpInt;
    }

};

int main()
{
    Solution* solution;

    //test 53
    vector<int> nums_53 = {-1,-2};
    int result_53 = solution->_53_maxSubArray(nums_53);

    //test 4
    vector<int> nums1_4 = {1,7,8,9,10};
    vector<int> nums2_4 = {2,3,4,5,6};
    double result_4 = solution->_4_findMedianSortedArrays(nums1_4, nums2_4);

    //test 215
    vector<int> nums_215 = {10,3,9,1,8,4,7,2,5};
    int result_215 = solution->_215_findKthLargest_select(nums_215, 1);
    return 1;
}