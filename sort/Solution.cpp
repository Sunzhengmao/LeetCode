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

    //验证桶排序算法
    // template<class Record>
    void BucketSort(int Array[], int n, int max)
    {
        int* TempArray = new int[n];
        int* count = new int[max];
        int i;
        for (i=0; i<n; i++)
            TempArray[i] = Array[i];
        for (i=0; i<max; i++)
            count[Array[i]]++;
        for (i=1; i<max; i++)
            count[i] += count[i-1];
        for (i=n-1; i>=0; i--)
        {
            int index = count[TempArray[i]];
            Array[--index] = TempArray[i];
        }
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

    vector<int> input = {5,3,7,11,9,3};
    solution->BucketSort(&input, input.size(), )

    return 1;
}