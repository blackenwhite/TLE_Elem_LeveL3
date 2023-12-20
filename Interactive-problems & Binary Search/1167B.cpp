#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
#define pii pair<int, int>
#define N 100005
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
        cout << x << " ";
    }
    cout << "\n";
}


int n;
vector<int>v,pref;

struct node{
    int x,y,z;
};

void print(int a, int b) {
    cout<<"? "<<a<<" "<<b<<endl;
}

node foo(pii a, pii b){
    node ans;
    if(a.ff==b.ff || a.ff==b.ss){
        ans.y = a.ff;
        ans.x = a.ss;
        ans.z = (ans.y == b.ff)? b.ss:b.ff;

    } else {
        ans.y = a.ss;
        ans.x = a.ff;
        ans.z = (ans.y == b.ff)? b.ss:b.ff;
    }
    return ans;
}

void solve()
{
    vector<int>v = {42,8,16,15,23,4};
    map<int,pii> mp;

    for(int i=0;i<5;i++){
        for(int j=i+1;j<6;j++){
            int x = v[i]*v[j];
            mp[x] = {v[i],v[j]};
        }
    }

    vector<int> ans(6);

    print(1,2);
    int res;
    cin>>res;
    pii a1a2 = mp[res];
    print(2,3);
    cin>>res;
    pii a2a3 = mp[res];
    // ans[1] = find_common(a1a2,a2a3);
    node temp = foo(a1a2,a2a3);
    ans[0] = temp.x; ans[1] = temp.y; ans[2] = temp.z;

    print(4,5);
    cin>>res;
    pii a4a5 = mp[res];

    print(5,6);
    cin>>res;
    pii a5a6 = mp[res];

    node t2 = foo(a4a5, a5a6);
    ans[3] = t2.x, ans[4] = t2.y, ans[5] = t2.z;

    cout<<"! ";
    for(int i=0;i<6;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;

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
        solve();
    }
    // for(tt=1;tt<=t;tt++){
    //     cin>>s;
    //     cout<<rec(0,1,1)<<"\n";
    // }
    return 0;
}
