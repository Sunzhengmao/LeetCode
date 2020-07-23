#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <string>
#include <Windows.h>
#include <process.h>
// #include <pthread>
#include "Semaphore.h"

using namespace std;

/**
 * 开辟一个线程并不难，难的是线程之间数据的同步和互斥
 * 1. 互斥锁：          最直接了当，直接lock和unlock
 * 2，条件变量＋互斥锁:  有一个科学的等待机制，等待别人的唤醒，然后进行下一步。可以先下一步再等待，这样就等同于唤醒自己，一般都会加上防止虚假唤醒的机制
 * 3. 信号量：          有很多互斥锁，可以实现被n个(n>1)线程共同访问  超过n了就得等，使用时可以先给他一个子，然后可以用，用完再给
 *                      这样可以在不同函数内操作
 */

//------------------------------
//     用互斥锁+条件变量实现    
//------------------------------

// =================================================================================================================================
// 1115、两个不同的线程将会共用一个 FooBar 实例。其中一个线程将会调用 foo() 方法，另一个线程将会调用 bar() 方法。
//       请设计修改程序，以确保 "foobar" 被输出 n 次。
class FooBar {
private:
    int n;
    std::condition_variable con;
    std::mutex Mu;
    int count = 1;

public:
    FooBar(int n) 
    {
        this->n = n;
        m_bar.lock();
        // m_foo.lock();
        // std::thread thread_foo(FooBar::foo());
        // std::thread thread_bar(this->bar());
        // foo();

    }

    void start()
    {
        std::thread t_foo(& FooBar::foo, this);
        std::thread t_bar(& FooBar::bar, this);

        t_foo.join();
        t_bar.join();
    }
    void foo() 
    {
        
        for (int i = 0; i < n; i++) 
        {
            
        	// 解法1. 直接用锁来做，但是这样有违only the owner can unlock the mutex规则，容易产生死锁 
            // printFoo() outputs "foo". Do not change or remove this line.
            m_foo.lock();
        	printf("Foo");
            m_bar.unlock();


            // 解法2. 用条件变量+锁的方式试一下
            // std::unique_lock<std::mutex> lk(Mu);
            // con.wait(lk, [this]() 
            // {
            //     return count == 1;
            // });
            // printf("Foo");
            // count --;
            // con.notify_one();
        }
    }

    void bar() 
    {
        
        for (int i = 0; i < n; i++) {
            
        	// 解法1. 直接用锁来做，但是这样有违only the owner can unlock the mutex规则，容易产生死锁 
        	// printBar() outputs "bar". Do not change or remove this line.
            m_bar.lock();
        	printf("bar");
            m_foo.unlock();

            // 解法2. 用条件变量+锁的方式试一下
            // std::unique_lock<std::mutex> lk(Mu);
            // con.wait(lk, [this]()
            // {
            //     return count==0;
            // });
            // printf("bar");
            // count++;
            // con.notify_one();
        }
    }

private:
    int sem1 = 1;
    int sem2 = 0;
    std::mutex m_bar, m_foo;
};

// =================================================================================================================================
// 1116、每个线程都有一个 printNumber 方法来输出一个整数。修改给出的代码以输出整数序列 010203040506... ，其中序列的长度必须为 2n。
class ZeroEvenOdd 
{
private:
    int n;
    int count = 1;
    mutex Mu;
    condition_variable con;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        if (n % 2 != 0)
        {
            std::cerr<<"U need to input even"<<std::endl;
        }
        thread output0(&ZeroEvenOdd::zero, this);
        output0.join();
        thread output_even(& ZeroEvenOdd::even, this);
        output_even.join();
        thread output_odd(& ZeroEvenOdd::odd, this);
        output_odd.join();

    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero() 
    {
        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> lk(Mu);
            this->con.wait(lk, [this]()
            {
                return count == 1;
            });
            cout << 0;
            if (i % 2 == 0)//如果i是偶数，则该打印奇数了
                count == 3;
            else
                count == 2;
            con.notify_one();
        }
    }

    void even() 
    {
        for (int i = 0; i < n/2; i++)
        {
            unique_lock<mutex> lk(Mu);
            this->con.wait(lk, [this]()
            {
                return count == 3;
            });
            cout << i*2;
            count = 1;
            con.notify_one();
        }
    }

    void odd() 
    {
        for (int i = 0; i < n/2; i++)
        {
            unique_lock<mutex> lk(Mu);
            this->con.wait(lk, [this]()
            {
                return count == 2;
            });
            cout << 2 * i + 1;
            count = 1;
            con.notify_one();
        }
    }
};

