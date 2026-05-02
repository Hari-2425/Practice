#include <bits/stdc++.h>

using namespace std;

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
        lruList.erase(cacheMap[key]);
        lruList.push_front({key, res});
        return res;
    }
    
    void put(int key, int value) {
        if(cacheMap.find(key)==cacheMap.end()){
            int delKey = lruList.end()->first;
            cacheMap.erase(delKey); // delete LRU key from Map
            lruList.erase(lruList.end()); // delete LRU key from Cache

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
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(){

    return 0;
}