/*************************************************************************************************
 *
 * 146. LRU Cache
 * Design a data structure that follows the constraints of a Least Recently Used cache.
 *
 * A linked list of recently used keys and a hashtable that contains pointers (iterators) to list
 * nodes.  On access, keys can be moved in the list in O(1), and the hashtable gives amortized
 * O(1) as well.
 *
 * Faster than 99.49% (!) and less memory than 88.87% of C++ submissions.
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
    friend ostream& operator<<(ostream& , const LRUCache&);
public:
    LRUCache(int capacity_);
    int get(int key);
    void put(int key, int value);
private:
    size_t capacity;
    struct Value {
        int value;
        list<int>::iterator node;
    };
    unordered_map<int, Value> cache;
    list<int> history;
};

LRUCache::LRUCache(int capacity_)
{
    if (capacity_ < 1) throw invalid_argument("capacity must be positive");
    capacity = capacity_;
}

void LRUCache::put(int key, int value)
{
    auto it = cache.find(key);
    if (it != cache.end()) {
        it->second.value = value;
        history.splice(history.begin(), history, it->second.node);
    } else {
        history.push_front(key);
        cache[key] = { value, history.begin() };
    }

    if (cache.size() > capacity) {
        cache.erase(history.back());
        history.pop_back();
    }
}

int LRUCache::get(int key)
{
    auto it = cache.find(key);
    if (it != cache.end()) {
        history.splice(history.begin(), history, it->second.node);
        return it->second.value;
    } else {
        return -1;
    }

}

ostream& operator<<(ostream &os, const LRUCache &cache)
{
    os << "capacity=" << cache.capacity << ", cache: ";
    for (const auto &p : cache.cache) {
        os << '(' << p.first << ':' << p.second.value << ')';
    }
    os << ", recently used: ";
    for (const int &k : cache.history) os << k << ' ';
    return os;
}

int main(void)
{
    LRUCache *cache = new LRUCache(2);
    cache->put(1,1);
    cache->put(2,2);
    cout << "get(1) = " << cache->get(1) << ", expected 1" << endl;
    cache->put(3,3);
    cout << "get(2) = " << cache->get(2) << ", expected -1" << endl;
    cache->put(4,4);
    cout << "get(1) = " << cache->get(1) << ", expected -1" << endl;
    cout << "get(3) = " << cache->get(3) << ", expected 3" << endl;
    cout << "get(4) = " << cache->get(4) << ", expected 4" << endl;

    delete cache;
    return 0;
}
