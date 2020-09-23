#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
char random2(char s1, char s2);
string modifyString(string s); 
int numTriplets(vector<int>& nums1, vector<int>& nums2) ;
int son(vector<int>& nums1, vector<int>& nums2);

string modifyString(string s) 
{
    int i=0;
    if(s[i]=='?')
    {
        s[i]='a';
        while (s[i]!=s[i+1])
            s[i] = 'a'-'0'+1+'0';
    }
    i++;
    for(; i<s.size()-1; i++)
    {
        if(s[i]=='?')
        {
            s[i] = 'a';
            while (s[i]==s[i-1] || s[i]==s[i+1])
            {
                s[i] = 'a'-'0'+1+'0';
            }
        }
    }
    if(s[i]=='?')
    {
        s[i]='a';
        while (s[i]!=s[i-1])
            s[i] = 'a'-'0'+1+'0';
    }
    return s;
}

int numTriplets(vector<int>& nums1, vector<int>& nums2) 
{
    return son(nums1, nums2) + son(nums2, nums1);
}

int son(vector<int>& nums1, vector<int>& nums2) 
{
    int cnt=0, cnt_i=0;
    map<long long, int> hash;
    for(int i=0; i<nums1.size(); i++)
    {
        long long a1 = (long long) (nums1[i]) * (long long) (nums1[i]);
        if (hash.find(a1) != hash.end())
        {
            cnt+=hash[a1];
            continue;
        }
        for(int j=0; j<nums2.size(); j++)
        {
            for(int k=j+1; k<nums2.size(); k++)
            {
                long long b1 = (long long)(nums2[j]) * (long long)(nums2[k]);
                if (a1 == b1)
                    cnt_i++;
            }
        }
        cnt += cnt_i;
        hash[a1] = cnt_i;
    }
    return cnt;
}

int main()
{
    string s = "?zs";
    // string s_q1 = modifyString(s);

    // char a = 'a';
    // a = a - '0' + 1 + '0';
    // int i=1;
    // return 1;

    vector<int> n1{1,3,1,2};
    vector<int> n2{2,3,5,3,2};
    int a = numTriplets(n1, n2);
}