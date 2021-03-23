#include <functional>
#include <stdio.h>
#include <utility>
#include <vector>
#include <stack>
#include <iostream>
#include <queue>

#include <map>
// #include <pair>
using namespace std;
void display(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int array[], int x, int y) {
    int key  = array[x];
    array[x] = array[y];
    array[y] = key;
}

// 从大到小排序
// void Down(int array[], int i, int n) {
//     int child = 2 * i + 1;
//     int key   = array[i];
//     while (child < n) {
//         if (child + 1 < n && array[child] > array[child + 1]) {
//             child++;
//         }
//         if (key > array[child]) {
//             swap(array, i, child);
//             i = child;
//         } else {
//             break;
//         }
//         child = child * 2 + 1;
//     }
// }

// 从小到大排序
void Down(int array[], int i, int n) { // 最后结果就是大顶堆
    int parent = i;                    // 父节点下标
    int child  = 2 * i + 1;            // 子节点下标
    while (child < n) {
        if (child + 1 < n && array[child] < array[child + 1]) { // 判断子节点那个大，大的与父节点比较
            child++;
        }
        if (array[parent] < array[child]) { // 判断父节点是否小于子节点
            swap(array, parent, child);     // 交换父节点和子节点
            parent = child;                 // 子节点下标 赋给 父节点下标
        }
        child = child * 2 + 1; // 换行，比较下面的父节点和子节点
    }
}

void BuildHeap(int array[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) { // 倒数第二排开始, 创建大顶堆，必须从下往上比较
        Down(array, i, size);                 // 否则有的不符合大顶堆定义
    }
}

void HeapSort(int array[], int size) {
    printf("初始化数组：");
    BuildHeap(array, size); // 初始化堆
    display(array, size);   // 查看初始化结果
    for (int i = size - 1; i > 0; i--) {
        swap(array, 0, i); // 交换顶点和第 i 个数据
                           // 因为只有array[0]改变，其它都符合大顶堆的定义，所以可以从上往下重新建立
        Down(array, 0, i); // 重新建立大顶堆

        printf("排序的数组：");
        display(array, size);
    }
}

void quickSort_iter(vector<int>& nums) {
    stack<pair<int,int>> s;
    s.push(make_pair(0, nums.size()-1));
    while(s.size()) {
        int left = s.top().first;
        int right = s.top().second;
        s.pop();
        int l = left;
        int r = right;
        int partition = nums[left];
        while(l < r) {
            while(l<r && nums[r]>=partition) r--;
            while(l<r && nums[l]<=partition) l++;
            if(l<r) swap(nums[r], nums[l]);
        }
        swap(nums[l], nums[left]);
        if(left<l-1) s.push(make_pair(left, l-1));
        if(l+1<right) s.push(make_pair(l+1, right));
    }
}

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if(k > input.size()) return {};
        if(k == input.size()) return input;
        vector<int> arr(input.begin(), input.begin()+k);
        heapSort(arr);
        for(int i=k; i<input.size(); ++i) {
            if(arr[0] > input[i]) {
                arr[0] = input[i];
                // swap(arr[k-1], arr[0]);
                sink(arr, 0, k);
            }
        }
        return arr;
    }
    void heapSort(vector<int>& arr) {
        if(arr.size()<=1) return;
        int n = arr.size();
        for(int i=n/2-1; i>=0; --i) {
            sink1(arr, i, n);
        }
        for(int i=n-1; i>0; --i) {
            swap(arr[i], arr[0]);
            sink1(arr, 0, i);
        }
    }
    void sink(vector<int>& arr, int parent, int n) {
        int child = 2*parent + 1;
        while(child<n) {
            if(child+1<n && arr[child]<arr[child+1]) {
                child++;
            }
            if(arr[parent] < arr[child]) {
                swap(arr[parent], arr[child]);
                parent = child;
            }
            child = 2*child + 1;
        }
    }
    void sink1(vector<int>& arr, int parent, int n) {
        int child = 2*parent + 1;
        while(child<n) {
            if(child+1<n && arr[child]>arr[child+1]) {
                child++;
            }
            if(arr[parent] > arr[child]) {
                swap(arr[parent], arr[child]);
                parent = child;
            }
            child = 2*child + 1;
        }
    }    
    int findKth(vector<int> input, int n, int k) {
        if(k > input.size()) return {};
        priority_queue<int, vector<int>, greater<int>> q;
        for(int i=0; i<n; ++i) {
            q.push(input[i]);
            if(q.size() > k) {
                q.pop();
            }
        }
        // for(int i=0; i<input.size(); ++i){
        //     cout<<q.top()<<endl;
        //     q.pop();
        // }
            
        return q.top();
    }
};

class Solution1 {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        typedef long long ll;
        const ll mod = 1e9 + 7;
        map<int, int, greater<int>> m0, m1;
        if(orders.size() == 1) return ll(orders[0][1]) % mod;
        for(auto& order:orders) {
            int price = order[0];
            int& amount = order[1];
            if(order[2] == 0) {
                auto iter = m1.lower_bound(price), end = m1.end();
                while(iter != end && amount > 0) {
                    if(iter->first <= price) {
                        int temp = min(iter->second, amount);
                        iter->second -= temp;
                        amount -= temp;
                        iter++;
                    }
                    // else break;
                }
                if(amount > 0) {
                    m0[price] += amount;
                }
            }
            if(order[2] == 1) {
                auto iter = m0.begin(), end = m0.end();
                while(iter != end && amount > 0) {
                    if(iter->first >= price) {
                        int temp = min(iter->second, amount);
                        iter->second -= temp;
                        amount -= temp;
                        iter++;
                    }
                    else break;
                }
                if(amount > 0) {
                    m1[price] += amount;
                }
            }
        }
        ll res = 0;
        for(auto iter=m0.begin(); iter!=m0.end(); ++iter) {
            res += iter->second;
            res %= mod;
        }
        for(auto iter=m1.begin(); iter!=m1.end(); ++iter) {
            res += iter->second;
            res %= mod;
        }
        return res;        

    }
};

int main() {
    int array[] = {100, 20, 10, 1, 2, 1, 2, 0, 0};
    // int array[] = {49, 38, 65, 97, 76, 13, 27, 49, 10};
    int size    = sizeof(array) / sizeof(int);

    vector<int> input{4,5,1,6,2,7,3,8};
    Solution solution;
    vector<int> output = solution.GetLeastNumbers_Solution(input, 4);
    int res = solution.findKth(input, input.size(), 2);

    Solution1 s1;
    vector<vector<int>> zhousai;
    zhousai.push_back(vector<int>{12,16,1});
    zhousai.push_back(vector<int>{28,4,0});
    zhousai.push_back(vector<int>{19,29,1});
    zhousai.push_back(vector<int>{7,10,0});
    zhousai.push_back(vector<int>{29,26,0});
    zhousai.push_back(vector<int>{4,19,0});
    zhousai.push_back(vector<int>{18,10,0});
    zhousai.push_back(vector<int>{3,17,1});
    zhousai.push_back(vector<int>{19,26,1});
    // [[12,16,1],[28,4,0],[19,29,1],[7,10,0],[29,26,0],[4,19,0],[18,10,0],[3,17,1],[19,26,1]]
    int res1 = s1.getNumberOfBacklogOrders(zhousai);
    // vector<int> input{5,2,3,1};
    // quickSort_iter(input);

    // 打印数据
    // printf("%d \n", size);
    // printf("排序前数组：");
    // display(array, size);
    // HeapSort(array, size);

    return 0;
}