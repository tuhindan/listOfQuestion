// semphore is only vaialble in c++20 and above
// use https://www.onlinegdb.com/online_c++_compiler for testing
// https://www.geeksforgeeks.org/operating-systems/sleeping-barber-problem-in-process-synchronization/

#include <iostream>
#include <mutex>
#include <thread>
#include <semaphore>
#include <deque>

using namespace std;

#define SEAT 10
mutex mtx;
binary_semaphore wake(0);

deque<int> queue;
int count = 0 ;

void barberShop()
{
    while(true) {
        mtx.lock();
        if(!queue.empty()) {
            int cus = queue.front();
            queue.pop_front();
            mtx.unlock();
            cout<<"Barber cutting hair "<<cus<<endl;
            this_thread::sleep_for(1s);
            
            
        } else {
            cout<<"Barber is sleeping"<<endl;
            mtx.unlock();
            wake.acquire();
        }
    }

}

void customer()
{
    mtx.lock();
    count++;
    if(queue.empty()) {
        cout<<"Customer "<<count<<" waking Barber"<<endl;
        wake.release();
    }
    if(queue.size() == SEAT)
    {   
        cout<<"Customer "<<count<<" left, no seats available"<<endl;
        mtx.unlock();
        return;
    }
    cout<<"Customer "<<count<<" sat"<<endl; 
    queue.push_back(count);
    mtx.unlock();
}

void customer_driver() {
    for(int i = 1 ; i <=15 ; i++)
    customer();
    
    this_thread::sleep_for(1s);
    
    for(int i = 1 ; i <=5 ; i++)
    customer();
}
    

// drive code
int main()
{
    thread producer_thread(barberShop);
    thread consumer_thread(customer_driver);

    consumer_thread.join();
    producer_thread.join();

    return 0;
}
