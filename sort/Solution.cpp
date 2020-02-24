#include <iostream>
#include<vector>

using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

    //桶排序算法
    void BucketSort(vector<int>& Array, int max)
    {
        const int n = Array.size();
        vector<int> TempArray = {};
        vector<int> count(max, 0);
        int i;
        for (i=0; i<n; i++)
            TempArray.push_back(Array[i]);
        for (i=0; i<n; i++)
            count[Array[i]]++;
        for (i=1; i<max; i++)
            count[i] += count[i-1];
        for (i=n-1; i>=0; i--)
            Array[--count[TempArray[i]]] = TempArray[i];
    }

    //快速排序
    void QuickSort(vector<int>& input, int left, int right)
    {
        if (left >= right) return ;
        if (left == right-1)
        {
            if (input[left] > input[right])
                swap(input[left], input[right]);
            return ;
        }

        const int N = input.size();
        int cut = Partition(input, left, right);
        QuickSort(input, left, cut-1);
        QuickSort(input, cut+1, right);        
    }

    int Partition(vector<int>& input, int left, int right)
    {
        if (left == right) return input[left];
        if (left > right)  return -1;

        int tempValue = input[right-1];
        input[right-1] = input[right];

        // int middle = (right - left >> 1) + left;
        // int tempValue = input[middle];
        // input[middle] = input[right];

        while (left != right)
        {
            while (input[left] <= tempValue && left < right)
                left++;
            if (left < right)
            {
                // swap(input[left], input[right]);
                input[right] = input[left];
                right--;
            }

            while (input[right] > tempValue && left < right)
                right--;
            if (left < right)
            {
                // swap(input[left], input[right]);
                input[left] = input[right];
                left++;
            }          
        }
        input[left] = tempValue;

        return left;       
    }
};
/////////////////////////////////////////////////////
//   实现桶排序                                ///////
//   实现快排的交换操作                        ///////
//   找出其与第k个最小值的方法的区别            ///////
/////////////////////////////////////////////////////
int main()
{
    Solution* solution;

    vector<int> input_bucket = {5,3,7,11,9,3};
    solution->BucketSort(input_bucket, 12);

    vector<int> input_quick = {6,7,4,2,8,1,0,5,3};
    solution->QuickSort(input_quick, 0, 8);

    return 1;
}