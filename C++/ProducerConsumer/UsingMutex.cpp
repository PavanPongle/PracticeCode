#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer() {
   for (int i = 1; i <= 5; ++i) {
      std::lock_guard<std::mutex> lock(mtx);
      buffer.push(i);
      std::cout << "Produced: " << i << std::endl;
      cv.notify_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
   }
}

void consumer() {
   while (true) {
      std::unique_lock<std::mutex> lock(mtx);
      cv.wait(lock, [] { return !buffer.empty(); });
      int data = buffer.front();
      buffer.pop();
      std::cout << "Consumed: " << data << std::endl;
      lock.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }
}

int main() {
   std::thread producerThread(producer);
   std::thread consumerThread(consumer);
    
   producerThread.join();
   consumerThread.join();

   return 0;
}


/*********************************************************************************************/

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
atomic<bool> g_turn{0};

void fun(int id, char c)
{
    //cout << "inside fun" << endl;
    int k = 10;
    while(k--)
    {
        if(g_turn.load() == id)
        {
            //cout << "found turn" << endl;
            std::cout << c << endl;
            g_turn.store(!g_turn.load());
            cv.notify_all();
        }
        
        {
            //cout << "sleeping"<< endl;
            mutex mtx;
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [&]() { return id == g_turn.load(); || k <= 0});
            //cout << "after sleeping"<< endl;
        }
    }
   
}

int main()
{
    thread t1(fun, 0, '#');
    thread t2(fun, 1, '*');
    
    t1.join();
    t2.join();

    return 0;
}