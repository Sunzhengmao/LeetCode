#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
 
//声明一个模板
typedef std::function<int(int)> Functional;
int paintingPlan(int n, int k);
int Cnm(int n, int m);
 
int paintingPlan(int n, int k) 
{
        if(k<n) return 0;
        if(k==n*n) return 1;
        int ans = 0;
        if(k%n==0) //整除n
        {
            ans += 2* Cnm(n,k/n);
        }
        int ans2 = 0;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                int temp = n*i + n*j - i*j;
                if(k == temp)
                    ans2++;
            }
        }
        return ans + ans2/2;
}

int Cnm(int n, int m)
{
    int fenzi = 1;
    int fenmu = 1;
    for(int i=0; i<m; i++)
    {
        fenzi *= n-i;
        fenmu *= i+1;
    }
    return int(fenzi/fenmu);
}

int main(int argc, char* argv[])
{
    int ans = paintingPlan(4,13);
    // params(output_something);

    // //封装普通函数
    // Functional obj = TestFunc;
    // int res = obj(0);
    // cout << "normal function : " << res << endl;
 
    // //封装lambda表达式
    // obj = lambda;
    // res = obj(1);
    // cout << "lambda expression : " << res << endl;
 
    // //封装仿函数
    // Functor functorObj;
    // obj = functorObj;
    // res = obj(2);
    // cout << "functor : " << res << endl;
 
    // //封装类的成员函数和static成员函数
    // CTest t;
    // obj = std::bind(&CTest::Func, &t, std::placeholders::_1);
    // res = obj(3);
    // cout << "member function : " << res << endl;
 
    // obj = CTest::SFunc;
    // res = obj(4);
    // cout << "static member function : " << res << endl;
 
    return 0;
}