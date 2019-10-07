#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
class Solution {
public:
    // 2019.10.3 第一次解答，感觉还可以更精简
    // int reverse(int x) 
    // {
    //     int sign=1;
    //     if (x<0)
    //         sign = -1;
    //     long input = sign * long(x);
    //     if((input>pow(2,31)-1)||(input<(-pow(2,31))))
    //         return 0;
    //     long output=0;
    //     vector<int> result;
    //     int stop=1;
    //     int count;
    //     //每次都取余数，直到取为0
    //     for (count=1;stop!=0;count++ )
    //     {
    //         result.push_back(input%10);//每次的余数
    //         stop = input/10;
    //         input = stop;
    //     }
    //     for (int i = 0;result.size()!=0; i++)
    //     {
    //         int tmp = result.back();
    //         output+=pow(10,i) * tmp;
    //         result.pop_back();
    //         if((output>(pow(2,31)-1))||(output<(-pow(2,31))))
    //             return 0;
    //     }
    //     return sign * output;     
    // }

    ///2019.10.4 -> 100, 83.07
    int reverse(int x) 
    {
        int sign = x>0 ? 1:-1;
        // if (x<0)   sign = -1;
        long input = sign * long(x);//这里用long来得到比int更多的位数，以检测int类是否在[-2^31, 2^31-1]范围内
        // long input = x>0? long(x):long(-x);
        if((input>pow(2,31)-1)||(input<(-pow(2,31))))
            return 0;
        long num = 0;
        for (int count=1; input!=0; count++ )
        {
            int last_one = input % 10;//每次取出来的余数都可以直接乘以10，利用循环得到最终的值
            num = num*10 + last_one;
            input = input/10;
        }
        num *= sign;
        if((num>pow(2,31)-1)||(num<(-pow(2,31))))
            return 0;
        return num;     
    }
};

int main()
{
    Solution solution;   
    int a = -214748;
    int output = solution.reverse(a);
    cout<<output<<endl;
}

