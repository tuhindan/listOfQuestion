#include <iostream>
#include <mutex>
#include <list>
#include <unordered_map>

using namespace std;

class LRU {
    private:
        const static int capacity =4;
        unordered_map<int, pair<string, list<int>::iterator>> cache;
        list<int> dll;
    
    public:
        string fetch(int key) {
            auto it = cache.find(key);
            if(it != cache.end()) {
                list<int>::iterator dll_it = it->second.second;
                dll.erase(dll_it);
                dll.push_front(key);
                cache[key] = make_pair(it->second.first, dll.begin());
                return it->second.first;
            } else 
                return "";
        }
        
        void insert(int key, string value) {
            auto it = cache.find(key);
            if(it != cache.end()) {
                cout<<"key exists : updating"<<endl;

                list<int>::iterator dll_it = it->second.second;
                dll.erase(dll_it);
                
            } else {
                if(cache.size() == capacity) {
                    int del_key = dll.back();
                    dll.pop_back();
                    cache.erase(del_key);
                    
                }
            }
            dll.push_front(key);
            cache[key] = make_pair(value, dll.begin());
        }
        
};

// drive code
int main()
{
    LRU c = LRU();
    c.insert(1, "tuhin");
    c.insert(2, "sanju");
    c.insert(3, "adrija");
    c.insert(4, "rimi");
    cout<<c.fetch(1)<<endl;
    c.insert(5, "goku");
    cout<<c.fetch(2)<<endl; // deleted from cache


    return 0;
}
