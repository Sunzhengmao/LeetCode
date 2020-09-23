#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<math.h>

#include<unordered_map>
using namespace std;
/*
比较好用的算法：抽屉法，双指针法

总结vector的基本用法
一、vector 的初始化：可以有五种方式,举例说明如下：
    (1) vector<int> a(10); //定义了10个整型元素的向量（尖括号中为元素类型名，它可以是任何合法的数据类型），但没有给出初值，其值是不确定的。
   （2）vector<int> a(10,1); //定义了10个整型元素的向量,且给出每个元素的初值为1
   （3）vector<int> a(b); //用b向量来创建a向量，整体复制性赋值
   （4）vector<int> a(b.begin(),b.begin+3); //定义了a值为b中第0个到第2个（共3个）元素
   （5）int b[7]={1,2,3,4,5,9,8};
        vector<int> a(b,b+7); //从数组中获得初值
    (6) vector<int> a={1,2,3};
二、vector对象的几个重要操作，举例说明如下：
    （1）a.assign(b.begin(), b.begin()+3); //b为向量，将b的0~2个元素构成的向量赋给a
    （2）a.assign(4,2); //是a只含4个元素，且每个元素为2
    （3）a.back(); //返回a的最后一个元素
    （4）a.front(); //返回a的第一个元素
    （5）a[i]; //返回a的第i个元素，当且仅当a[i]存在2013-12-07
    （6）a.clear(); //清空a中的元素
    （7）a.empty(); //判断a是否为空，空则返回ture,不空则返回false
    （8）a.pop_back(); //删除a向量的最后一个元素
    （9）a.erase(a.begin()+1,a.begin()+3); //删除a中第1个（从第0个算起）到第2个元素，也就是说删除的元素从a.begin()+1算起（包括它）一直到a.begin()+         3（不包括它）
    （10）a.push_back(5); //在a的最后一个向量后插入一个元素，其值为5
    （11）a.insert(a.begin()+1,5); //在a的第1个元素（从第0个算起）的位置插入数值5，如a为1,2,3,4，插入元素后为1,5,2,3,4
    （12）a.insert(a.begin()+1,3,5); //在a的第1个元素（从第0个算起）的位置插入3个数，其值都为5
    （13）a.insert(a.begin()+1,b+3,b+6); //b为数组，在a的第1个元素（从第0个算起）的位置插入b的第3个元素到第5个元素（不包括b+6），如b为1,2,3,4,5,9,8         ，插入元素后为1,4,5,9,2,3,4,5,9,8
    （14）a.size(); //返回a中元素的个数；
    （15）a.capacity(); //返回a在内存中总共可以容纳的元素个数
    （16）a.resize(10); //将a的现有元素个数调至10个，多则删，少则补，其值随机
    （17）a.resize(10,2); //将a的现有元素个数调至10个，多则删，少则补，其值为2
    （18）a.reserve(100); //将a的容量（capacity）扩充至100，也就是说现在测试a.capacity();的时候返回值是100.这种操作只有在需要给a添加大量数据的时候才         显得有意义，因为这将避免内存多次容量扩充操作（当a的容量不足时电脑会自动扩容，当然这必然降低性能） 
    （19）a.swap(b); //b为向量，将a中的元素和b中的元素进行整体性交换
    （20）a==b; //b为向量，向量的比较操作还有!=,>=,<=,>,<
三、顺序访问vector的几种方式，举例说明如下：
1、向量a中添加元素
    vector<int> a;
    for(int i=0;i<10;i++)
    a.push_back(i);
2、也可以从数组中选择元素向向量中添加
    int a[6]={1,2,3,4,5,6};
    vector<int> b；
    for(int i=1;i<=4;i++)
    b.push_back(a[i]);
3、也可以从现有向量中选择元素向向量中添加
    int a[6]={1,2,3,4,5,6};
    vector<int> b;
    vector<int> c(a,a+4);
    for(vector<int>::iterator it=c.begin();it<c.end();it++)
    b.push_back(*it);
4、也可以从文件中读取元素向向量中添加
    ifstream in("data.txt");
    vector<int> a;
    for(int i; in>>i)
        a.push_back(i);
5、【误区】
    vector<int> a;
    for(int i=0;i<10;i++)
        a[i]=i;
        //这种做法以及类似的做法都是错误的。刚开始我也犯过这种错误，后来发现，下标只能用于获取已存在的元素，而现在的a[i]还是空的对象
（2）从向量中读取元素
1、通过下标方式读取
    int a[6]={1,2,3,4,5,6};
    vector<int> b(a,a+4);
    for(int i=0;i<=b.size()-1;i++)
        cout<<b[i]<<" ";
2、通过遍历器方式读取
    int a[6]={1,2,3,4,5,6};
    vector<int> b(a,a+4);
    for(vector<int>::iterator it=b.begin();it!=b.end();it++)
        cout<<*it<<" ";
四、几种重要的算法，使用时需要包含头文件：
    #include<algorithm>
    （1）sort(a.begin(),a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素进行从小到大排列
    （2）reverse(a.begin(),a.end()); //对a中的从a.begin()（包括它）到a.end()（不包括它）的元素倒置，但不排列，如a中元素为1,3,2,4,倒置后为4,2,3,1
    （3）copy(a.begin(),a.end(),b.begin()+1); //把a中的从a.begin()（包括它）到a.end()（不包括它）的元素复制到b中，从b.begin()+1的位置（包括它）开始复制，覆盖掉原有元素
    （4）find(a.begin(),a.end(),10); //在a中的从a.begin()（包括它）到a.end()（不包括它）的元素中查找10，若存在返回其在向量中的位置
    （5）resize()

*/
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

