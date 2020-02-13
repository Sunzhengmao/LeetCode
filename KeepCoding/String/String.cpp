#include <iostream>
#include <string>
#include <vector>
using namespace std;



//这节课讲了一个算法：检测子串
vector<int> generateMask(string s);

//1、暴力匹配法
bool detectSubString(string superString, string subString)
{
    if (subString.size() > superString.size()) return false;

    for (size_t i = 0; i < superString.size(); i++)
    {
        for (size_t j = 0; j < subString.size(); j++)
        {
            if (superString[i] != subString[j])
            {
                return false;
            }
        }
    }
    return true;    
}

//2.1 KMS算法，每次只考虑子串
vector<int> generateMask(string s)
{
    const int N = s.size();
    if (N == 0) return {};

    bool mask = false;
    int initial = -1;
    
    vector<int> result = {initial};
    
    for (int i = 1; i < N; i++)
    {
        if (s[i] == s[i-1])
        {
            result.push_back(++initial);
            mask = true;
        }
        else
        {
            if (mask)
            {
                result.push_back(++initial);
                initial = -1;
                mask = false;
            }
            else
            {
                result.push_back(-1);
                initial = -1;
            }
        }
    }
    return result;
}
//2.2 这次考虑父字符串
int locInSupString(string sups, string subs)
{
    if (sups.size() < subs.size()) return -1;

    vector<int> mask = generateMask(subs);

    int i=0, j=0;
    for (; i < sups.size(); i++, j++)
    {          
        if (sups[i] != subs[j])
        {
            j = mask[j];
            i--;
            j--;
            continue;
        }        
        
        if (j == subs.size()-1)
        {
            return i-j;
        }
    }

    return -1;
}
int main()
{
    string s = "aaabcdd";
    vector<int> result = generateMask(s);

    string supString = "abcdefabcdeff";
    string subString = "abcdeff";
    int location = locInSupString(supString, subString);

    cout<<"hello world: "<<location<<endl;
    return 1;
}