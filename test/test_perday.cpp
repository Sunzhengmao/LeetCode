#include<iostream>
#include<vector>
using namespace std;
class test_perday
{
private:
    vector<vector<int>> result; // 存放符合条件结果的集合
    vector<int> path; // 用来存放符合条件结果
    void backtracking(int n, int k, int startIndex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        // 这个for循环有讲究，组合的时候 要用startIndex，排列的时候就要从0开始
        for (int i = startIndex; i <= n; i++) {
            path.push_back(i); // 处理节点 
            backtracking(n, k, i + 1);
            path.pop_back(); // 回溯，撤销处理的节点
        }
    }
public:

    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return result;
    }

private:
    /* data */
public:
    test_perday(/* args */);
    ~test_perday();

    vector<vector<int>> combine_myself(int n, int k) 
    {
        if(n<1 || k<1 || n<k) return {};

        vector<vector<int> > ans11;
        for(int i=0; i<k; i++)
        {
            ans11.push_back(vector<int>{i+1});
        }
        if(n==k) return ans11;

        vector<vector<int> > ans;
        int cnt = n-k+1;
        for(int i=1; i<=cnt; i++)
        {
            ans.push_back(vector<int>{i});
        }

        // 第二个开始了
        for(int j=2; j<=k; j++)
        {
            int n_i = n-k+j;
            // 把原来的取出来，找到最后一个（最大的），
            int size = ans.size();
            for(int i=0; i<size; i++)
            {
                vector<int> ans_i = ans[i];
                int max = ans_i[ans_i.size()-1];
                while(max < n_i)
                {
                    vector<int> ans_j = ans_i;
                    ans_j.push_back(++max);
                    ans.push_back(ans_j);
                }
            }
        }
        // vector<vector<int> > result
        return ans;
    }   
};

test_perday::test_perday(/* args */)
{
}

test_perday::~test_perday()
{
}


int main()
{
    test_perday solution;
    vector<vector<int>> test_0908 = solution.combine(4,3);

    return 1;
}