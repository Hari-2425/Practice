#include <bits/stdc++.h>
#include <mutex>
#include <shared_mutex>
#include <iostream>

using namespace std;

class Employee{
    public:
    string name;
    string id;
    int salary;
    Employee(string name, string id, int sal){
        name = name;
        id = id;
        salary = sal;
    }
};

struct EmployeeComp{
    bool operator()(const Employee& a,
        const Employee& b) const{
        if(a.salary == b.salary){
            return (a.id < b.id);
        }
        return a.salary < b.salary;
    }
};

class LRUCache {
public:
    int cap;
    list<pair<int, int>> lruList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;
    

    LRUCache(int capacity) {
        cap = capacity;
    }

    void moveFront(int key, int val){
        lruList.erase(cacheMap[key]);
        lruList.push_front({key, val});
        cacheMap[key] = lruList.begin();
    }
    
    int get(int key) {
        if(cacheMap.find(key)==cacheMap.end()){
            return -1;
        }
        int res = cacheMap[key]->second;
        moveFront(key, res);
        return res;
    }
    
    void put(int key, int value) {
        if(cacheMap.find(key)==cacheMap.end()){
            if(lruList.size() >= cap){
                int delKey = lruList.end()->first;
                cacheMap.erase(delKey); // delete LRU key from Map
                lruList.erase(lruList.end()); // delete LRU key from Cache
            }
            lruList.push_front({key, value}); // push new key into Cache
            cacheMap[key] = lruList.begin(); // push new key into Map
        }
        else{
            // Remove the {key, value} from cache
            lruList.erase(cacheMap[key]);

            // Put it at the front
            lruList.push_front({key, value});

            // Update map to store updated address
            cacheMap[key] = lruList.begin();
        }
    }

    void put2(int key, int val){
        if(cacheMap.count(key)){
            moveFront(key, val);
        }
        else{
            if(lruList.size() >= cap){
                int delKey = lruList.back().first;
                cacheMap.erase(delKey);
                lruList.pop_back();
            }
            lruList.push_front({key, val});
            cacheMap[key] = lruList.begin();
        }

    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){
    shared_mutex mtx;
    shared_lock sl;
    return 0;
}