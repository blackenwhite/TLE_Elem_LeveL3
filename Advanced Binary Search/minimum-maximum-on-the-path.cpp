/*
The road network consists of 𝑛
 junctions and 𝑚
 one-way roads, with each road leading from a lower-numbered junction to a higher-numbered junction. Each road has a number. Your task is to find a path from junction 1 to junction 𝑛
, consisting of at most 𝑑
 edges, on which the maximum of the numbers corresponding to the edges is minimal possible.

Input
The first line contains integers 𝑛
, 𝑚
, and 𝑑
 (2≤𝑛≤105
, 1≤𝑚,𝑑≤105
). The next 𝑚
 lines contain triples of numbers 𝑎𝑖
, 𝑏𝑖
, 𝑐𝑖
 (1≤𝑎𝑖<𝑏𝑖≤𝑛
, 0≤𝑐𝑖≤109
), which mean that there is a road, leading from the junction 𝑎𝑖
 to the junction 𝑏𝑖
, which has number 𝑐𝑖
. For each pair of junctions, there is at most one road that connects them.

Output
On the first line print the number of edges in the selected path 𝑘
 (𝑘≤𝑑
). On the next line print 𝑘+1
 integers, indices of junctions visited by the selected path.

If there is no path from junction 1 to junction 𝑛
 consisting of at most 𝑑
 edges, print one integer −1
.

Key Takeaway:
The critical insight was: For a fixed maximum edge weight, we only care about reaching each node with the minimum number of edges, not all possible ways to reach it.

*/

/**
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

ll n, m, d;
vector<pii> v[N];

vector<ll> ans;

bool dfs(ll node, vector<bool>& visited, ll x, vector<ll>& tempAns, ll rem) {
    if (node == n) {
        tempAns.push_back(node);
        return true;
    }
    visited[node] = true;
    bool ans = false;
    for (auto it : v[node]) {
        if (!visited[it.ff] && it.ss <= x && rem > 0) {
            bool possible = dfs(it.ff, visited, x, tempAns, rem - 1);
            if (possible) {
                tempAns.push_back(node);
                return true;
            }
        }
    }
    return ans;
}

bool check(ll mid) {
    queue<pair<ll, ll>> q; // {node, edges_used}
    vector<ll> dist(n + 1, inf); // minimum edges to reach each node
    vector<ll> parent(n + 1, -1);
    
    q.push({1, 0});
    dist[1] = 0;
    
    while (!q.empty()) {
        auto [node, edges] = q.front();
        q.pop();
        
        if (node == n) {
            // Reconstruct path
            ans.clear();
            ll curr = n;
            while (curr != -1) {
                ans.push_back(curr);
                curr = parent[curr];
            }
            return true;
        }
        
        if (edges >= d) continue;
        
        for (auto it : v[node]) {
            ll next = it.ff;
            ll weight = it.ss;
            if (weight <= mid && dist[next] > edges + 1) {
                dist[next] = edges + 1;
                parent[next] = node;
                q.push({next, edges + 1});
            }
        }
    }
    return false;
}

void solve(ll tt) {
    cin >> n >> m >> d;
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        v[a].push_back({b, c});
    }

    ll lo = 0, hi = 1e9;
    ll res = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid)) {
            res = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    if (res == -1) {
        cout << -1 << "\n";
        return;
    }
    cout << ans.size()-1 << "\n";
    for (ll i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

signed main() {
    ll t = 1;
    // cin >> t;
    for (ll tt = 1; tt <= t; tt++) {
        solve(tt);
    }
}
