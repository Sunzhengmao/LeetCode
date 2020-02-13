#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Point{
    Point(int x_, int y_) : x(x_), y(y_) {};
    int x;
    int y;
};

struct KD_tree{
    KD_tree(Point point_): point(point_), leftNode(NULL), rightNode(NULL) {};

    Point point;
    KD_tree* leftNode;
    KD_tree* rightNode;
};

int findCut(vector<int>& nums, int left, int right);
int findKthMin(vector<int> &nums, int left, int right, int K);
KD_tree* generateKDTree(vector<Point>& nums, int direction);

int findKthMin(vector<int> &nums, int left, int right, int K)
{
    if (left > right)
    {
        cerr<<"nums' left is bigger than right"<<endl;
        return (-1);
    }
        
    if (left == right)
        return nums[left];

    int cut = findCut(nums, left, right);

    if (cut == K)
    {
        return nums[K];
    }
    if (cut > K)    
    {
        return findKthMin(nums, left, cut-1, K);
    }
    if (cut < K)
    {
        return findKthMin(nums, cut+1, right, K-cut);
    }
    return 0;
}

int findCut(vector<int>& nums, int left, int right)
{    
    int i = left;
    int j = right;
    int tmp = nums[j];

    for (int k = left; k < right; k++)
    {
        if (nums[k] <= tmp)
        {
            swap(nums[k], nums[i]);
            i++;
        }
        
    }

    swap(nums[j], nums[i]);
    
    return i;
}

KD_tree* generateKDTree(vector<Point>& nums, int direction)
{
    if (nums.size() == 0)  return NULL;
    if (nums.size() == 1)  return new KD_tree(nums[0]);

    const int N = nums.size();
    vector<int> x_location, y_location;
    x_location.reserve(2*N);
    y_location.reserve(2*N);

    for (int i = 0; i < nums.size(); i++)
    {
        x_location.push_back(nums[i].x);
        y_location.push_back(nums[i].y);
    }
    vector<int> x_location_copy(x_location);//为防止出现findKthMin修改nums数组的值，又复制了一个新的
    vector<int> y_location_copy(y_location);

    vector<int>::iterator iter_x = x_location.begin();
    vector<int>::iterator iter_y = y_location.begin();
    
    vector<Point> leftNums={}, rightNums={};
    leftNums.reserve(N);
    rightNums.reserve(N);

    KD_tree* root = new KD_tree(Point(0,0));
    
    if (direction & 1)//那就先x方向咯
    {
        const int nY = y_location_copy.size();
        root->point.y = findKthMin(y_location_copy, 0, nY-1, int(nY/2));

        //从x_location和y_location中删去y_value这个点,并且按照大小分为两个向量
        for (; iter_y != y_location.end(); iter_x++, iter_y++)
        {
            if (root->point.y > *iter_y)
            {
                leftNums.push_back(Point(*iter_x, *iter_y));
                continue;
            }
            if (root->point.y < *iter_y)
            {
                Point point(*iter_x, *iter_y);
                rightNums.push_back(point);
                continue;
            }
            
            root->point.x = *iter_x;
        }
    }
    if (! (direction & 1))
    {
        const int nX = x_location_copy.size();
        root->point.x = findKthMin(x_location_copy, 0, nX-1, int(nX/2));

        //从x_location和y_location中删去x_value这个点,并且按照大小分为两个向量
        for (; iter_x != x_location.end(); iter_x++, iter_y++)
        {
            if (root->point.x > *iter_x)
            {
                leftNums.push_back(Point(*iter_x, *iter_y));
                continue;
            }
            if (root->point.x < *iter_x)
            {
                rightNums.push_back(Point(*iter_x, *iter_y));
                continue;
            }
            
            root->point.y = *iter_y;
        }
    }

    direction++;
    root->leftNode = generateKDTree(leftNums, direction);
    root->rightNode = generateKDTree(rightNums, direction);
    
    return root;
}

int main()
{
    const int N = 6;

    vector<Point> kd_tree={};
    kd_tree.push_back(Point(2,3));
    kd_tree.push_back(Point(5,4));
    kd_tree.push_back(Point(9,6));
    kd_tree.push_back(Point(4,7));
    kd_tree.push_back(Point(8,1));
    kd_tree.push_back(Point(7,2));
    
    KD_tree* root = generateKDTree(kd_tree, 0);

    cout<<"hello world! "<<endl;

    return 1;

}

