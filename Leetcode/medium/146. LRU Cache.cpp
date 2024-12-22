
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 







/*********************my solution***********************/






class LRUCache {
    unordered_map<int, list<pair<int, int>>::iterator> data;
    list<pair<int, int>> lt;

public:
    LRUCache(int capacity) {
        data.reserve(capacity);
        lt.resize(capacity);
    }

    int get(int key) {

        auto it = data.find(key);
        if (it != data.end())
        {
            lt.splice(lt.begin(), lt, it->second);
            return it->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto it = data.find(key);
        if (it != data.end())
        {
            lt.splice(lt.begin(), lt, it->second);
            it->second->second = value;
        }
        else
        {
            data.erase(lt.rbegin()->first);
            lt.rbegin()->first = key;
            lt.rbegin()->second = value;
            data[key] = std::prev(std::end(lt));
            lt.splice(lt.begin(), lt, std::prev(std::end(lt)));
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */





/**********************TOP solution***********************/





#define NO_SAN __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))
#define INL __attribute__((always_inline))
#define HOT __attribute__((hot))
#define INL_ATTR noexcept INL NO_SAN HOT
#define OUTL_ATTR noexcept NO_SAN HOT
#define LAM_ATTR INL NO_SAN HOT noexcept

#pragma GCC diagnostic ignored "-Wshift-op-parentheses"

constexpr uint MAX_STORAGE_QW = 7u << 21;
uint64_t storage[MAX_STORAGE_QW];
uint storage_used = 0;

void* operator new(std::size_t sz) {
    if (sz == 0)
        ++sz;
 
    const uint used = storage_used;
    storage_used += sz + 15u >> 4 << 1;
    // assert(storage_used < MAX_STORAGE_QW);
    return storage + used;
}
 
void* operator new[](std::size_t sz) {
    if (sz == 0)
        ++sz;
 
    const uint used = storage_used;
    storage_used += sz + 15u >> 4 << 1;
    // assert(storage_used < MAX_STORAGE_QW);
    return storage + used;
}
 
void operator delete(void* ptr) noexcept {
}
 
void operator delete(void* ptr, std::size_t size) noexcept {
}
 
void operator delete[](void* ptr) noexcept {
}
 
void operator delete[](void* ptr, std::size_t size) noexcept {
}

class LRUCache {
private:
    typedef uint16_t ref_t;
    static constexpr ref_t MAXCAP = 3000, NONE = USHRT_MAX, MAXV = 10'000;
    static constexpr uint8_t KSH = 17;
    static constexpr uint VMASK = (1u << KSH) - 1u;

    struct entry_t {
        uint kv;
        ref_t prev, next;
    };

    static entry_t storage[MAXCAP];
    static ref_t index[MAXV+1u], used, cap, head;

    static void insbefore(const ref_t i, const ref_t next) INL_ATTR {
        if (next == NONE) {
            storage[i].next = storage[i].prev = i;
        } else if (storage[next].next == next) {
            storage[i].next = storage[i].prev = next;
            storage[next].next = storage[next].prev = i;
        } else {
            const ref_t prev = storage[next].prev;
            storage[i].prev = prev;
            storage[next].prev = i;
            storage[i].next = next;
            storage[prev].next = i;
        }
    }

    static void makehead(const ref_t i) INL_ATTR {
        if (head != NONE) {
            const ref_t prev = storage[i].prev, next = storage[i].next;
            storage[next].prev = prev;
            storage[prev].next = next;
            insbefore(i, head);
        }
        head = i;
    }

public:
    LRUCache(const uint c) INL_ATTR {
        cap = c;
        fill(index, index + MAXV, NONE);
    }
    
    static int get(const uint key) OUTL_ATTR {
        // cout << "Get " << key << ':';
        const ref_t i = index[key];
        // if (i == NONE) cout << "NONE" << endl;
        if (i == NONE) return -1;
        if (head != i) makehead(i);
        // cout << (storage[i].kv & VMASK) << endl;
        return storage[i].kv & VMASK;
    }
    
    static void put(const uint key, const uint value) OUTL_ATTR {
        // cout << "Put " << key << ':' << value << endl;
        ref_t i;
        if (i = index[key]; i == NONE) {
            if (used < cap) {
                i = used++;
                // cout << "Allocated " << i << endl;
                insbefore(i, head);
                head = i;
            } else {
                head = i = storage[head].prev;
                index[storage[i].kv >> KSH] = NONE;
            }
        } else if (head != i)
            makehead(i);
        storage[i].kv = (key << KSH) + value;
        index[key] = i;
        // cout << "Now:";
        // ref_t j = head;
        // do {
        //     cout << ' ' << (storage[j].kv >> KSH) << ':' << (storage[j].kv & VMASK);
        //     j = storage[j].next;
        // } while (j != head);
        // cout << endl;
    }

    ~LRUCache() INL_ATTR {
        head = NONE;
        used = 0;
    }
};

LRUCache::entry_t LRUCache::storage[MAXCAP];
LRUCache::ref_t LRUCache::index[MAXV+1u], LRUCache::used, LRUCache::cap, LRUCache::head = NONE;

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();