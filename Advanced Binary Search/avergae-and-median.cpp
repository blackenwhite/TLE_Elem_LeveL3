// https://atcoder.jp/contests/abc236/tasks/abc236_e

#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1000000007;
#define pii pair<int, int>
#define N 100005
int inf = 1e18;
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
vector<int>a;


double maxSum(vector<double> &v) {
    double dp[n+2][2];
    dp[n][0] = 0;
    dp[n][1] = 0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++) {
            double ans;
            if(j==1) {
                ans = v[i] + dp[i+1][0];
            } else {
                ans = max(v[i]+dp[i+1][0] , dp[i+1][1]);
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][0];
}

double get_best_avg() {
    double left = 0, right = 1e9;
    for(int iter=0;iter<=60;iter++) {
        double mid = (left+right)/2.0;
        vector<double> temp(n);
        for(int i=0;i<n;i++){
            temp[i]=a[i]-mid;
        }
        if(maxSum(temp)>=0){
            // cout<<"hello mid = "<<mid<<"\n";
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

int get_best_median() {
    int lo = 0, hi = 1e9;
    int ans = -1;
    while(lo<=hi) {
        int mid = (lo+hi)/2.0;
        vector<double> temp(n);
        for(int i=0;i<n;i++){
            temp[i] = a[i]>=mid?1:-1;
        }
        if(maxSum(temp)>0){
            ans = mid;
            lo = mid+1;
        } else {
            hi = mid-1;
        }
    }
    return ans;
}

void solve()
{
    cin>>n;
    a.resize(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    double avg = get_best_avg();
    printf("%.7f\n",avg);
    int med = get_best_median();
    printf("%lld", med);
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
