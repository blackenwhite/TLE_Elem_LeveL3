// codeforces 1810C
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1e12+7;
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

int fact[10]; // make it to N
int invFact[10]; // make it to N

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
        cout << x << " ";
    }
    cout << "\n";
}

int n,a,b;
vector<int>v;

int p[N];

void solve() {
    cin>>n>>a>>b;
    set<int>st;

    int cost = 0;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        if(st.find(x)==st.end()){
            st.insert(x);
        } else {
            cost+=a;
        }
    }

    int c=0;
    for(auto x:st) {
        p[++c] = x;
    }

    int ans = inf;

    for(int i=1;i<=c;i++){
        ans = min(ans, b*(p[i]-i)+(c-i)*a);
    }

    ans = min(ans, c*a+b);
    cout<<(ans+cost)<<"\n";

}


signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int t = 1;
    cin >> t;

    // init();
    while (t--)
    {
        solve();
    }
    // for(tt=1;tt<=t;tt++){
    //     cin>>s;
    //     cout<<rec(0,1,1)<<"\n";
    // }
    return 0;
}
