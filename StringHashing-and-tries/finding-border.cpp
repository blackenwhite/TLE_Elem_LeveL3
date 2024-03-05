// CSES finding border
// author : Nabajyoti
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
#define pii pair<int, int>
#define N 100100
int inf = 1e18;
#define ff first 
#define ss second


struct less_than_key
{
    bool operator()(const pii &a, const pii &b)
    {
        return (a.first - a.second) > (b.first - b.second);
    }
};

int gcd(int a, int b)
{
    if (a < b)
        return gcd(b, a);
    if (b == 0)
        return a;
    return gcd(a % b, b);
}

int mult(int a, int b) // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

int exponent(int a, int b)
{
    int ans = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return ans;
}

int inverse(int a) { return exponent(a, mod - 2); }

int fact[N];
int invFact[N];

void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = mult(i, fact[i - 1]);
    }

    invFact[N - 1] = inverse(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        invFact[i] = mult(invFact[i + 1], i + 1);
    }
}

int nCr(int n, int r)
{
    return mult(fact[n], mult(invFact[n - r], invFact[r]));
}

int add(int a, int b)
{ // O(1)
    int ans = (a + b);
    if (ans >= mod)
        ans -= mod;
    if (ans < 0)
        ans += mod;
    return ans;
}

// int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<vector<int>> dirs;

void pr(vector<int> &v)
{
    cout << "Printing vector---\n";
    for (auto x : v)
    {
        // cout << x.ff << " "<<x.ss<<"\n";
        cout<<x<<" ";
    }
    cout << "\n";
}

class Hashing{
    public:

    string s;
    int p = 53;

    int n;
    vector<int>prefixHash;
    vector<int>powersOfP;
    vector<int>inversePowersOfP;

    Hashing(string a){
        s = a;
        n = s.size();
        prefixHash.resize(n);
        powersOfP.resize(n);
        inversePowersOfP.resize(n);
        calculatePowersOfP();
        calculatePrefixHash();
    }

    void calculatePowersOfP() {
        int currentPower = 1;
        for(int i=0;i<n;i++){
            powersOfP[i] = currentPower;
            currentPower = mult(currentPower, p);
        }

        inversePowersOfP[n-1] = inverse(powersOfP[n-1]);
        for(int i=n-2;i>=0;i--){
            inversePowersOfP[i] = mult(inversePowersOfP[i+1],p);
        }
    }

    void calculatePrefixHash() {
        int hashSoFar = 0;
        for(int i=0;i<n;i++) {
            hashSoFar = hashSoFar + ((s[i]-'a'+1)*powersOfP[i])%mod;
            prefixHash[i] = hashSoFar;
        }
    }

    int getHash(int l, int r){
        int val1 = prefixHash[r];
        int val2 = l==0?0:prefixHash[l-1];
        int x = add(val1,-val2);
        return mult(x,inversePowersOfP[l]);
    }

};



string s;

void solve() {
    cin>>s;
    int n = s.size();
    Hashing h = Hashing(s);

    vector<int>ans;
    for(int k=1;k<n;k++){
        int hash1 = h.getHash(0,k-1);
        int hash2 = h.getHash(n-k,n-1);
        if(hash1==hash2) ans.push_back(k);
    }

    for(auto it:ans){
        cout<<it<<" ";
    }

}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;

    // init();
    while (t--)
    {
        // cin>>s;
        // if(s=="0") break;
        solve();
    }
    // for(tt=1;tt<=t;tt++){
    //     cin>>s;
    //     cout<<rec(0,1,1)<<"\n";
    // }
    return 0;
}
