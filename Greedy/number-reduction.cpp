// codeforces 1765N
// author : Nabajyoti
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
#define pii pair<int, int>
#define N 1000100
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

void pr(vector<pii> &v)
{
    cout << "Printing vector---\n";
    for (auto x : v)
    {
        cout << x.ff << " "<<x.ss<<"\n";
    }
    cout << "\n";
}

int n,k;
string s;

void solve() {
    cin>>s;
    cin>>k;
    string t = "";
    n = s.size();

    deque<int>nums[10];

    for(int i=0;i<n;i++) {
        nums[s[i]-'0'].push_back(i);
    }

    for(int i=0;i<n;i++){
        int currentIdx = n, newIdx = n;
        for(int j=0;j<10;j++){
            if(nums[j].size())currentIdx = min(currentIdx,nums[j].front());
        }

        for(int j=(i==0);j<10;j++){
            if(nums[j].size() && nums[j].front()-currentIdx <=k ) {
                t+=('0'+j);
                newIdx = nums[j].front();
                break;
            }
        }
        k-=newIdx - currentIdx;

        for(int j=0;j<10;j++){
            while(nums[j].size() && nums[j].front()<=newIdx) nums[j].pop_front();
        }

        
    }
    cout<<string(t.begin(), t.end()-k)<<"\n";

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
