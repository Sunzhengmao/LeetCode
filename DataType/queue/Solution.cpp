#include <iostream>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

class MyStack
{
public:
    MyStack() {};
    ~MyStack() {};
    
public:

    queue<int> myqueue;

    /** Push element x onto stack. */
    void push(int x) {
        myqueue.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int lastOne1=0;
        queue<int> temp;
        int size = myqueue.size();
        for(int i=0; i<size; i++)
        {
            lastOne1 = myqueue.front();
            myqueue.pop();
            if(i<size-1) temp.push(lastOne1);            
        }
        myqueue = temp;
        return lastOne1;
    }
    
    /** Get the top element. */
    int top() {
        int lastOne;
        queue<int> temp = myqueue;
        while(!temp.empty())
        {
            lastOne = temp.front();
            temp.pop();            
        }
        return lastOne;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return myqueue.empty();
    }
};

int main()
{
    MyStack mystack;
    mystack.push(1);
    mystack.push(2);
    mystack.push(3);
    bool empty = mystack.empty();
    int i = mystack.top();
    int j = mystack.pop();

    int l = 0;
    queue<int> myqueue;
    myqueue.push(1);
    myqueue.push(2);
    myqueue.push(3);
    myqueue.push(4);
    myqueue.push(5);

    int k = myqueue.back();
    myqueue.emplace(6);
    int temp = myqueue.front();
    myqueue.pop();
    myqueue.push(7);
    int size = myqueue.size();
    // myqueue.swap(myqueue);

    stack<int> mstack;
    mstack.emplace(1);
    mstack.push(2);
    mstack.emplace(3);
    int ii = mstack.top();
    mstack.pop();
    size = mstack.size();

    cout<<'1'<<endl;
}