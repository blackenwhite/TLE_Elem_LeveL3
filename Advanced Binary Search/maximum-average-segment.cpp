/**
Given an array of 𝑛
 and a number 𝑑
. Your task is to find a segment of length at least 𝑑
, on which the arithmetic mean of the elements is maximum possible.

Input
The first line contains two integers 𝑛
 and 𝑑
 (1≤𝑑≤𝑛≤105
). The next line contains 𝑛
 integers 𝑎𝑖
, the elements of array (0≤𝑎𝑖≤100
).

Output
Print two integers, indices of the first and last elements of the required segment (elements are numbered starting from 1).
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

ll n, d;
vl v;
pii res;

bool check(ld x) {
    vector<ld> pr(n);
    for (ll i = 0; i < n; i++) {
        pr[i] = (i ? pr[i - 1] : 0.0) + (v[i] - x);
    }

    ld min_val = 0.0;
    ll min_pos = -1;

    for (ll i = d - 1; i < n; i++) {
        ll left_bound = i - d;
        if (left_bound >= 0 && pr[left_bound] < min_val) {
            min_val = pr[left_bound];
            min_pos = left_bound;
        }
        if (pr[i] >= min_val) {
            res.ff = min_pos + 1;
            res.ss = i;
            return true;
        }
    }
    return false;
}

void solve(ll tt) {
    cin >> n >> d;
    v.resize(n);
    for (ll i = 0; i < n; i++) cin >> v[i];

    ld lo = 0.0, hi = 101.0;
    ll finalL = 0, finalR = d - 1;
    for (int iter = 0; iter < 60; ++iter) {
        ld mid = (lo + hi) / 2.0;
        if (check(mid)) {
            lo = mid;
            finalL = res.ff;
            finalR = res.ss;
        } else {
            hi = mid;
        }
    }
    cout << finalL + 1 << " " << finalR + 1 << "\n";
}

signed main() {
    ll t = 1;
    // cin >> t;
    for (ll tt = 1; tt <= t; tt++) {
        solve(tt);
    }
}
