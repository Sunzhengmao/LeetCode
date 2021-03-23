
//      2018/05/04 9:56:28
//      multimap-erase

// removes elements
#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include<vector>
#include<algorithm>
#include<unordered_set>

using namespace std;

typedef multimap<string, int, less<string>>  M;

void print(M& m){
    M::iterator it = m.begin();
    cout << "multimap:" << endl;
    while (it != m.end()){
        cout << it->first << "-" << it->second << endl;
        it++;
    }
}
int backtrace(vector<int> presum, vector<int> stones, int l, int r)
{
    if(l==r) return 0;
    if(l==r-1) return max(stones[l], stones[r]);
    if(stones[l]>stones[r])//alice移除r
    {
        int alice = presum[r-1]-presum[l]+stones[l];
        //l
        int bob_1 = presum[r-1]-presum[l+1]+stones[l+1];
        int diff_1 = alice-bob_1 + backtrace(presum, stones, l+1, r-1);
        
        //r-1
        int bob_2 = presum[r-2]-presum[l]+stones[l];
        int diff_2 = alice-bob_2 + backtrace(presum, stones, l, r-2);     
        
        int min1 = min(diff_1, diff_2);        
        return min1;
    }
    else//alice移除l
    {
        int alice = presum[r]-presum[l+1]+stones[l+1];
        //l+1
        int bob_1 = presum[r]-presum[l+2]+stones[l+2];
        int diff_1 = alice-bob_1 + backtrace(presum, stones, l+2, r);
        
        //r
        int bob_2 = presum[r-1]-presum[l+1]+stones[l+1];
        int diff_2 = alice-bob_2 + backtrace(presum, stones, l+1, r-1);
        
        int min2 = min(diff_1, diff_2);        
        return min2;
    }
    return 0;
    
}

class solution
{
public:
    int count = 0;
    void permute(vector<int>&nums, int l) 
    {
        if (l == nums.size() - 1) 
        {
            int i;
            for (i = 1; i <= nums.size(); i++) 
            {
                if (nums[i - 1] % i != 0 && i % nums[i - 1] != 0)
                    break;
            }
            if (i > nums.size()) 
            {
                count++;
            }
        }
        for (int i = l; i < nums.size(); i++) 
        {
            swap(nums, i, l);
            permute(nums, l + 1);
            swap(nums, i, l);
        }
    }
    void swap(vector<int>&nums, int x, int y) 
    {
        int temp = nums[x];
        nums[x] = nums[y];
        nums[y] = temp;
    }    
};

int lengthOfLongestSubstring(string s) 
{
    unordered_set<char> se;
    int n = s.size();
    int rpoint = 0; //右指针
    int num = 0;
    for(int i=0; i<n; i++)
    {
        if(i!=0)
        {
            se.erase(s[i-1]);
        }
        while(se.count(s[rpoint])==0 && rpoint < n)
        {
            se.insert(s[rpoint]);
            rpoint++;
        }
        num = max(num, rpoint-i);
    }
    return num;
}
int maximumUniqueSubarray(vector<int>& nums) 
{
    int ans = 0;
    int n = nums.size();
    unordered_set<int> myset;
    vector<int> presum(n, nums[0]);
    for(int i=1; i<n; ++i)
        presum[i] = presum[i-1]+nums[i];
    
    int rp = 0;
    for(int lp=0; lp<n; ++lp)
    {
        if(lp!=0)
            myset.erase(nums[lp-1]);
        while(rp<n && myset.count(nums[rp])==0)
        {
            myset.insert(nums[rp]);
            rp++;
        }
        ans = max(ans, presum[rp-1]-presum[lp]+nums[lp]);
    }
    return ans;
}


int eatenApples(vector<int>& apples, vector<int>& days) 
{
    int n = apples.size();
    int ans = 0;
    map<int, pair<int,int>> mymap;
    for(int i=0; i<n; ++i)
    {
        if(apples[i]!=0)
            mymap[i]={apples[i], days[i]};
        if(mymap.begin()!=mymap.end())
        {
            mymap.begin()->second.first--;
            if(mymap.begin()->second.first<=0) mymap.erase(mymap.begin()); 
            ans++;
        }
        auto iter = mymap.begin();
        while(iter != mymap.end())
        {
            iter->second.second--;
            if(iter->second.second<=0)  
                mymap.erase(iter++);
            else iter++;
        }
    }

    while(!mymap.empty())
    {
        if(mymap.begin()!=mymap.end())
        {
            mymap.begin()->second.first--;
            if(mymap.begin()->second.first==0) mymap.erase(mymap.begin()); 
            ans++;
        }
        auto iter = mymap.begin();
        while(iter != mymap.end())
        {
            iter->second.second--;
            if(iter->second.second==0)  
                mymap.erase(iter++);
            else iter++;
        }
    }
    return ans;

}

vector<int> findBall(vector<vector<int>>& grid) 
{
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> ans(cols, -1);
    int pre = 0;
    for(int i=0; i<cols; ++i) //第i个球
    {
        int row = 0;
        int col_now = i;
        int pre = grid[0][i];
        for(; row<rows-1; ++row)
        
        {
            if(pre == 1)
            {
                col_now += 1;
                if(grid[row][col_now]==-1)
                {
                    break;   
                }
                else
                {
                    pre = grid[row+1][col_now];                        
                }
            }
            else
            {
                col_now -= 1;
                if(grid[row][col_now]==1)
                {
                    break;
                }
                else
                {
                    pre = grid[row+1][col_now];
                }
            }
        }
        if(row==rows-2)
            ans[i]=col_now;          
    }
    return ans;

}

vector<int> searchRange(vector<int>& nums, int target) 
{
    int n = nums.size();
    int left = 0, right = n;
    vector<int> ans(2,-1);
    if(n==0) return ans;
    while(left < right)
    {
        int mid = left + ((right - left) >> 1);
        if(nums[mid] <= target)
            left = mid+1;
        else 
            right = mid;
    }
    ans[1] = nums[left-1]==target ? left-1 : -1; // upper
    left = 0; right = n;
    while(left < right)
    {
        int mid = left + ((right - left) >> 1);
        if(nums[mid] < target)
            left = mid+1;
        else 
            right = mid;
    }
    ans[0] = nums[left]==target ? left : -1; // lower
    return ans;
}

class Father {
    public:
    virtual void f() {
        cout<<"Father->f()"<<endl;
    }
};
class Son : public Father {
    public:
    virtual void f() {
        cout<<"Son->f()"<<endl;
    }
};

void func(const Father& fff) {
    cout<<"szm"<<endl;
}
//========================
int main()
{
    vector<int> stones = {481,905,202,250,371,628,92,604,836,338,676,734};

    // vector<int> input{1};
    // auto ans = searchRange(input, 0);
    Father objf;
    Son objs;

    Father* pf = &objf;
    Father* ps = &objs;

    Father* pf1 = &objf;
    auto res = dynamic_cast<Son*>(pf1);
    if(!pf1) {
        cout<<"null"<<endl;
    }
    func(objf);

    return 0;
}
