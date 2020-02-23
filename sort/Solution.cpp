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
    void QuickSort(vector<int>& input)
    {
        const int N = input.size();
        int middle = N/2;
        int i = 0;
        int j = N-1;
        while (i <= j)
        {
            while (input[i] > input[middle])
            {
                
            }
            
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
    solution->BucketSort(input, 12);

    return 1;
}