//===============================================================================================================
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
    void _88_merge1(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if(nums1.empty()) return;
        int num1_idx=0, num2_idx=1;
        int num2_first = nums2[0];
        int left=0, right=nums1.size()-1;
        bool mask = true;
        while (left < right)
        {
            int weight = (left + right) >> 1;
            if(nums1[weight] == num2_first) 
            {
                num1_idx = weight;
                mask = false;
                break;
            }
            if(num2_first < nums1[weight]) right = weight;
            else left = weight + 1;
        }
        if (mask) num1_idx = left;
        nums1.insert(nums1.begin()+num1_idx, num2_first);
        
        for (; num2_idx < nums2.size(); num2_idx++)
        {
            while(!((nums2[num2_idx] <= nums1[num1_idx]) && (nums2[num2_idx] > nums1[num1_idx-1])))
            {
                num1_idx++;
            }
            nums1.insert(nums1.begin() + num1_idx, nums2[num2_idx]);
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
    // (4)选择排序，原来我一开始用的是选择排序不是冒泡。。。
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

    // (5)插入排序
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

    // (6)快速排序
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

    void _912_sortArray_quickSort(int left, int right, vector<int>& arr)
    {
        if(left >= right)
            return;
        int i, j, base, temp;
        i = left, j = right;
        base = arr[left];  //取最左边的数为基准数
        while (i < j)
        {
            while (arr[j] >= base && i < j)
                j--;
            while (arr[i] <= base && i < j)
                i++;
            if(i < j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        //基准数归位
        arr[left] = arr[i];
        arr[i] = base;
        _912_sortArray_quickSort(left, i - 1, arr);//递归左边
        _912_sortArray_quickSort(i + 1, right, arr);//递归右边
    }

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
        vector<int> result(max+1, 0);//这是那个桶，index是待排序数组的值
        for (int i = 0; i < nums.size(); i++)
        {
            result[nums[i]]++;//把有这个值的都加一
        }
        vector<int> output;
        for (int j = 0; j < result.size(); j++)
        {
            while(result[j]!=0)
            {
                output.push_back(j);
                result[j]--;
            }
        }
        return output;        
    }

//==================================================================================================================
    // 给定一个整数数组 A，如果它是有效的山脉数组就返回 true，否则返回 false。
    bool _941_validMountainArray(vector<int>& A) 
    {
        if(A[1] <= A[0]) return false;//如果第一个数没有第二个数小，就直接false好了
        int max = A[1];
        bool startdown = false;
        for(vector<int>::size_type i=2; i!=A.size(); i++)
        {
            if (A[i] > max && !startdown)
            {
                max = A[i];
                continue;
            }
            //如果能到这说明A[i]<=max
            startdown = true;
            if(A[i] < max)
            {
                max = A[i];
            }
            else
            {
                return false;
            }
        }
        return startdown;
    }

//================================================================================================================
    //561、给定长度为 2n 的数组, 你的任务是将这些数分成 n 对, 例如 (a1, b1), (a2, b2), ..., (an, bn) ，使得从1 到 n 的 min(ai, bi) 总和最大。
    //第一感觉是先排序，然后从最小的开始隔一个取一个，桶排序可能会好一些，试一下
    int _561_arrayPairSum(vector<int>& nums) 
    {
        sort(nums.begin(),nums.end());
        int sum=0;
        for (int i = 0; i < nums.size(); i=i+2)
        {
            sum+=nums[i];
        }
        return sum;
    }
//===============================================================================================================
    //989、对于非负整数 X 而言，X 的数组形式是每位数字按从左到右的顺序形成的数组。例如，如果 X = 1231，那么其数组形式为 [1,2,3,1]。
    //果真出现了int保存不下的数，所以需要换个思路了，对每一位进行操作
    vector<int> _989_addToArrayForm(vector<int>& A, int K) 
    {
        int last = K;
        for (vector<int>::size_type i = A.size(); i != 0; i--)
        {
            last = last + A[i-1];
            A[i-1] = (last) % 10;
            last = last/10;
            if(last==0) break;
        }
        while(last!=0)
        {
            A.insert(A.begin(), last%10);
            last /= 10;
        }
        return A;
    }

//==============================================================================================================
    //932、对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：对于每个 i < j，都不存在 k 满足 i < k < j 
    //使得 A[k] * 2 = A[i] + A[j]。那么数组 A 是漂亮数组。
    vector<int> _932_beautifulArray(int N) 
    {
        return {};
    }

//==============================================================================================================
/*      由于时间复杂度有点高，所以想换个方法
        int max_in_Left = 0;
        for(int i = 0; i!=A.size(); i++)
        {
            bool UcanStop = true;
            if(max_in_Left<A[i]) 
                max_in_Left = A[i];//left中最大的要小于right中最小的
            for(int j = A.size()-1; j!=i; j--)//依次遍历求最小
            {
                if(A[j]<max_in_Left) //如果不满足大于left的最大的，就退出吧，如果都满足了就可以return i了
                {
                    UcanStop = false;
                    break;
                }
            }
            if(UcanStop) 
            {
                return i+1;
            }
        }
*/
    //915、给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right
    //不知道为什么别人就能想出来我就不行。。。如果
    int _915_partitionDisjoint(vector<int>& A) 
    {   
        int lmax = A[0];
        int rmax = A[1];
        int left = 0;
        int N = A.size();
        for (int i = 1; i < N; ++i) 
        {
            rmax = max(rmax, A[i]);//当前最大值
            if (A[i] < lmax) //一出现比左边最大值还要小的就得更新left，因为要找到第一个不满足≤左边最大值的点，这样才能保证left右边比左边都大
            {
                left = i;
                lmax = max(lmax, rmax);//同时还要保证此时我的左边的最大的是当前最大的，如果还有比左边最大值更大的值。。。妈的越说越乱
                //left右边还有比左边更大的，如果没有降到max_in_left下，证明他们都可以算成右序列了，否则就是降到下面，比他们还要小，就得更新max_in_left
                //怎么说呢，还是朝着简单的方向走，而且把条件分析清楚，还是对题意理解不透彻   
            }
        }
        return left + 1;        
    }

//====================================================================================================================
    //905、给定一个非负整数数组 A，返回一个数组，在该数组中， A 的所有偶数元素之后跟着所有奇数元素。
    //输入：[3,1,2,4], 输出：[2,4,3,1]
    vector<int> _905_sortArrayByParity(vector<int>& A) 
    {
        int left=0, right = A.size()-1;
        while(1)
        {
            while((A[left]%2==0) && (left<right))//是偶数就要换下一个，因为要和后面的偶数进行替换
                left++;
            while((A[right]%2!=0) && (left<right))//是奇数就得找下一个，因为奇数留在后面
                right--;
            if(left<right)
                swap(A[left], A[right]);
            else break;
        }
        return A;
    }

//==================================================================================================================
    //448、给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。
    //输入:[4,3,2,7,8,2,3,1]，输出:[5,6]
    vector<int> _448_findDisappearedNumbers(vector<int>& nums) 
    {

        // 用map还是慢啊，计算哈希算子本身就比较费时间，所以最好能跳过，每次即使遍历
        // map<int, int> output;
        // vector<int> result;
        // for(vector<int>::iterator i = nums.begin(); i!=nums.end(); i++)
        //     output[*i]++;
        // for(int i = 1; i<=nums.size(); i++)
        // {
        //     if(output[i]==0)
        //         result.push_back(i);
        // }
        // return result;
        vector<int> result;
        for(int i = 0; i<nums.size(); i++)
        {
            while (nums[i]!=nums[nums[i]-1])
                swap(nums[i], nums[nums[i]-1]);
        }
        for(int i = 0; i<nums.size(); i++)
        {
            if(nums[i] != (i+1))
                result.push_back(i+1);
        }
        return result;
    }
    
//==================================================================================================================
    //442、给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。
    vector<int> _442_findDuplicates(vector<int>& nums) 
    {
        vector<int> ret;
        //思路是对原数组进行处理，对应位置上放i，如果对应位置上已经有i了，就证明重复了呗
        for (int i=0; i!=nums.size(); i++)
        {
            while(nums[i] != nums[nums[i]-1])
                swap(nums[i],nums[nums[i]-1]);  // nums[i]-1位置放置nums[i]元素
        }
        for(int i=0; i!=nums.size(); i++)
        {
            if(nums[i]!=i+1)
                ret.push_back(nums[i]);
        }
        return ret;        
    }

//====================================================================================================================
    //27、移除元素，给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
    vector<int> _27_removeElement1(vector<int>& nums, int val) 
    {
        if (nums.size() == 0)
            return {};

        int front_index = 0;// back_index = 0;
        for (size_t back_index = 0; back_index < nums.size(); back_index++)
        {
            if (nums[back_index] != val)
            {
                nums[front_index] = nums[back_index];
                front_index ++;
            }
        }
        vector<int> result(nums.begin(), nums.begin()+front_index);
        return result;
    }
    //27、这次取front_index到最后的，我感觉这样就不用从头到尾一直
    vector<int> _27_removeElement2(vector<int>& nums, int val) 
    {
        if (nums.size() == 0)
            return {};

        int front_index = 0;// back_index = 0;
        for (size_t back_index = 0; back_index < nums.size(); back_index++)
        {
            if (nums[back_index] == val)
            {
                if (nums[front_index] == val)
                {
                    front_index ++;
                }
                else
                {
                    swap(nums[front_index], nums[back_index]);
                    front_index ++;
                }
            }
        }
        vector<int> result(nums.begin()+front_index, nums.end());
        return result;
    }

//===========================================================================================================
    //35、给出一个排序之后的数组和val，按照大小找出target应在的index
    int _35_searchInsert1(vector<int>&nums, int target)
    {
        if(nums.size()==0) return 0;
        int left=0, right=nums.size();
        while (left < right)
        {
            int middle = left + right >> 1;
            if (nums[middle] == target) return middle;
            if (nums[middle] < target)
            {
                left = middle+1;
            }
            else
            {
                right = middle;
            }
        }
        return left;        
    }

//============================================================================================================
    //66、给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。
    vector<int> _66_plusOne1(vector<int>& digits) 
    {
        if (digits.empty()) return{};
        bool needAdd = true;
        for (int i = digits.size()-1; i >= 0; i--)
        {
            if (needAdd)
            {
                if(digits[i] >= 9)
                {
                    needAdd = true;
                    digits[i] = 00;
                }
                else
                {
                    needAdd = false;
                    digits[i] += 1;
                    break;
                }
            }
        }
        if (needAdd) digits.insert(digits.begin(), 1);
        return digits;
    }

//==============================================================================================================
    //1、给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    vector<int> _1_twoSum(vector<int>& nums, int target) 
    {
        if(nums.empty()) return {};
        unordered_map<int, int> hashMap;

        int front_index = 0;
        for (; front_index < nums.size(); front_index++)
        {
            int diff = target - nums[front_index];
            if(hashMap.find(diff) == hashMap.end())//没找到
            {
                hashMap.insert(make_pair(nums[front_index], front_index));
            }
            else
            {
                return vector<int>{hashMap[diff], front_index};
            }
        }
        return {};        
    }

//===========================================================================================================
    //121、给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。先买入再卖出，设计算法获取最大利润。
    int _121_maxProfit(vector<int>& prices) 
    {
        if(prices.empty()) return 0;
        int lowest_price = prices[0];
        int max_profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] < lowest_price)
            {
                lowest_price = prices[i];
                continue;
            }
            
            int today_profit = prices[i]-lowest_price;
            if (today_profit > max_profit)
            {
                max_profit = today_profit;
            }
        }
        return max_profit;
    }
    //122、数组的第i个元素是股票第i天的价格。设计算法计算最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）
    int _122_maxProfit1(vector<int>& prices) //这是寻找一个一个的波峰和波谷的思想，
    {
        if (prices.empty()) return 0;
        int lowest_price = prices[0];
        int max_profit = 0;
        int result = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            int today_profit = prices[i] - lowest_price;
            if (today_profit > max_profit)
            {
                max_profit = today_profit;
            }          
            else
            {
                lowest_price = prices[i];
                result += max_profit;
                max_profit = 0;
            }
        }
        result += max_profit;
        return result;        
    }
    int _122_maxProfit2(vector<int> & prices)// 这里用贪心的一个算法，线性且常数空间
    {
        int result = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > prices[i-1])
                result += prices[i] - prices[i-1];
        }
        return result;
    }
    //123、整体情况都一样，但是最多可以完成两笔交易
    int _123_maxProfit1(vector<int>& prices) //我的想法就是把每次利润记录下来，并找出最大的两个
    {
        int max_profit = 0;
        int more_profit = 0;
        int today_profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > prices[i-1])
            {
                today_profit += prices[i] - prices[i-1];
            }
            else
            {
                if (today_profit > max_profit)
                {
                    more_profit = max_profit;
                    max_profit = today_profit;
                }
                else
                {
                    if (today_profit > more_profit)
                        more_profit = today_profit;
                }
                today_profit = 0;
            }
        }
        if (today_profit > max_profit)
        {
            more_profit = max_profit;
            max_profit = today_profit;
        }
        else
        {
            if (today_profit > more_profit)
                more_profit = today_profit;
        }
        return max_profit + more_profit;

    }

