#include <math.h>
#include <vector>
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

//=========================================================================================================================
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

//============================================================================================================
    //122、给定一个数组，它的第i个元素是一支给定股票第i天的价格。设计一个算法来计算你所能获取的最大利润。
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
    
};

int main()
{
    Solution* solution;

    //test 1221
    string s_1221 = "RLLLLRRRLR";
    int result_1221 = solution->_1221_balancedStringSplit(s_1221);

    //test 122
    vector<int> prices_122 = {7,1,5,3,6,4,3,6,5,11,3,8,9,12,2,4,5,7,1,5,3,6,4,3,6,5,11,3,8,9,12,2,4,5,7,1,5,3,6,4,3,6,5,11,3,8,9,12,2,4,5};
    clock_t start_122, end_122;
    start_122 = clock();
    int result_122 = solution->_122_maxProfit(prices_122);
    // int result_122 = solution->_122_maxProfit_better(prices_122);
    end_122 = clock();
    cout<< (double)(end_122 - start_122)/CLOCKS_PER_SEC <<endl;

    return 1;   
}