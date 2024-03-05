struct Hashing{
    string s;
    ll p = 30;
    ll m = 1e9 + 7;
    int n;
    vector<ll> prefixHash;
    vector<ll> powersOfP;
    vector<ll> inversePowersOfP;
    Hashing(string queryString){
        s = queryString;
        n = s.size();
        prefixHash.resize(n);
        powersOfP.resize(n);
        inversePowersOfP.resize(n);
        calculatePowersAndInversePowersOfP();
        calculatePrefixHashes();
    }
    void calculatePowersAndInversePowersOfP(){ // O(n)
        ll currentPower = 1;
        for(int i = 0; i < n; i++){
            powersOfP[i] = currentPower;
            currentPower = (currentPower * p) % m;
        }
        inversePowersOfP[n - 1] = mminvprime(powersOfP[n - 1], m);
        for(int i = n - 2; i >= 0; i--){
            inversePowersOfP[i] = (inversePowersOfP[i + 1] * p) % m;
        }
    }
    void calculatePrefixHashes(){
        ll hashSoFar = 0;
        for(int i = 0; i < n; i++){
            hashSoFar = (hashSoFar + (s[i] - 'a' + 1) * powersOfP[i]) % m;
            prefixHash[i] = hashSoFar;
        }
    }
    
    
    ll substringHash(int l, int r){  // O(1)
        ll val1 = prefixHash[r];
        ll val2 = l > 0 ? prefixHash[l - 1] : 0LL;
        return ((val1 - val2 + m) * inversePowersOfP[l]) % m;
    }
};