//=======================================================================================================
    //118、给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。
    vector<vector<int>> _118_generate(int numRows) 
    {
        if(numRows == 0) return {};
        vector<vector<int>> result;
        for(int i=1; i<=numRows; i++)
        {
            if(i==1) 
            {
                result.push_back({1});
                continue;
            }
            if(i==2)
            {
                result.push_back({1,1});
                continue;
            }
            vector<int> &lastRow = result.back();
            vector<int> thisRow = {1};
            for(int j = 0; j<lastRow.size()-1; j++)
            {
                thisRow.push_back(lastRow[j] + lastRow[j+1]);
            }
            thisRow.push_back(1);
            result.push_back(thisRow);
        }
        return result;
    }

//===============================================================================================
    //48、给定一个 n × n 的二维矩阵表示一个图像。将图像顺时针旋转 90 度。
    void _48_rotate(vector<vector<int>>& matrix) 
    {
        if(matrix.empty()) return;
        for(int i=0; i<matrix.size(); i++)
        {
            for(int j=i; j<matrix.size(); j++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
    }
//================================================================================================
    //62、机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。问总共有多少条不同的路径？
    //////////////////////////////////  大名鼎鼎的动态规划  ///////////////////////////////////
    int gcd(int a,int b)   //求分子分母的最大公约数
    {
        return b==0?a:gcd(b,a%b);
    }
    int _62_uniquePaths(int m, int n) 
    {
        int ans=m+n-2;         //记录需走过的方格数
        int a=1,b=1,l=n-1;     //a记录组合公式的分子，b记录组合公式的分母
        for (int i=1;i<=n-1;i++)
        {
            a*=ans;
            ans--;
            b*=l;
            l--;
        //这里我们采取边乘边约分的方法，否则数据稍大是会爆int
            int g=gcd(a,b);     //记录最大公约数
            a/=g;               //约分
            b/=g;               //约分
        }
        return a/b;
    }

//=========================================================================================================
    //78、给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。说明：解集不能包含重复的子集。
    vector<vector<int>> _78_subsets(vector<int>& nums) 
    {
        // if(nums.empty()) return {};
        vector<vector<int>> result{{}};//已经放了空的在里面了
        for(int i=0; i<nums.size(); i++)
        {
            vector<vector<int>> temp_result = result;
            for(auto &item : temp_result)
            {
                item.push_back(nums[i]);
                result.push_back(item);
            }
        }
        return result;
    }
};

int main()
{
    vector<int> input={1,1,2,3,2,1,2};
    Solution* solution;
    int size=solution->_26_removeDuplicates(input);

    //test 189
    vector<int> test189 = {1,2,3,4,5,6,7};
    solution->_189_rotate(test189,6);

    //test 88
    vector<int> nums1={1,2,3,4,5,6};
    vector<int> nums2={4,5};
    // solution->_88_merge(nums1, 6, nums2, 2);

    //test 912
    vector<int> input912={4,2,3,3,2,7,6,9,0};
    vector<int> output = solution->_912_sortArray_bucketSort(input912);

    //teset 941
    vector<int> input941 = {1,3,7,9};
    bool output941 = solution->_941_validMountainArray(input941);

    //test 989
    vector<int> input989 = {9,9,9,9,9,9,9};
    vector<int> output989 = solution->_989_addToArrayForm(input989, 1);

    //test 915
    vector<int> input915 = {5,0,3,8,6};
    int output915 = solution->_915_partitionDisjoint(input915);

    //test 905
    vector<int> input905 = {5,3,1,2,4};
    vector<int> output905 = solution->_905_sortArrayByParity(input905);

    //test 448
    vector<int> input448 = {4,5,3,1,7,2,1};
    vector<int> ouput448 = solution->_448_findDisappearedNumbers(input448);

    //test 442
    vector<int> input442 = {4,3,2,7,8,2,3,1};
    vector<int> output442 = solution->_442_findDuplicates(input442);

    //test 27
    vector<int> input27 = {1,2,3,4};
    vector<int> output27 = solution->_27_removeElement2(input27, 3);

    //test 35
    vector<int> input35 = {1,3,5,6};
    int output35 = solution->_35_searchInsert1(input35, 2);

    //test 66
    vector<int> input66 = {9};
    vector<int> output66 = solution->_66_plusOne1(input66);

    //test 1
    vector<int> input1 = {2,17,11,15,7};
    vector<int> output1 = solution->_1_twoSum(input1, 17);

    //test 121
    vector<int> input121 = {7,1,5,3,6,4};
    int output121 = solution->_121_maxProfit(input121);

    //test 122
    vector<int> input122 = {1,2,3,4,5};
    int output122 = solution->_122_maxProfit2(input122);

    //test 123
    vector<int> input123 = {1,2,4,2,5,7,2,4,9,0};
    int output123 = solution->_123_maxProfit1(input123);

    //test 118
    vector<vector<int>> output118 = solution->_118_generate(5);

    //test 62
    int output62 = solution->_62_uniquePaths(7,3);

    //test 78
    vector<int> input78{};
    vector<vector<int>> output78 = solution->_78_subsets(input78);
    return 0;
}