// =================================================================================================================================
// 1117、你必须保证产生一个水分子所需线程的结合必须发生在下一个水分子产生之前。
//       有bug，我以为是要输入一个东西，没想到直接来两个线程，输出2个H之后输出O，然后一直循环就好了
class H2O 
{
private:
    int count_H = 100;
    int count_O = 100;
    condition_variable con;
    mutex Mu;
    string input_str;
    char mark = ' ';
    int index = 0;

public:
    H2O(string input) : input_str(input)
    { 
        
    };

    void start()
    {
        std::thread thread_H(&H2O::hydrogen, this);
        std::thread thread_O(&H2O::oxygen, this);
        std::thread thread_traffic(&H2O::traffic, this);

        thread_H.join();
        thread_O.join();
        thread_traffic.join();
    }
    void traffic()
    {        
        count_H = 0;
        count_O = 0;
        for (auto str : input_str)
        {
            if (str == 'H')
            {
                count_H ++; 
                con.notify_all();
                std::this_thread::sleep_for(chrono::seconds(1));
            }
            else
            {
                count_O ++ ;
                con.notify_all();
                std::this_thread::sleep_for(chrono::seconds(1));
            }
        }
        
    }

    void hydrogen()//function<void()> releaseHydrogen 
    {
        unique_lock<mutex> lk(Mu);
        con.wait(lk, [this]()
        {
            return (count_H < 2);
        });
        // releaseHydrogen();
        cout<<"H";
        // count_H ++;
        if (count_O >= 1 && count_H >= 2)
        {
            count_O = 0;
            count_H = 0;
        }   
        // con.notify_all();       
    }

    void oxygen()//function<void()> rel
    {
        unique_lock<mutex> lk(Mu);
        con.wait(lk, [this]()
        {
            return (count_O < 1);
        });
        // releaseOxygen();
        cout<<"O";
        // count_O ++;
        if (count_O >= 1 && count_H >= 2)
        {
            count_O = 0;
            count_H = 0;
        }
        // con.notify_all();    
    }

    
};

// =================================================================================================================================
// 1195、3->fizz; 5->buzz; 3&5->fizzbuzz; 35都不行->i
//       例如：当 n = 15，输出： 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz
class FizzBuzz {
private:
    int n;
    int idx = 2;
    mutex Mu;
    condition_variable con;
    int mark = 1;

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    void start()
    {
        thread thread_count(&FizzBuzz::count, this);
        thread thread_3(&FizzBuzz::fizz, this);
        thread thread_5(&FizzBuzz::buzz, this);
        thread thread_35(&FizzBuzz::fizzbuzz, this);
        thread thread_(&FizzBuzz::number, this);

        thread_count.join();
        thread_35.join();
        thread_3.join();
        thread_5.join();
        thread_.join();
    }

    // 还得专门写一个运行这些线程的函数
    void count()
    {
        for (int i = 1; i <= n; i++)
        {
            idx = i;
            mark = 1;
            cout<<endl<<idx<<": ";
            con.notify_all();
            this_thread::sleep_for(chrono::seconds(1));
        }
        
    }

    // printFizz() outputs "fizz".
    void fizz() 
    {
        while (idx < n)
        {
            unique_lock<mutex> lk(Mu);
            con.wait(lk, [this]()
            {   
                return (idx % 3 == 0) && (idx % 5 != 0) && (mark==1) || idx>=n;
                // return idx==4;
            });
            mark = 0;
            // idx ++ ;
            if ((idx % 3 == 0) && (idx % 5 != 0)) cout<<"fizz, ";
            // con.notify_all();
        }        
    }

