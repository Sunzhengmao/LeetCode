#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int helloworld();
int reverse(int x) ;
int main()
{
    cout<<"hello world!"<<endl;
    for (int i = 0; i < 10; i++)
    {
        cout<<"I love U "<<i<<"times;"<<endl;
        int a = helloworld();
    }
    
}

int helloworld()
{
    printf("hello world!\n");
    return 1;
}

int reverse(int x) 
{
    if((x>pow(2,31)-1)||(x<(-pow(2,31))))
        return 0;
    int sign=1;
    if (x<0)
            sign = -1;
        int input = sign * x;
        int output=0;
        vector<int> result;
        int stop=1;
        int count;
        //每次都取余数，直到取为0
        for (count=1;stop!=0;count++ )
        {
            result.push_back(input%10);
            stop = input/10;
            input = stop;
        }
        for (int i = 0;result.size()!=0; i++)
        {
            int tmp = result.back();
            output+=pow(10,i) * tmp;
            result.pop_back();
        }
        int o = sign * output;
        return o;     
    }