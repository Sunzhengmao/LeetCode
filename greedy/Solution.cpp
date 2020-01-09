/**
 * 2020.1.3
 * 所谓贪婪，就是在局部里面找最优的，然后放眼到全局，也能是最优的，所以我们需要将大路子合理的分划出小步子，然后
 * 分别去计算就行
 **/
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>
#include <ctime>
#include <iostream>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//1221、在一个「平衡字符串」中，'L' 和 'R' 字符的数量是相同的。给出一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串
    //这里其实是失败的，因为我没考虑万一不平衡了怎么办。。。
    int _1221_balancedStringSplit(string s) 
    {
        stack<char> something={};
        int num = 0;
        int result = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if(something.empty())
            {
                something.push(s[i]);
                continue;
            }
            if(something.top() == s[i])//如果栈里面的东西等于s[i]，就可以放进来，然后记着数
                num++;
            else
            {
                i+=num;
                something={};
                result++;
                num=0;
            }   
        }
        return result;        
    }

//122、 给定一个数组，它的第i个元素是一支给定股票第i天的价格。设计一个算法来计算你所能获取的最大利润。
    //     你可以多次买卖一支股票，你必须在再次购买前出售掉之前的股票
    //-----------------------------||   分析   ||--------------------------------------//
    //失败的原因是：时间复杂度太高，都无法在有限时间内跑完了，虽然是迭代的方法，好像是n4次方//
    //-----------------------------||   结束   ||--------------------------------------//
    int _122_maxProfit(vector<int>& prices) 
    {
        if(prices.size() < 2) return 0;
        if(prices.size() == 2)//如果第一个大，则不能买，返回0，否则就买，利润是大的减小的
            return prices[0]>=prices[1]? 0:prices[1]-prices[0];
        
        int base = prices[0];//选一个基准出来，把这个时候买入的挣得钱的最多的找出来
        int profit = 0;//记录这个base下的利润最大的值
        for (int i = 1; i < prices.size(); i++)
        {
            if(base >= prices[i])//如果base都贵于你，就不能卖了，否则会赔本
                continue;
            if(i == prices.size()-1)//如果i已经是最后一个了，就别往后取了
                profit = max(profit, prices[i]-base);
            else
            {//否则还是得往后取
                vector<int> resPrices(prices.begin()+i+1, prices.end());//把剩下的进行迭代一下
                profit = max(profit, prices[i]-base+_122_maxProfit(resPrices));                  
            }
        }
        vector<int> theTwoDay(prices.begin()+1, prices.end());
        return max(profit, _122_maxProfit(theTwoDay));
    }
    //- - - - - - - - - - - - - - || 正确解法 || - - - - - - - - - - - - - - - - //
    //买股票可以在当天卖掉然后当天买入，这样只要今天比昨天还高就卖
    // - - - - - - - - - - - - - -|| 真牛逼呀 || - - - - - - -  - - - - - - - - -//
    int _122_maxProfit_better(vector<int>& prices)
    {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if(prices[i]>prices[i-1])
                profit+=prices[i]-prices[i-1];
        }
        return profit;        
    }

//55、  给定一个非负整数数组，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳跃的最大长度。判断是否能够到达最后一个位置。
    bool _55_canJump(vector<int>& nums) 
    {
        //初步想法：找0的位置，如果不能跨过0的话，就肯定不行
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i]==0)//如果i不是最后一位
            {
                int loc = i-1;
                int step = (i==(nums.size()-1))? 1:2;
                bool IcanGo = false;
                while (loc >= 0)
                {   
                    if(nums[loc] >= step)
                    {   
                        IcanGo = true;
                        break;
                    }
                    loc--;
                    step++;
                }
                if (!IcanGo)
                {
                    return false;
                }
            }
        }
        return true;
    }

    //----------------------------|| 最远位置 ||-----------------------------------//
    //尽可能到达最远位置（贪心），如果能到达某个位置，那一定能到达它前面的所有位置。
    //----------------------------|| 贪心算法 ||----------------------------------//
    bool _55_canJump_greedy(vector<int>& nums)
    {
        int max_i = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i<=max_i && nums[i]+i>max_i)
            {
                max_i = nums[i] + i;
            }
        }
        return max_i>=nums.size()-1;        
    }

