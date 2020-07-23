#include <iostream>
#include <vector>
using namespace std;

int main()
{
    float fx = 100.f;
    float fy = 200.f;
    float ux = 1.f;
    float uy = 2.f;
    float cv_K[3*3];
    cv_K[0*3 + 0] = fx;
    cv_K[1*3 + 1] = fy;
    cv_K[0*3 + 2] = ux;
    cv_K[1*3 + 2] = uy;
    float* pdata = &cv_K[0];

    float K[3][3] = {{1,2,3}, {2,4,6},{3,6,9}};
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            cout<<K[i][j]<<endl;
        }
        
    }
    
    vector<int> result;
    result.
    return 0;
}