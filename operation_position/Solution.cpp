#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include <math.h>
using namespace std;

class Solution
{
//==============================================================
//位操作的几种：①异或；②奇数位与偶数位；③每位判断是0还是1；④每位输出
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
        int n = x^y;
        int n_ji = n & 0xAAAAAAAA; //1010 1010 1010 1010
        int n_ou = n & 0x55555555; //0101 0101 0101 0101
        n = (n_ji>>1) + n_ou;
        n_ji = n & 0xCCCCCCCC;     //1100 1100 1100 1100
        n_ou = n & 0x33333333;
        n = (n_ji>>2) + n_ou;
        
        n_ji = n & 0xF0F0F0F0;
        n_ou = n & 0x0F0F0F0F;
        n = (n_ji>>4) + n_ou;

        n_ji = n & 0xFF00FF00;
        n_ou = n & 0x00FF00FF;
        n = (n_ji>>8) + n_ou;

        n_ji = n & 0xFFFF0000;
        n_ou = n & 0x0000FFFF;
        return (n_ji>>16) + n_ou;
    }

//=========================================================================================================
    //输出一个二进制数字
    template <class T>  
    void PrintfBinary(T a)  
    {   
        for (int i = sizeof(a) * 8 - 1; i >= 0; --i)  
        {  
            if ((a >> i) & 1)  
                putchar('1');  
            else   
                putchar('0');  
            if (i % 4 == 0)  
                putchar(' ');  
        }  
        putchar('\n');  
    } 

//=========================================================================================================
    //268、给定一个包含 0, 1, 2, ..., n 中 n 个数的序列，找出 0 .. n 中没有出现在序列中的那个数。
    int _268_missingNumber_shabi(vector<int>& nums) 
    {
        int sum = 0;
        int i = 0;
        for (; i < nums.size(); i++)
        {
            sum+=nums[i]-i;
        }
        return i-sum;        
    }

    int _268_missingNumber_operator(vector<int>& nums)
    {
        int result = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            result^=nums[i];
            result^=i;
        }   
        return result;
    }

//=========================================================================================================
    //231、给定一个整数，编写一个函数来判断它是否是 2 的幂次方。
    bool _231_isPowerOfTwo(int n) 
    {
        int num_1 = 0;
        while (n)
        {
            if (n & 1) num_1++;
            if (num_1 > 1) return false;
            n = n >> 1;
            PrintfBinary(n);
        }
        return num_1==1? true:false;     
    }

    bool _231_isPowerOfTwo_others(int n)
    {
        if(n<=0) return false;
        if((n&(n-1))==0) return true;
        return false;  
    }

//========================================================================================================
    //389、给定两个字符串s和t，字符串t随机位置添加一个字母。请找出在t中被添加的字母。
    char _389_findTheDifference(string s, string t) 
    {
        char result = t[t.size()-1];
        for (int i = 0; i < s.size(); i++)
        {
            result ^= s[i];
            result ^= t[i];
        }
        return result;
        
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
    cout<< sizeof(int) <<endl;
    cout<< sizeof(m) <<endl;
    cout<< sizeof(uint16_t) <<endl;

    // 6、二进制逆序
    uint16_t n = 34520;
    solution->PrintfBinary(n);
    // cout<<bitset<sizeof(n)*8>(n)<<endl;这也是输出二进制数字的方法，但是没有空格
    uint16_t n_ji = n & 0xAAAA;//1010 1010 1010 1010只取了奇数位
    uint16_t n_ou = n & 0x5555;//0101 0101 0101 0101只取了偶数位
    n = (n_ji>>1) | (n_ou<<1); //实现了每2位为一组的交换
    n_ji = n & 0xCCCC;         //1100 1100 1100 1100
    n_ou = n & 0x3333;         //0011 0011 0011 0011
    n = (n_ji>>2) | (n_ou<<2); //实现了每4位为一组的交换
    n_ji = n & 0xF0F0;         //1111 0000 1111 0000
    n_ou = n & 0x0F0F;         //0000 1111 0000 1111
    n = (n_ji>>4) | (n_ou<<4); //实现了每8位为一组的交换
    n_ji = n & 0xFF00;         //1111 1111 0000 0000
    n_ou = n & 0x00FF;         //0000 0000 1111 1111
    n = (n_ji>>8) | (n_ou<<8);
    cout<< n <<endl;

    // 7、二进制数1的个数
    uint16_t g = 34520;
    solution->PrintfBinary(g);
    uint16_t g_ji = g & 0xAAAA; //1010 1010 1010 1010
    uint16_t g_ou = g & 0x5555; //0101 0101 0101 0101
    g = (g_ji>>1) + g_ou;
    solution->PrintfBinary(g);
    g_ji = g & 0xCCCC;          //1100 1100 1100 1100
    g_ou = g & 0x3333;          //0011 0011 0011 0011
    g = (g_ji>>2) + g_ou;
    solution->PrintfBinary(g);
    g_ji = g & 0xF0F0;          //1111 0000 1111 0000
    g_ou = g & 0x0F0F;          //0000 1111 0000 1111
    g = (g_ji>>4) + g_ou;
    solution->PrintfBinary(g);
    g_ji = g & 0xFF00;          //1111 1111 0000 0000
    g_ou = g & 0x00FF;          //0000 0000 1111 1111
    g = (g_ji>>8) + g_ou;
    solution->PrintfBinary(g);
    cout<< g <<endl;
    //====================================================//
    //===============||    骚操作结束    ||===============//
    //===================================================//


    // test 136
    vector<int> nums_136 = {4,1,2,1,2};
    int result_136 = solution->_136_singleNumber_yihuo(nums_136);
    
    // test 169
    vector<int> nums_169 = {3,2,2};
    int result_169 = solution->_169_majorityElement_1(nums_169);

    // test 231
    int n_231 = -16;
    bool result_231 = solution->_231_isPowerOfTwo(n_231);

    // test char
    char a_char = 'a';
    solution->PrintfBinary(a_char);

    // test int of 1
    // -1    -> 1111 1111 1111 1111 1111 1111 1111 1111
    // 2^31  -> 0111 1111 1111 1111 1111 1111 1111 1111 
    // -2^31 -> 1000 0000 0000 0000 0000 0000 0000 0000
    int a_int = pow(2, 31);
    for (int i = 0; i < 100; i++)
    {   
        solution->PrintfBinary(a_int);
        a_int++;
    }
    
    int a_ = pow(2, 32);
    int b_int = -1 *pow(2, 31);
    solution->PrintfBinary(a_int);
    solution->PrintfBinary(b_int);

    return 0;
}
