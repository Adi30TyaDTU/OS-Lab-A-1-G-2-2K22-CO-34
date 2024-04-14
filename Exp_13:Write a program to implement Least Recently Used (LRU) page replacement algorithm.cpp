
// The Least Recently Used (LRU) Page Replacement Algorithm is a commonly used algorithm in virtual memory management. It replaces the least recently used page when a new page needs to be brought into memory. 
// The algorithm replaces the page that has not been accessed for the longest period of time. It uses a data structure like a queue or a doubly linked list to keep track of the order in which pages are accessed. 
// When a page is accessed, it is moved to the front of the queue or the head of the linked list. 
// When a page needs to be replaced, the page at the end of the queue or the tail of the linked list (which is the least recently used page) is replaced


#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        auto it = _cache.find(key);
        if (it == _cache.end()) return -1;

        // Move accessed page to the front of the list
        _lru.splice(_lru.begin(), _lru, it->second);

        return it->second->second;
    }

    void put(int key, int value) {
        auto it = _cache.find(key);
        if (it != _cache.end()) {
            // Update the value and move the page to the front of the list
            it->second->second = value;
            _lru.splice(_lru.begin(), _lru, it->second);
            return;
        }

        if (_cache.size() >= _capacity) {
            // Remove the least recently used page from the cache
            int lruKey = _lru.back().first;
            _cache.erase(lruKey);
            _lru.pop_back();
        }

        // Add the new page to the cache and the front of the list
        _lru.emplace_front(key, value);
        _cache[key] = _lru.begin();
    }

private:
    int _capacity;
    list<pair<int, int>> _lru; // List to keep track of the access order
    unordered_map<int, list<pair<int, int>>::iterator> _cache; // Map to quickly look up a page
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // Returns 1
    cache.put(3, 3); // Evicts key 2
    cout << cache.get(2) << endl; // Returns -1 (not found)
    cache.put(4, 4); // Evicts key 1
    cout << cache.get(1) << endl; // Returns -1 (not found)
    cout << cache.get(3) << endl; // Returns 3
    cout << cache.get(4) << endl; // Returns 4

    return 0;
}
