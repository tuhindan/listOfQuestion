// https://www.geeksforgeeks.org/operating-systems/producer-consumer-problem-using-semaphores-set-1/

#include <iostream>
#include <mutex>
#include <thread>
#include <semaphore>
#include <deque>

using namespace std;

#define BUFFER 4
mutex mtx;
counting_semaphore<BUFFER> empty_count(BUFFER);
counting_semaphore<BUFFER> data_count(0);

deque<int> queue;
int count = 0 ;

void consumer()
{
    while(true) {
        // cout<<"waiting for data acquire"<<endl;
        data_count.acquire();
        mtx.lock();
        
        int data = queue.front();
        queue.pop_front();
        
        mtx.unlock();
        empty_count.release();
        
        cout<<"Data processing for "<<data<<endl;
        this_thread::sleep_for(1s);
    }

}

void producer()
{
    // cout<<"waiting for empty acquire"<<endl;
    empty_count.acquire();
    mtx.lock();
    
    count++;
    cout<<"Data pushed for "<<count<<endl;
    queue.push_back(count);
    
    mtx.unlock();
    data_count.release();
    
}

void customer_driver() {
    for(int i = 1 ; i <=15 ; i++)
        producer();
    
    this_thread::sleep_for(1s);
    
    for(int i = 1 ; i <=5 ; i++)
        producer();
}
    

// drive code
int main()
{
    thread producer_thread(consumer);
    thread consumer_thread(customer_driver);

    consumer_thread.join();
    producer_thread.join();

    return 0;
}
