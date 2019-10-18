#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
//===============================================================================================================
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

//=====================================================================================================================
    //88、给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
    void _88_merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
        nums1.resize(m);
        nums2.resize(n);
        vector<int>::iterator nums1_pt = nums1.begin(), nums1_next = nums1_pt+1;
        //想对nums2进行遍历，对每一个nums2找到nums1的位置
        for(vector<int>::size_type i=0; i!=nums2.size(); i++)
        {
            for (; ;nums1_pt++,nums1_next++)
            {   
                if (*nums1_pt<=nums2[i] && nums2[i]<*nums1_next)
                {   
                    vector<int>::iterator tmp1 = nums1_pt;
                    vector<int>::iterator tmp2 = nums1_next;
                    nums1.insert(nums1_pt, nums2[i]);
                    nums1_pt = tmp1+1;
                    nums1_next = tmp2+1;
                    break;
                }
            }
        }        
    }

//===========================================================================
//==================                          ===============================
//==================      十大排序算法         ===============================
//==================                          ===============================
//===========================================================================
    //912、给定一个整数数组 nums，将该数组升序排列。
    //（1）冒泡法排序，先挑最大的
    vector<int> _912_sortArray_bubble_max(vector<int>& nums) 
    {
        for(vector<int>::size_type i=nums.size()-1; i!=0; i--)
        {
            bool canIStop = true;//这里加了一个可以提前停止的东西
            for(vector<int>::size_type j=0; j!=i; j++)
            {
                if(nums[j] > nums[j+1])//如果这个比后面的大，就把大的放到后面，就是挑出来最大的
                {
                    swap(nums[j+1], nums[j]);
                    canIStop = false;//如果一直没进来，就证明以及达到想要的顺序了，就可以停止了
                }
            }
            if(canIStop==true) return nums; 
        }
        return nums;
    }
    //（2）冒泡法排序，先挑最小的
    vector<int> _912_sortArray_bubble_min(vector<int>& nums) 
    {
        for(vector<int>::size_type i=0; i!=nums.size()-1; i++)
        {
            for(vector<int>::size_type j=nums.size()-2; j!=i-1; j--)//小排序是从后往前，就把小的放到最前面了
            {
                if(nums[j] > nums[j+1])//如果这个比后面的大，就把大的放到后面，就是挑出来最大的
                {
                    swap(nums[j+1], nums[j]);
                }
            }
        }
        return nums;
    }
    // （3）双向冒泡
    // 普通的冒泡排序在一趟循环中只能找出一个最大值或最小值，双向冒泡则是多一轮循环既找出最大值也找出最小值
    vector<int> _912_sortArray_bubble_2dir(vector<int>& nums)
    {
        int order = 1;
        for (vector<int>::size_type i = 1; i != nums.size()-1; i++)
        {
            if(nums[i-1]>nums[i])//先比较一次，得到最小的，放到第一个位置上，然后比较最后一个与最小的哪个更小，所以第一个位置就是最小的
                swap(nums[i], nums[i-1]);
            if(nums[i-1]>nums[i+1])
                swap(nums[i-1], nums[i+1]);
            if(nums[i]>nums[i+1])//如果第二个位置是大的，就换到第三个位置上
                swap(nums[i], nums[i+1]);
        }
        return nums;       
    }
    // 选择排序，原来我一开始用的是选择排序不是冒泡。。。
    // 和冒泡排序相似，区别在于选择排序是将每一个元素和它后面的每一个元素进行比较和交换，从而找到最小值
    // 最好：O(n2)
    // 最坏：O(n2)
    // 平均：O(n2)
    vector<int> _912_sortArray_selectSort(vector<int>& nums) 
    {
        for(int i=0; i<nums.size(); i++) {
            for(int j=i+1; j<nums.size(); j++) {
                if(nums[i] > nums[j]) {
                    swap(nums[i], nums[j]);
                }
            }
        }
        return nums;
    }

