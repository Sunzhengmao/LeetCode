#include <iostream>
#include <thread>
#include "Semaphore.h"
 
std::mutex m;
szm::semaphore ba, cb, dc;
 
void a()
{
    ba.wait();  // b --> a
    // std::lock_guard<std::mutex> lock{m};
    std::cout << "thread a" << '\n';
}
void b()
{
    cb.wait();  // c --> b
    // std::lock_guard<std::mutex> lock{m};
    std::cout << "thread b" << '\n';
    ba.signal();  // b --> a
}
void c()
{
    dc.wait();  // d --> c
    // std::lock_guard<std::mutex> lock{m};
    std::cout << "thread c" << '\n';
    cb.signal();  // c --> b
}
void d()
{
    // std::lock_guard<std::mutex> lock{m};
    std::cout << "thread d" << '\n';
    dc.signal();  // d --> c
}
 
int main()
{
    ba.init(0);
    cb.init(0);
    dc.init(0);
    std::thread th1{a}, th2{b}, th3{c}, th4{d};
   
    th1.join();
    th2.join();
    th3.join();
    th4.join();
   
    std::cout << "thread main" << std::endl;
   
    return 0;
}