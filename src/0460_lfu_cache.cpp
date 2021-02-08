/*************************************************************************************************
 *
 * 146. LFU Cache
 * Design a data structure that follows the constraints of a Least Frequently Used cache. (Resolve
 * ties by removing the least recently used candidate.)
 *
 * A set sorted by frequency and last access, and a map whose values contain pointers (iterators)
 * to nodes in the set. On access, keys can be moved in the set in O(log n).
 *
 ************************************************************************************************/

#include <ctime>
#include <exception>
#include <iostream>
#include <map>
#include <set>

using namespace std;

class LFUCache {
    friend ostream& operator<<(ostream& , const LFUCache&);

public:
    LFUCache(int capacity_) : capacity(capacity_) {}

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second.value = value;
            it->second.node = touch_frequency_node(it->second.node);
        } else {
            if (cache.size() == capacity) drop_lfu();
            auto p = history.insert({ key, 1, clock() }); // p.first = iterator to inserted element
            cache[key] = { value, p.first };
        }

        cout << "put(" << key << "," << value << ") => " << *this << endl;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            it->second.node = touch_frequency_node(it->second.node);
            cout << "get(" << key << ") -> " << it->second.value << " => " << *this << endl;
            return it->second.value;
        } else {
            cout << "get(" << key << ") -> -1 => " << *this << endl;
            return -1;
        }
    }

private:
    size_t capacity;

    struct FrequencyNode {
        int key;
        int frequency;
        clock_t last_access;
        bool operator<(const FrequencyNode other) const {
            return this->frequency < other.frequency
                || (this->frequency == other.frequency && this->last_access < other.last_access);
        }
        void touch() { ++frequency; last_access = clock(); }
    };
    set<FrequencyNode> history;

    struct Value {
        int value;
        set<FrequencyNode>::iterator node;
    };
    map<int, Value> cache;

    set<FrequencyNode>::iterator touch_frequency_node(const set<FrequencyNode>::iterator it)
    {
        FrequencyNode n = *it;
        n.touch();
        history.erase(it);
        auto p = history.insert(n);
        return p.first;
    }

    void drop_lfu(void) {
        cache.erase(history.begin()->key);
        history.erase(history.begin());
    }
};


ostream& operator<<(ostream &os, const LFUCache &cache)
{
    os << "capacity=" << cache.capacity << ", cache: ";
    for (const auto &p : cache.cache) {
        os << '(' << p.first << ':' << p.second.value << ')';
    }
    os << ", frequency: ";
    for (const LFUCache::FrequencyNode &n : cache.history) {
        os << '<' << n.key << "," << n.frequency << "," << n.last_access << "> ";
    }
    return os;
}

int main(void)
{
    LFUCache *cache = new LFUCache(0);
    cache->put(0,0);
    cache->get(0);

    /* LFUCache *cache = new LFUCache(2);
     * cache->put(1,1);
     * cache->put(2,2);
     * cache->get(1);
     * cache->put(3,3);
     * cache->get(2);
     * cache->get(3);
     * cache->put(4,4);
     * cache->get(1);
     * cache->get(3);
     * cache->get(4); */

    delete cache;
    return 0;
}

/* This input generates heap-used-after-free error:
 *
 * ["LFUCache","put","put","put","put","put","get","put","get","get","put","get","put","put","put","get","put","get","get","get","get","put","put","get","get","get","put","put","get","put","get","put","get","get","get","put","put","put","get","put","get","get","put","put","get","put","put","put","put","get","put","put","get","put","put","get","put","put","put","put","put","get","put","put","get","put","get","get","get","put","get","get","put","put","put","put","get","put","put","put","put","get","get","get","put","put","put","get","put","put","put","get","put","put","put","get","get","get","put","put","put","put","get","put","put","put","put","put","put","put"]
[[10],[10,13],[3,17],[6,11],[10,5],[9,10],[13],[2,19],[2],[3],[5,25],[8],[9,22],[5,5],[1,30],[11],[9,12],[7],[5],[8],[9],[4,30],[9,3],[9],[10],[10],[6,14],[3,1],[3],[10,11],[8],[2,14],[1],[5],[4],[11,4],[12,24],[5,18],[13],[7,23],[8],[12],[3,27],[2,12],[5],[2,9],[13,4],[8,18],[1,7],[6],[9,29],[8,21],[5],[6,30],[1,12],[10],[4,15],[7,22],[11,26],[8,17],[9,29],[5],[3,4],[11,30],[12],[4,29],[3],[9],[6],[3,4],[1],[10],[3,29],[10,28],[1,20],[11,13],[3],[3,12],[3,8],[10,9],[3,26],[8],[7],[5],[13,17],[2,27],[11,15],[12],[9,19],[2,15],[3,16],[1],[12,17],[9,1],[6,19],[4],[5],[5],[8,1],[11,7],[5,2],[9,28],[1],[2,2],[7,4],[4,22],[7,24],[9,26],[13,28],[11,26]]

 */
