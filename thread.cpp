#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::mutex mutex;

int a = 0;

void do_stuff(int index)
{
    std::cout << "cekam na mutex: " << index << std::endl;
    mutex.lock();
    std::cout << "mutex je muj: "  << index << std::endl;
    mutex.unlock();
    std::cout << "odemknut: " << index << std::endl;
}

void say_hello() 
{
    for(int i = 0; i < 10; i++)
    {
        a++;
    }
}

void say_something()
{
    for(int i = 0; i <= INT16_MAX; i++)
    {
        a = a + 1;
    }
}

int main() 
{
    std::thread t1(do_stuff, 1);
    std::thread t2(do_stuff, 2);
    t1.join();
    t2.join();

    return 0;
}