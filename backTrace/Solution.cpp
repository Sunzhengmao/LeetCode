#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_set>
// #include
using namespace std;

//46、全排列
class Solution46
{
private:
    vector<int> path;
    vector<int> visited;
    void backTrace_46(vector<int> nums, int cnt)
    {
        if(path.size() == cnt)
        {
            ans.push_back(path);
            return;
        }

        for(int i=0; i<nums.size(); i++)
        {
            if(visited[i] == 1) continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            backTrace_46(nums, cnt);
            visited[i] = 0;
            path.pop_back();
        }
    }

public:
    vector<vector<int> > ans;
    vector<vector<int>> permute(vector<int>& nums) 
    {
        visited = vector<int>(nums.size(), 0);
        backTrace_46(nums, nums.size());
        return ans;
    }
};


//47、带重复数字的全排列
class Solution47
{
private:
    vector<int> path;
    vector<int> visited;
    void backTrace_46(vector<int> nums)
    {
        if(path.size() == nums.size())
        {
            ans.push_back(path);
            return;
        }

        for(int i=0; i<nums.size(); i++)
        {
            if(visited[i] == 1) continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            backTrace_46(nums);
            path.pop_back();
            visited[i] = 0;
        }
    }

public:
    vector<vector<int> > ans;
    vector<vector<int>> permute(vector<int>& nums) 
    {
        visited = vector<int>(nums.size(), 0);
        backTrace_46(nums);
        return ans;
    }
};

//39 组合总和
class Solution39
{
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        visited = vector<int>(candidates.size(), 0);
        backTrace(candidates, target, 0);
        return ans;
    }  
private:
    vector<int> visited;
    vector<int> path;
    vector<vector<int>> ans;
    map<set<int>, int> map_set;
    int index = 0;

    void backTrace(vector<int> nums, int target, int begin)
    {
        if(target<0) 
            return;
        if(target == 0)
        {
            ans.push_back(path);
        }

        for(int i=begin; i<nums.size(); i++)
        {
            path.push_back(nums[i]);
            backTrace(nums, target-nums[i], i);
            path.pop_back();
        }
    }
};

class Solution40 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        visited = vector<int>(candidates.size(), 0);
        // sort(candidates.begin(), candidates.end());
        backTrace(candidates, target, 0);
        return ans;
    }  
private:
    vector<int> visited;
    vector<int> path;
    vector<vector<int>> ans;
    map<set<int>, int> map_set;
    int index = 0;

    void backTrace(vector<int> nums, int target, int begin)
    {
        if(target<0) 
            return;
        if(target == 0)
        {
            ans.push_back(path);
        }

        for(int i=0; i<nums.size(); i++)
        {
            if(i>0 && nums[i]==nums[i-1] && visited[i-1]==0 ) continue;
            if(i<begin) continue;
            if(visited[i]==1) continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            backTrace(nums, target-nums[i], i);
            visited[i] = 0;
            path.pop_back();
        }
    }
};

class Solution216 {
public:
    vector<vector<int>> combinationSum3(int target, int cnt) {
        visited = vector<int>(9, 0);
        // sort(candidates.begin(), candidates.end());
        backTrace(vector<int>{1,2,3,4,5,6,7,8,9}, target, 0, cnt);
        return ans;
    }  
private:
    vector<int> visited;
    vector<int> path;
    vector<vector<int>> ans;
    map<set<int>, int> map_set;
    int index = 0;

    void backTrace(vector<int> nums, int target, int begin, int cnt)//path中必须只有cnt个数
    {
        if(target<0 || path.size() > cnt) 
            return;
        if(target == 0 && path.size() == cnt)
        {
            ans.push_back(path);
            return;
        }

        for(int i=begin; i<nums.size(); i++)
        {
            // if(i>0 && nums[i]==nums[i-1]) continue;
            // if(visited[i]==1) continue;
            // visited[i] = 1;
            path.push_back(nums[i]);
            backTrace(nums, target-nums[i], i+1, cnt);
            // visited[i] = 0;
            path.pop_back();
            if(target == nums[i] && path.size() == cnt)
                break;
            if(path.size() > cnt)
                break;
        }
    }
};

//著名的N皇后问题，现在挑战下
class Solution51 {
public:
    vector<vector<string>> solveNQueens(int n) {
        visited = vector<int>(n, 0);
        backTrace(n);
        return ans;
    }  
private:
    vector<int> visited;
    vector<int> path;
    vector<vector<string>> ans;
    int first_line = 1;

    void backTrace(int n)//path中必须只有cnt个数
    {
        if(path.size() > n)
            return;
        if(path.size() == n)
        {
            vector<string> temp1;
            for(auto i : path)
            {
                string temp;
                for(int j=0; j<n; j++)
                {
                    if(i==j)
                        temp+="Q";
                    else
                        temp+=".";
                }
                temp1.push_back(temp);
            }
            ans.push_back(temp1);
            return;
        }

        for(int col=0; col<n; col++)
        {   
            if(!path.empty() && ~in_line(col)) continue;
            if(visited[col]==1) continue;
            visited[col] = 1;
            path.push_back(col);
            backTrace(n);
            visited[col] = 0;
            path.pop_back();
        }
    }

    bool in_line(int col)
    {
        int curr_row = path.size();
        int curr_col = col;
        for(int i=0; i<path.size(); i++)
        {
            int row = i;
            // int col = path[i];
            if(row - curr_row == path[i] - curr_col)
                return true;
        }
        return false;
    }
};


int main()
{
    Solution46 s46;
    vector<int>input46{1,2,3};
    // vector<vector<int>> ans46 = s46.permute(input46);

    Solution47 s47;
    vector<int>input47{1,1,2};
    // vector<vector<int>> ans47 = s47.permute(input47);

    Solution39 s39;
    vector<int>input39{2,3,6,7};
    // vector<vector<int>> ans39 = s39.combinationSum(input39, 7);

    Solution51 s51;
    vector<vector<string>> ans51 = s51.solveNQueens(4);

    set<int> a{1,2,3};
    set<int> b{2,3,1};
    bool right = (a==b);
    return 1;



}