//==================================================================================================================================
    // 插入排序
    // 把第2个值拿出来以此和前面的进行比较（前一个），如果确实没有前面的小，就把前面的值赋到这个位置上，然后把tmp给前面；
    // 如果tmp还是比前面这个小，就继续这个动作，直到不小为之。
    // 主要是从第二个值开始以此跟前面所有的进行比较，把最小的放到最前面
    // 最好：O(n)，原数组已经是升序的  
    // 最坏：O(n2)， 原数组已经是降序的
    // 平均：O(n2)
    vector<int>  _912_sortArray_insertSort(vector<int> &nums) 
    {
        for(int i=1; i<nums.size(); i++) 
        {
            int temp = nums[i];
            int j = i;
            while(j >= 1 && temp < nums[j-1]) //如果比前一个小，就需要转换一下
            {
                nums[j] = nums[j-1];
                j--;
            }
            nums[j] = temp;
        }
        return nums;
    }

//==================================================================================================================================
    // 快速排序
    // 选择一个元素作为基数（通常是第一个元素），把比基数小的元素放到它左边，比基数大的元素放到它右边（相当于二分），再不断递归基数左右两边的序列。
    // 快速排序之填坑
    // 从右边向中间推进的时候，遇到小于基数的数就赋给左边（一开始是基数的位置），右边保留原先的值等之后被左边的值填上。
    // 最好：O(n * logn)，其他的数均匀分布在基数的两边，此时的递归就是不断地二分左右序列。
    // 最坏：O(n2) ， 其他的数都分布在基数的一边，此时划分左右序列就相当于成了插入排序。
    // 平均：O(n * logn)
    // vector<int> _912_sortArray_quickSort(vector<int>& nums)
    // {
    //     if(nums.size()<2) return nums;
    //     int middle = nums[0];
    //     vector<int> small,big;
    //     for(vector<int>::size_type i=1; i!=nums.size(); i++)
    //     {
    //         if(nums[i]<middle)
    //             small.push_back(nums[i]);
    //         else
    //             big.push_back(nums[i]);
    //     }
    //     vector<int> small_new = _912_sortArray_quickSort(small);
    //     vector<int> big_new   = _912_sortArray_quickSort(big);
    //     return plusAll(small, middle, big);
    //     // return _912_sortArray_quickSort();
    // }

    // vector<int> plusAll(const vector<int>& t1, int t2, const vector<int>& t3)
    // {
    //     vector<int> result(t3);
    //     result.insert(result.begin(), t2);
    //     for (int i=t1.size()-1; i>=0; i--)
    //         result.insert(result.begin(), t1[i]);
    // }
    void quickSort(int arr[], int left, int right) 
    {
        if(left >= right)  return;
        // 取第一个数为基数
        int temp = arr[left]; 
        int index = 0;
        // 将小于基数的数放到基数左边，大于基数的数放到基数右边，并返回基数的位置
        {
            int p = left;
            int q = right;
            while(p < q) {
            while(p < q && arr[q] >= temp)  q--;
            arr[p] = arr[q];
            while(p < q && arr[p] < temp)  p++;
            arr[q] = arr[p];
            }
            index = q;
        }
        // 修改基数的位置
        arr[index] = temp;
        // 递归排序基数左右两边的序列
        quickSort(arr, left, index - 1);
        quickSort(arr, index + 1, right);
    }

//===================================================================================================================
    // 桶排序
    // 将数组元素有序分配到n个桶里，最后再合并各个桶
    // 最好：O(n)，每个数都在分布在一个桶里，这样就可以省略将数插入排序到桶里的时间(类似于计数排序以空间换时间)。
    // 最坏：O(n2)，所有的数都分布在一个桶里
    // 平均：O(n + k)，k表示桶的个数
    vector<int> _912_sortArray_bucketSort(vector<int>& nums)
    {
        //先找最大值行不
        int max=0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i]>max)
            {
                max=nums[i];
            }
        }
        vector<int> result(max+1, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            result[nums[i]]++;//把有这个值的都加一
        }
        vector<int> output;
        for (int j = 0; j < result.size(); j++)
        {
            if(result[j]!=0)
                output.push_back(j);
        }
        return output;        
    }

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

    //test 88
    vector<int> nums1={1,2,3,4,5,6};
    vector<int> nums2={4,5};
    // solution->_88_merge(nums1, 6, nums2, 2);

    //test 912
    vector<int> input912={4,2,3,7,6,9,0};
    vector<int> output = solution->_912_sortArray_bucketSort(input912);
    return 0;
}