    // printBuzz() outputs "buzz".
    void buzz() 
    {
        while (idx < n)
        {
            unique_lock<mutex> lk(Mu);
            con.wait(lk, [this]()
            {
                return (idx % 3 != 0) && (idx % 5 == 0) && (mark==1) || idx>=n;
                // return idx==3;
            });
            mark = 0;
            // idx ++ ;
            if ((idx % 3 != 0) && (idx % 5 == 0)) cout<<"buzz, ";
            // con.notify_all();
        }              
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz() 
    {
        while (idx < n)
        {
            unique_lock<mutex> lk(Mu);
            con.wait(lk, [this]()
            {
                return (idx % 3 == 0) && (idx % 5 == 0) && (mark==1) || idx>=n;
                // return idx == 2;
            });
            mark = 0;
            // idx ++ ;
            if ((idx % 3 == 0) && (idx % 5 == 0)) cout<<"fizzbuzz, ";
            // con.notify_all();
        }         
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number() //function<void(int)> printNumber
    {
        while (idx < n)
        {
            unique_lock<mutex> lk(Mu);
            con.wait(lk, [this]()
            {
                return (idx % 3 != 0) && (idx % 5 != 0) && (mark==1) || idx>=n;
                // return idx == 1;
            });
            mark = 0;
            if ((idx % 3 != 0) && (idx % 5 != 0)) cout<<idx<<", ";
            // idx ++ ;
            // con.notify_all();
        } 
        
    }
};

// 别人成功的版本的改进之处：
// 1.在con的return条件中加入 || (num>n)，使其在满足条件之后可以继续运行，并跳出for循环，完成该线程；
// 2.把con等待和线程任务交换，（先完成任务再con等待，只要满足要求就去完成任务，然后接着循环）
//   这样就可以实现自己线程激活自己的，如果是先con的话，只能激活别的等待，不能激活自己的，导致程序卡住；
// 3.还是没学会人家是怎么调用指针函数的。。。
class FizzBuzz_others {
private:
    int n;
    int num;
    condition_variable cv;
    mutex m;
public:
    FizzBuzz_others(int n) {
        this->n = n;
        num = 1;
    }

    // function<void()> fizz_output = []() {
    //     cout << "fizz" << endl;
    // };

    // function<void()> buzz_output = []() {
    //     cout << "buzz" << endl;
    // };

    // function<void()> fizzbuzz_output = []() {
    //     cout << "fizzbuzz" << endl;
    // };

    // function<void(int)> num_output = [](int n) {
    //     cout << n << endl;
    // };

    void start()
    {
        thread th1(&FizzBuzz_others::fizz, this);
        thread th2(&FizzBuzz_others::buzz, this);
        thread th3(&FizzBuzz_others::fizzbuzz, this);
        thread th4(&FizzBuzz_others::number, this);

        th1.join();
        th2.join();
        th3.join();
        th4.join();
    }


    // printFizz() outputs "fizz".function<void()> printFizz
    void fizz() {
        unique_lock<mutex> lk(m);
        for ( ; num <= n ; )
        {
            if (num % 3 == 0 && num % 5 != 0)
            {
                // printFizz();
                cout<<"fizz, ";
                ++num;
                cv.notify_all();
            }
            cv.wait(lk, [this] {return (num > n) || num % 3 == 0 && num % 5 != 0; });
        }
    }

    // printBuzz() outputs "buzz".function<void()> printBuzz
    void buzz() {
        unique_lock<mutex> lk(m);
        for (; num <= n;)
        {
            if (num % 5 == 0 && num % 3 != 0)
            {
                // printBuzz();
                cout<<"Buzz, ";
                ++num;
                cv.notify_all();
            }
            cv.wait(lk, [this] {return (num > n) || num % 5 == 0 && num % 3 != 0; });
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".function<void()> printFizzBuzz
    void fizzbuzz() {
        unique_lock<mutex> lk(m);
        for (; num <= n;)
        {
            if (num % 3 == 0 && num % 5 == 0)
            {
                // printFizzBuzz();
                cout<<"FizzBuzz, ";
                ++num;
                cv.notify_all();
            }
            cv.wait(lk, [this] {return (num > n) || num % 3 == 0 && num % 5 == 0; });
        }
    }

    // printNumber(x) outputs "x", where x is an integer.function<void(int)> printNumber
    void number() {
        unique_lock<mutex> lk(m);
        for (; num <= n;)
        {
            if (num % 3 != 0 && num % 5 != 0)
            {
                // printNumber(num);
                cout<<num<<", ";
                ++num;
                if (num > n)
                {
                    cv.notify_all();
                    break;
                }
                if (num % 3 != 0 && num % 5 != 0)
                {
                    continue;
                }
                else
                {
                    cv.notify_all();
                }
            }
            cv.wait(lk, [this] {return (num > n) || num % 3 != 0 && num % 5 != 0; });
        }
    }
};


// ---------------------------------
//      用信号量实现
//----------------------------------

// =================================================================================================================================
// 1115、两个不同的线程将会共用一个 FooBar 实例。其中一个线程将会调用 foo() 方法，另一个线程将会调用 bar() 方法。
//       请设计修改程序，以确保 "foobar" 被输出 n 次。
class FooBar_Semaphore {   
private:
    int n;
    szm::semaphore sem_foo, sem_bar;


public:
    FooBar_Semaphore(int n) 
    {    
        this->n = n;
        sem_foo.init(1);
        sem_bar.init(1);
        sem_bar.wait();

    }

    void start()
    {
        thread thread_foo(&FooBar_Semaphore::foo, this);
        thread thread_bar(&FooBar_Semaphore::bar, this);

        thread_bar.join();
        thread_foo.join();
    }

    void foo() {
        
        for (int i = 0; i < n; i++) {
            sem_foo.wait();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	cout<<"Foo";
            sem_bar.signal();
        }
    }

    void bar() {
        
        for (int i = 0; i < n; i++) {
            sem_bar.wait();
        	// printBar() outputs "bar". Do not change or remove this line.
        	cout<<"Bar, "<<endl;
            sem_foo.signal();
        }
    }
};

// =================================================================================================================================
// 1116、每个线程都有一个 printNumber 方法来输出一个整数。修改给出的代码以输出整数序列 010203040506... ，其中序列的长度必须为 2n。
class ZeroEvenOdd_semaphore {
private:
    int n;
    int count = 1;
    szm::semaphore sem_zero, sem_even, sem_odd;

public:
    ZeroEvenOdd_semaphore(int n) 
    {
        this->n = n;
        if (n % 2 != 0)
        {
            std::cerr<<"U need to input even"<<std::endl;
            return ;
        }
        sem_zero.init(0);
        sem_even.init(0);
        sem_odd.init(0);
        sem_zero.signal();
    }

    void start()
    {
        thread output0(&ZeroEvenOdd_semaphore::zero, this);
        thread output_even(& ZeroEvenOdd_semaphore::even, this);
        thread output_odd(& ZeroEvenOdd_semaphore::odd, this);
        output0.join();
        output_even.join();
        output_odd.join();
    }

    void zero() 
    {
        for (int i = 0; i < n; i++)
        {
            sem_zero.wait();
            cout << 0;
            if (i % 2 == 0)//如果i是偶数，则该打印奇数了
                sem_even.signal();
            else
                sem_odd.signal();
        }
    }

    void even() 
    {
        for (int i = 0; i < n/2; i++)
        {
            sem_even.wait();
            cout << i*2+1;
            sem_zero.signal();
        }
    }

    void odd() 
    {
        for (int i = 0; i < n/2; i++)
        {
            sem_odd.wait();
            cout << 2 * i + 2;
            sem_zero.signal();
        }
    }
};

// =================================================================================================================================
// 1117、你必须保证产生一个水分子所需线程的结合必须发生在下一个水分子产生之前。
//       有bug，我以为是要输入一个东西，没想到直接来两个线程，输出2个H之后输出O，然后一直循环就好了
class H2O_semahpore
{
private:
    int count_H = 100;
    int count_O = 100;
    condition_variable con;
    mutex Mu;
    string input_str;
    char mark = ' ';
    int index = 0;

public:
    H2O_semahpore(string input) : input_str(input)
    { 
        
    };

    void start()
    {
        std::thread thread_H(&H2O_semahpore::hydrogen, this);
        std::thread thread_O(&H2O_semahpore::oxygen, this);
        std::thread thread_traffic(&H2O_semahpore::traffic, this);

        thread_H.join();
        thread_O.join();
        thread_traffic.join();
    }
    void traffic()
    {        
        count_H = 0;
        count_O = 0;
        for (auto str : input_str)
        {
            if (str == 'H')
            {
                count_H ++; 
                con.notify_all();
                std::this_thread::sleep_for(chrono::seconds(1));
            }
            else
            {
                count_O ++ ;
                con.notify_all();
                std::this_thread::sleep_for(chrono::seconds(1));
            }
        }
        
    }

    void hydrogen()//function<void()> releaseHydrogen 
    {
        unique_lock<mutex> lk(Mu);
        con.wait(lk, [this]()
        {
            return (count_H < 2);
        });
        // releaseHydrogen();
        cout<<"H";
        // count_H ++;
        if (count_O >= 1 && count_H >= 2)
        {
            count_O = 0;
            count_H = 0;
        }   
        // con.notify_all();       
    }

    void oxygen()//function<void()> rel
    {
        unique_lock<mutex> lk(Mu);
        con.wait(lk, [this]()
        {
            return (count_O < 1);
        });
        // releaseOxygen();
        cout<<"O";
        // count_O ++;
        if (count_O >= 1 && count_H >= 2)
        {
            count_O = 0;
            count_H = 0;
        }
        // con.notify_all();    
    }

    
};

// ====================================================================================================================s=============
// 1195、3->fizz; 5->buzz; 3&5->fizzbuzz; 35都不行->i
//       例如：当 n = 15，输出： 1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz
//       这个题的考察点：如何激活自己的线程，如何自动停止
class FizzBuzz_semahpore {
private:
    int n;
    int idx = 2;
    szm::semaphore sem_fizz, sem_buzz, sem_fizzbuzz, sem_num;
    int mark = 1;

public:
    FizzBuzz_semahpore(int n) 
    {
        this->n = n;
        sem_buzz.init(0);
        sem_fizz.init(0);
        sem_fizzbuzz.init(0);
        sem_num.init(0);
    }

    void start()
    {
        thread thread_count(&FizzBuzz_semahpore::count, this);
        thread thread_3(&FizzBuzz_semahpore::fizz, this);
        thread thread_5(&FizzBuzz_semahpore::buzz, this);
        thread thread_35(&FizzBuzz_semahpore::fizzbuzz, this);
        thread thread_(&FizzBuzz_semahpore::number, this);

        thread_count.join();
        thread_35.join();
        thread_3.join();
        thread_5.join();
        thread_.join();
    }

    // 还得专门写一个运行这些线程的函数
    void count()
    {
        for (int i = 1; i <= n; i++)
        {
            switch ((i%3==0)<<1 | (i%5==0))
            {
            case 0:
                sem_num.signal();
                break;
            case 1:
                sem_buzz.signal();
                break;
            case 2:
                sem_fizz.signal();
                break;
            case 3:
                sem_fizzbuzz.signal();
                break;
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
        
    }

    // printFizz() outputs "fizz".
    void fizz() 
    {
        for (int i=1; i<=n; i++)
        {
            if ((i % 3 == 0) && (i % 5 != 0) ) 
            {
                sem_fizz.wait();
                cout<<"fizz, ";
            }
        }        
    }

    // printBuzz() outputs "buzz".
    void buzz() 
    {
        for (int i=1; i<=n; i++)
        {
            if ((i % 3 != 0) && (i % 5 == 0)) 
            {
                sem_buzz.wait();
                cout<<"buzz, ";
            }
        }              
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz() 
    {
        for (int i=1; i<=n; i++)
        {
            if ((i % 3 == 0) && (i % 5 == 0)) 
            {
                sem_fizzbuzz.wait();
                cout<<"fizzbuzz, ";
            }
        }         
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number() //function<void(int)> printNumber
    {
        for (int i=1; i<=n; i++)
        {
            if ((i % 3 != 0) && (i % 5 != 0))
            {
                sem_num.wait();
                cout<<i <<", ";
            }
        } 
        
    }
};

int main()
{

    // test 1115 ---------------------------------------------
    // FooBar_Semaphore foobar(5);
    // foobar.start();
    // FooBar foobar(5);
    // foobar.start();

    // // 在main中调用类中的函数
    // std::thread t_foo(&FooBar::foo, &foobar);
    // std::thread t_bar(&FooBar::bar, &foobar);
    // t_foo.join();
    // t_bar.join();

    // test 1116 ---------------------------------------------
    // ZeroEvenOdd zero_even_odd(1);
    // ZeroEvenOdd_semaphore zero_even_odd(4);
    // zero_even_odd.start();


    // test 1117 ---------------------------------------------
    // H2O h2o("OHHHHO");
    // h2o.start();

    // test 1195 ---------------------------------------------
    // FizzBuzz fizzbuzz(15);
    // fizzbuzz.start();
    FizzBuzz_semahpore fizzbuzz(15);
    fizzbuzz.start();

    // FizzBuzz_others fizzbuzz_others(15);
    // fizzbuzz_others.start();

    
    return 0;
}

