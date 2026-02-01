//https://www.geeksforgeeks.org/operating-systems/readers-writers-problem-set-1-introduction-and-readers-preference-solution/
//https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>

using namespace std;

mutex reader_lock, writer_lock;
binary_semaphore writer_semaphore(1);
int count  = 0;
int reader_number = 0;
int writer_number = 0;

void reader() {
    int num = 0;
    writer_lock.lock();
    reader_lock.lock();

    if(count == 0)
        writer_semaphore.acquire();
    reader_number++;
    count++;
    num = reader_number;
    
    reader_lock.unlock();
    writer_lock.unlock();

    
    cout<<"reading "<<num<<endl;
    this_thread::sleep_for(1s);
    
    reader_lock.lock();
    count--;
    if(count == 0)
        writer_semaphore.release();
    reader_lock.unlock();
    
}

void writer() {
    writer_lock.lock();
    writer_semaphore.acquire();
    writer_number++;
    
    cout<<"writing "<<writer_number<<endl;
    this_thread::sleep_for(2s);

    writer_semaphore.release();
    writer_lock.unlock();
}

int main()
{
    for(int i = 0 ; i < 5 ; i++) {
        thread reader1(reader);
        reader1.detach();
    }

    for(int i = 0 ; i < 3 ; i++) {
        thread writer1(writer);
        writer1.detach();
    }
   
   
    for(int i = 0 ; i < 5 ; i++) {
        thread reader1(reader);
        reader1.detach();
    }

    // if main thread is finished, nothing from the other thread will be printed
    this_thread::sleep_for(30s);

    return 0;
}
