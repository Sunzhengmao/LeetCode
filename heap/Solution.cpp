#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//=======================================================================================================
    //1046、有一堆石头，每块石头的重量都是正整数。每次选出两块最重的石头将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。
    //      如果 x == y，那么两块石头都会被完全粉碎；
    //      如果 x < y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
    //      最后，最多只会剩下一块石头。返回此石头的重量。如果没有石头剩下，就返回 0。
    int _1046_lastStoneWeight(vector<int>& stones) 
    {
        while (stones.size()>=2)//里面至少有两个的时候才能正常循环  
        {
            make_heap(stones.begin(), stones.end(), less<int>());

            // get x
            pop_heap(stones.begin(), stones.end(), less<int>());
            int x = *(stones.end()-1);
            stones.pop_back();

            // get y
            pop_heap(stones.begin(), stones.end(), less<int>());
            int y = *(stones.end()-1);
            stones.pop_back();

            if(x != y)
            {
                int back = abs(y-x);
                stones.push_back(back);
                push_heap(stones.begin(), stones.end(), less<int>());
            }            
        }
        if(stones.size())//只有一个的时候，就直接输出他的重量
            return stones[0];     
        return 0;
    }
};

int main()
{
    vector<int> nums = {4,5,6,7,8,1,1};
    Solution* solution;
    
    // test 1046
    vector<int> stones_1046 = {4,5,6,7,8,1,1};
    int output_1046 = solution->_1046_lastStoneWeight(stones_1046);


    make_heap(nums.begin(), nums.end(), less<int>());
    pop_heap(nums.begin(), nums.end(), less<int>());

    pop_heap(nums.begin(), nums.end(), less<int>());
    

    nums.push_back(10);
    push_heap(nums.begin(), nums.end());
    push_heap(nums.begin(), nums.end(), less<int>());
    cout<<"__"<<is_heap(nums.begin(), nums.end())<<endl;
    copy(nums.begin(),nums.end(),ostream_iterator<int>(cout,","));  //显示堆
    cout<<endl;

    make_heap(nums.begin(), nums.end(), less<int>());
    cout<<"__"<<is_heap(nums.begin(), nums.end())<<endl;
    copy(nums.begin(),nums.end(),ostream_iterator<int>(cout,","));  //显示堆
    cout<<endl;

    pop_heap(nums.begin(), nums.end(), less<int>());
    nums.pop_back();
    cout <<"_ _ _ _ _"<<is_heap(nums.begin(), nums.end()) << endl;
    make_heap(nums.begin(), nums.end(), less<int>());

    return 1;
}