#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();

//========================================================================================================
    //136、给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
    int _136_singleNumber_lowest(vector<int>& nums) 
    {
        if(nums.size()==1) return nums[0];
        vector<int> something = {};
        for (int i = 0; i < nums.size(); i++)
        {
            if (something.empty())
            {
                something.push_back(nums[i]);
                continue;
            }
            
            for (int j = 0; j < something.size(); j++)
            {
                if(nums[i]==something[j])//相等就证明要删除
                {
                    something.erase(something.begin()+j);
                }
            }
        }
        return something[0];       
    }
     
    
    //尼玛，位操作简直神了
    int _136_singleNumber_yihuo(vector<int> & nums)
    {
        int ret = 0;
        int len = nums.size();
        for (int i = 0; i < len; i++)
        {
            ret = nums[i]^ret;
        }
        return ret;
    }

//======================================================================================================
    //169、给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
    int _169_majorityElement_1(vector<int>& nums) 
    {
        map<int, int> count={};
        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
            if(count[nums[i]]>nums.size()/2)
                return nums[i];
        }        
        return 0;
    }

    int _169_majorityElement_2(vector<int>& nums) 
    {
        map<int, int> count={};
        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
        }        
        for (map<int, int>::iterator it = count.begin(); it != count.end(); it++)
        {
            if (it->second > nums.size()/2)
            {
                return it->first;
            }
        }
        return 0;
    }

//=========================================================================================================
    //461、两个整数之间的汉明距离指的是这两个数字对应二进制位不同的位置的数目。
    int _461_hammingDistance(int x, int y) 
    {

        return 1;
    }
};

int main()
{
    Solution *solution;

    //====================================================//
    //===============||    一些骚操作    ||===============//
    //===================================================//
    // 1、判断奇偶
    int i = 2;
    if (i & 1) //与1取和，如果i是偶数，则末尾也为1，则为真，所以
        cout<<"i是奇数"<<endl;

    // 2、交换两个数
    int a=1, b=2;
    a ^= b;//a=a^b
    b ^= a;//b=b^a=b^a^b=a, 因为异或是不一样就为1，所以相同两个数取异或就是0，任何数与0异或依旧为本身
    a ^= b;//a=a^b=a^b^a=b
    
    // 3、 取相反数
    int j = -11;
    cout<< (~j)+1 <<endl;//取反再加1，正常操作，记得给位操作加括号，否则他的优先级太低了

    // 4、求绝对值
    int z = j>>31;//取j的符号，若z是0则为正数，若z是-1则是负数
    cout<< ((z==0)?j:(~j+1)) <<endl;//方法1；
    cout<< (j^z)-z <<endl;//方法2：z若为0，j^0-z=j；z若为-1，j^(-1)-(-1)=对j取反加1，所以取了j的相反数

    // 5、高低位交换
    uint16_t m = 34520;
    uint16_t m_high = m>>8;
    uint16_t m_low = m<<8;
    cout<< (m_high | m_low) <<endl;
    //======================================//


    // test 136
    vector<int> nums_136 = {4,1,2,1,2};
    int result_136 = solution->_136_singleNumber_yihuo(nums_136);
    
    // test 169
    vector<int> nums_169 = {3,2,2};
    int result_169 = solution->_169_majorityElement_1(nums_169);

    // test 461

    return 0;
}
