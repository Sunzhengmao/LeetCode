#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Solution
{
private:
    
public:
    Solution(/* args */);
    ~Solution();
// 746. 使用最小花费爬楼梯,爬不需要费体力，停下来需要消耗体力
    int _746_minCostClimbingStairs(vector<int>& cost) 
    {
        if (cost.size() <= 2) return 0;

        const int N = cost.size();
        int result = cost[N-1];

        for (int i = N-2; i >= 1; i--)
        {
            if (cost[i-1] <= cost[i])
            {
                result += cost[i-1];
                i--;
            }
            else
            {
                result += cost[i];
            }
        }
        return result;   
    }

    int _746_minCostClimbingStairs_key(vector<int>& cost)
    {
        int c1 = cost[0];
        int c2 = cost[1];
        int c3 = 0;
        int N = cost.size();
        for (int i = 2; i < N; ++i) 
        {
            c3 = min(c1, c2) + cost[i];
            c1 = c2;
            c2 = c3;
        }
        return min(c1, c2);
    }

};



int main()
{
    Solution* solution;

    //test 746
    vector<int> cost_746 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    int result_746 = solution->_746_minCostClimbingStairs_key(cost_746);

    return 1;
}