//45、  同样的要跳到最后一个位置，但是这次要最小的步数
    int _45_jump(vector<int>& nums) 
    {
        int count = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if(nums[i]+i >= nums.size()-1) return count;
            int max_step = 0;
            int tmp = 0;
            //这里才是贪婪的开始，要nums[i]范围内，能够往后走的最多
            for (int j = 1; j <= nums[i]; j++)
            {
                if(j + nums[i+j] >= max_step)
                {
                    max_step = j + nums[i+j];
                    tmp = j;
                }
            }
            i += tmp-1;
            count++;            
        }
        return 0;        
    }

//392、 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
    bool _392_isSubsequence(string s, string t) 
    {
        if(s.size()==0) return true;
        int loc_t = 0;
        for (int i = 0; i < s.size(); i++)
        {
            bool Ifoundit = false;
            for (; loc_t < t.size(); loc_t++)
            {
                if (s[i] == t[loc_t])
                {
                    Ifoundit = true;
                    break;
                }
            }
            loc_t++;
            if (!Ifoundit) return false;
        }
        return true;        
    }

//134、 加油站，从i中得到gas[i]个油，前往下一个加油站需要消耗cost[i]个油，返回能循环一周的索引，否则返回-1
    int _134_canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        //初步思路是从这个索引开始，如果每个的gas和都能大于cost和
        
        for (int i = 0; i < gas.size(); i++)
        {
            if(gas[i]<cost[i]) continue;
            int index = i;
            int count = 0;//记录走了几步了，走完size步才能停
            int res = 0;
            bool IcanDo = true;
            while (count<gas.size())
            {
                count++;
                res += gas[index]-cost[index];
                if(res<0)
                {
                    IcanDo = false;
                    break;
                }
                index = index>=(gas.size()-1) ? 0 : (index+1);//如果index已经大于
            }
            if(IcanDo) return index;
        }
        return -1;
    }

    //---------------------------------|| 官方题解 ||---------------------------------------//
    //实现O(N)时间复杂度，还是很有技巧性的
    //---------------------------------|| 官方题解 ||---------------------------------------//
    int _134_canCompleteCircuit_offical(vector<int>& gas, vector<int>& cost)
    {
        int n = gas.size();
        int total_tank = 0;
        int curr_tank = 0;
        int starting_station = 0;
        for (int i = 0; i < n; ++i) 
        {
            total_tank += gas[i] - cost[i];
            curr_tank += gas[i] - cost[i];
            // If one couldn't get here,
            if (curr_tank < 0) 
            {
                // Pick up the next station as the starting one.
                starting_station = i + 1;
                // Start with an empty tank.
                curr_tank = 0;
            }
        }
        return total_tank >= 0 ? starting_station : -1;
    }
};

int main()
{
    Solution* solution;

    //test 1221
    string s_1221 = "RLLLLRRRLR";
    int result_1221 = solution->_1221_balancedStringSplit(s_1221);

    //test 122
    vector<int> prices_122 = {7,1,5,3,6,4,3,6,5};
    clock_t start_122, end_122;
    start_122 = clock();
    int result_122 = solution->_122_maxProfit(prices_122);
    // int result_122 = solution->_122_maxProfit_better(prices_122);
    end_122 = clock();
    // cout<< (double)(end_122 - start_122)/CLOCKS_PER_SEC <<endl;

    //test 55
    vector<int> nums_55 = {2,0,0};
    bool result_55 = solution->_55_canJump_greedy(nums_55);

    //test 45
    vector<int> nums_45 = {5,4,4,2,1,0,1};
    int result_45 = solution->_45_jump(nums_45);

    //test 134
    vector<int> gas_134 = {1,2,3,4,5};
    vector<int> cost_134 = {3,4,5,1,2};
    int result_134 = solution->_134_canCompleteCircuit(gas_134, cost_134);

    return 1;   
}