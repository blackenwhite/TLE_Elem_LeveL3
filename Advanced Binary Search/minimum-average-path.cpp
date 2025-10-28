/**

The road network consists of 𝑛
 junctions and 𝑚
 one-way roads, with each road leading from a lower-numbered junction to a higher-numbered junction. Each road has a number. Your task is to find a path from junction 1 to junction 𝑛
 at which the arithmetic mean of the numbers corresponding to the edges is minimal possible.

Input
The first line contains integers 𝑛
 and 𝑚
 (2≤𝑛≤105
, 1≤𝑚≤105
). The next 𝑚
 lines contain triples of numbers 𝑎𝑖
, 𝑏𝑖
, 𝑐𝑖
 (1≤𝑎𝑖<𝑏𝑖≤𝑛
, 0≤𝑐𝑖≤100
), which means that there is a road leading from the junction 𝑎𝑖
 to the junction 𝑏𝑖
, which corresponds to the number 𝑐𝑖
. For each pair of junction, there is at most one road that connects them. It is guaranteed that there is a path from junction 1 to junction 𝑛
.

Output
On the first line print the number of edges in the selected path 𝑘
. On the next line print 𝑘+1
 integers, indices of junctions visited by the selected path.
 * problem:
 * author: Nabajyoti
 *
 * ./program < input.txt > output.txt
 *
 * ulimit -s unlimited
 */
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>  // for fixed and setprecision
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second

using ll = long long int;
using ld = double;

using pii = pair<ll, ll>;
using vvl = vector<vector<ll>>;
using vl = vector<ll>;
const ll N = 2e5 + 2;
const ll mod = 1e9 + 7;
ll inf = 1e18;
const int nn = 20;

ll __gcd(ll a, ll b) {
    if (a == 0) return b;
    return __gcd(b % a, a);
}

ll mult(ll a, ll b)  // O(1)
{
    return ((a % mod) * (b % mod)) % mod;
}

// ll dirs[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
ll dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void print(vector<ll>& v) {
    cout << "printing array ---> \n";
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

void print(vvl& v) {
    cout << "printing array-->\n";
    for (auto it : v) {
        for (auto x : it) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) { return power(a, mod - 2, mod); }

long long binomial(long long n, long long k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    long long numerator = 1;
    for (long long i = 0; i < k; i++) {
        numerator = (numerator % mod * ((n - i) % mod)) % mod;
    }

    long long denominator = 1;
    for (long long i = 1; i <= k; i++) {
        denominator = (denominator * i) % mod;
    }

    return (numerator * modInverse(denominator, mod)) % mod;
}

/*-------------------------------------- x ----------------------------------------------*/

ll n, m;
vector<vector<pii>> adj;
vl par;
vector<ld> dp;

ld dfs(ll node, ld mid, vector<ll>& path) {
    if (node == n) {
        path[n] = n;
        return 0.0;
    }
    if (dp[node] != inf) return dp[node];
    ld ans = inf;
    ll child = -1;
    for (auto it : adj[node]) {
        ld temp = dfs(it.first, mid, path) + (it.second - mid);
        if (temp < ans) {
            ans = temp;
            child = it.ff;
        }
    }
    path[node] = child;
    return dp[node] = ans;
}

bool check(ld mid) {
    dp.assign(n + 1, inf);
    vl path(n + 1, 0);
    ld minn = dfs(1, mid, path);
    if (minn <= 0) {
        par = path;
        return true;
    }
    return false;
}

void solve(ll tt) {
    cin >> n >> m;
    adj.assign(n + 1, {});
    par.assign(n + 1, -1);

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    ld lo = 0, hi = 100.1;
    for (ll i = 0; i < 30; i++) {
        ld mid = (lo + hi) / 2.0;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    vl ans;
    ll node = 1;
    while (true) {
        ans.push_back(node);
        if (node == n) {
            break;
        }
        node = par[node];
    }

    cout << ans.size() - 1 << "\n";
    for (auto it : ans) {
        cout << it << " ";
    }
}

signed main() {
    ll t = 1;
    // cin >> t;
    for (ll tt = 1; tt <= t; tt++) {
        solve(tt);
    }
}
