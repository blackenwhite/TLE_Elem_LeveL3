class CompositeKey{
    public:

    string k;
    int time;

    CompositeKey(){

    }

    CompositeKey(string& a, int b){
        k = a;
        time = b;
    }

    bool operator==(const CompositeKey& other) const{
        return k==other.k && time==other.time;
    }
};

struct CompositeKeyHash {
    size_t operator()(const CompositeKey& key) const {
        return hash<string>()(key.k) ^ (hash<int>()(key.time) << 1);
    }
};

class TimeMap {
public:
    unordered_map<CompositeKey,string, CompositeKeyHash> mp;

    TimeMap() {

    }
    
    void set(string key, string value, int timestamp) {
        CompositeKey a(key,timestamp);
        mp[a]=timestamp;
    }
    
    string get(string key, int timestamp) {
        CompositeKey a(key,timestamp);
        if(mp.count(a)) {
            return mp[a];
        }
        return "";
    }
};


#include <iostream>
#include <map>
#include <string>

using namespace std;

class CompositeKey {
public:
    string k;
    int time;

    // Default constructor
    CompositeKey() {}

    // Constructor with string and int
    CompositeKey(const string& a, int b) {
        k = a;
        time = b;
    }

    // Equality operator
    bool operator==(const CompositeKey& other) const {
        return k == other.k && time == other.time;
    }

    // Less than operator for map ordering
    bool operator<(const CompositeKey& other) const {
        // First compare strings, then compare times if strings are equal
        return k < other.k || (k == other.k && time < other.time);
    }
};

class TimeMap {
public:
    map<CompositeKey, string> mp;  // Use std::map (no custom hash function needed)

    TimeMap() {
        // No explicit initialization needed
    }

    void set(const string& key, const string& value, int timestamp) {
        CompositeKey a(key, timestamp);
        mp[a] = value;  // Store value for the given CompositeKey
    }

    string get(const string& key, int timestamp) {
        CompositeKey a(key, timestamp);
        if (mp.count(a)) {
            return mp[a];
        }
        return "";
    }
};

int main() {
    TimeMap timeMap;
    timeMap.set("foo", "bar", 1);
    cout << timeMap.get("foo", 1) << endl;  // Output should be "bar"
    return 0;
}


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
