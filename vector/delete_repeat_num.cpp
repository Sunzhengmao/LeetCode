#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    //26、去除数组中重复的数字，并返回最后结果的数组个数，这里只能除去一些按照顺序排列的数组，
    //    主要应用了快指针和满指针来减小空间复杂度
    int _26_removeDuplicates(vector<int>& nums) 
    {   //size_type抽象意义是尺寸单位类型
        if(nums.size()<=1) return nums.size();
        //定义快指针i(已定义)和慢指针p
        vector<int>::size_type p=1;
        for(vector<int>::size_type i=1; i!=nums.size(); i++)
        {
            if(nums[i]!=nums[i-1]) //如果这一项不等于前一项，则放到慢指针中去，并加一
            {
                nums[p]=nums[i];
                p++;
            }
        }
        return p;
    }

    //912、给定一个整数数组 nums，将该数组升序排列
    vector<int> _912_sortArray(vector<int>& nums) 
    {   
        
    }

//======================================================================//
    //189、给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
    void _189_rotate(vector<int>& nums, int k) 
    {
        //题目要求只能使用O（1）空间复杂度的东西，所以我就只能增加时间了
        if(k%nums.size()==0) return;
        // int firstOne = nums[0];
        if(k<nums.size()/2)
        {
            for(vector<int>::size_type i=nums.size()-1; i!=0; i--)
            {
              int tmp = nums[i];
                nums[i] = nums[i-1];
                nums[i-1] = tmp;
            }
            _189_rotate(nums,--k);
        }
        else
        {
            for(vector<int>::size_type i=1; i!=nums.size(); i++)
            {
              int tmp = nums[i];
                nums[i] = nums[i-1];
                nums[i-1] = tmp;
            }
            _189_rotate(nums,++k);
        }
    }
    //又看到了一个耍赖皮的方法，pop并不是真正pop掉，还是可以访问的，可以往begin处插值
    void rotate(vector<int>& nums, int k) {
        int n = nums.size() -1;
        while(k > 0)
        {
            nums.pop_back();
            nums.insert(nums.begin() ,nums[n]);
            k--;
        }
        
    }

作者：wu-shi-sui-lao-yi
链接：https://leetcode-cn.com/problems/rotate-array/solution/c-shua-lai-pi-jie-fa-by-wu-shi-sui-lao-yi/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
};

int main()
{
    vector<int> input={1,1,2,3,2,1,2};
    Solution* solution;
    int size=solution->_26_removeDuplicates(input);
    cout<<"size is "<<size<<"."<<endl;

    //test 189
    vector<int> test189 = {1,2,3,4,5,6,7};
    solution->_189_rotate(test189,6);
    return 0;
}