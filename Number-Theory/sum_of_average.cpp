/*
Time Limit: 2 sec / Memory Limit: 1024 MiB

Score : 
450 points

Problem Statement
You are given a positive integer 
N and a length-
N integer sequence 
A=(A 
1
​
 ,A 
2
​
 ,…,A 
N
​
 ).

Define 
f(l,r) as the (arithmetic) mean of 
A 
l
​
 ,A 
l+1
​
 ,…,A 
r
​
 .

Find 
1≤l≤r≤N
∑
​
 f(l,r), modulo 
998244353.

Definition of a rational number modulo 
998244353
Constraints
1≤N≤5×10 
5
 
0≤A 
i
​
 <998244353
All input values are integers.
Input
The input is given from Standard Input in the following format:

N
A 
1
​
  
A 
2
​
  
… 
A 
N
​
 
Output
Output the answer.

*/

/**
 * problem:
 * author: Nabajyoti
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
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define ff first
#define ss second
#define pb push_back

using ll = long long int;
using ld = long double;
using pii = pair<ll, ll>;
const ll N = 2e5 + 5;
// const ll mod = 1e9 + 7;
const ll mod = 998244353;
ll inf = 1e18;
using vl = vector<ll>;

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

// ----- end of utilities ------ //

ll n;
vector<ll> v;

void solve() {
    cin >> n;
    v.assign(n, 0);

    for (ll i = 0; i < n; i++) {
        cin >> v[i];
    }

    // pre-compute the inverses
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for (ll i = 2; i <= n; i++) {
        inv[i] = mod - (ll)(mod / i) * inv[mod % i] % mod;
    }

    // pre-compute the harmonic means
    vector<ll> H(n + 1);
    H[1] = inv[1];
    for (ll i = 2; i <= n; i++) {
        H[i] = (H[i - 1] + inv[i]) % mod;
    }

    // compute the coefficents and the ans simultaneously
    ll ans = 0;
    vector<ll> C(n);
    C[0] = H[n];
    ans += (C[0] * v[0]) % mod;
    ans %= mod;
    for (ll i = 1; i < n; i++) {
        C[i] = (C[i - 1] + H[n - i] - H[i] + mod) % mod;
        ans = ans + (C[i] * v[i]) % mod;
        ans %= mod;
    }

    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
