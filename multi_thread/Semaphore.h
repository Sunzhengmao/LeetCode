#include <mutex>
#include <condition_variable>
using namespace std;

namespace szm
{
    
class semaphore
{
public:
    semaphore() : weakups_(0) {}
    ~semaphore() {}

    void init(int count = 1)
    {
        count_ = count;
    }

    void wait()
    {
        unique_lock<mutex> lk(Mu_);
        if (--count_ < 0)
        {   // 这里有点坑哦，必须是weakup大于0之后，我才能继续往下走，而且我往下走了才能用掉以此weakup，不能我还没用呢就丢掉以此weakup
            con_.wait(lk, [this]() {return weakups_>0;}); 
            weakups_ --;
        }
    }

    void signal()
    {
        unique_lock<mutex> lk(Mu_);
        if (++count_<=0)
        {
            weakups_++;
            con_.notify_one();
        }
    }

private:
    int count_;
    int weakups_;
    mutex Mu_;
    condition_variable con_;

};
}

// #include <mutex>
// #include <condition_variable>
 
// namespace szm{
//     class semaphore {
//     public:
//         // semaphore(int value=1): count(value), wakeups(0) {}
//         semaphore(): wakeups(0) {}
//         ~semaphore() {}

//         void init(int value=1)
//         {
//             count = value;
//         }
       
//         void wait(){
//             std::unique_lock<std::mutex> lock{mutex};
//             if (--count<0) { // count is not enough ?
//                 condition.wait(lock, [&]()->bool{ return wakeups>0;}); // suspend and wait ...
//                 --wakeups;  // ok, me wakeup !
//             }
//         }
//         void signal(){
//             std::lock_guard<std::mutex> lock{mutex};
//             if(++count<=0) { // have some thread suspended ?
//                 ++wakeups;
//                 condition.notify_one(); // notify one !
//             }
//         }
       
//     private:
//         int count;
//         int wakeups;
//         std::mutex mutex;
//         std::condition_variable condition;
//     };
// };