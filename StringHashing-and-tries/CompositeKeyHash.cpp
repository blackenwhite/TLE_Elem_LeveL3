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

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
