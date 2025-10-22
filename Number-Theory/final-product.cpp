/**
 * problem:
 * author: Nabajyoti
 *
 * ./program < input.txt > output.txt
 *
 * ulimit -s unlimited
 eta employees love two things: building cool products and scaling them up. As a new intern, you just started work on a cool product, but you want to make it even cooler during your internship.
Initially, your empty product has coolness 
1
1. Each of the next 
2
×
N
2×N days, you'll make a change, multiplying your product's coolness by any positive integer of your choice subject to the following requirements:
After the first 
N
N days, the coolness can be at most 
A
A (you're new to the codebase, so you shouldn't scale too quickly).
After all 
2
×
N
2×N days, your product should have coolness exactly 
B
B.
Please calculate how many sequences of 
2
×
N
2×N changes exist that yield a final product of coolness 
B
B, while ensuring a coolness of at most 
A
A after day 
N
N. As this number can be quite large, print it modulo 
1
0
9
+
7
10 
9
 +7.
Constraints
1
≤
T
≤
140
1≤T≤140
1
≤
N
≤
1
0
16
1≤N≤10 
16
 
1
≤
A
≤
1
0
14
1≤A≤10 
14
 
1
≤
B
≤
1
0
14
1≤B≤10 
14
 
Note: This chapter allows for much larger input than Chapter 1.
Input Format
Input begins with a single integer 
T
T, the number of test cases. Each case is a single line of three space-separated integers 
N
N, 
A
A, and 
B
B.
Output Format
For the 
i
i-th test case, print "Case #i: " followed by a single integer, the number of sequences of 
2
×
N
2×N nonnegative multipliers satisfying the above requirements, modulo 
1
0
9
+
7
10 
9
 +7.

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
// const ll N = 1e6 + 2;
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

ll n, A, B;
const ll M = 61;
ll fact[M];
ll invFact[M];

void init() {
    fact[0] = 1;
    for (ll i = 1; i < M; i++) {
        fact[i] = mult(i, fact[i - 1]);
    }

    invFact[M - 1] = modInverse(fact[M - 1], mod);
    for (ll i = M - 2; i >= 0; i--) {
        invFact[i] = mult(invFact[i + 1], i + 1);
    }
}

map<ll, ll> factorize(ll x) {
    map<ll, ll> ans;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            ans[i] = 0;
            while (x % i == 0) {
                ans[i]++;
                x = x / i;
            }
        }
    }
    if (x > 1) ans[x]++;
    return ans;
}

ll nCr(ll N, ll r) {
    if (r > N) return 0;
    if (r == 0 || r == N) return 1;

    ll nn = N;
    ll num = 1;  // numerator
    for (ll i = 0; i < r; i++) {
        num = mult(num, nn);
        nn--;
    }

    return mult(num, invFact[r]);
}

void solve(ll tt) {
    cin >> n >> A >> B;
    vector<ll> comb(60);
    for (ll i = 0; i <= 60; i++) {
        comb[i] = nCr(n + i - 1, i);
    }
    map<ll, ll> primesB = factorize(B);

    auto func = [&](ll x) -> ll {
        ll ans = 1;
        for (auto it : primesB) {
            ll p = it.ff;
            ll count = 0;
            while (x % p == 0) {
                count++;
                x = x / p;
            }
            ans = mult(ans, comb[count]);
        }
        return ans;
    };

    ll ans = 0;
    for (ll i = 1; i * i <= B; i++) {
        if (B % i == 0) {
            ll x = i, y = B / i;
            if (x <= A) {
                ans += mult(func(x), func(y));
                ans %= mod;
            }
            if(x!=y && y<=A) {
                ans += mult(func(x), func(y));
                ans%=mod;
            }
        }
    }
    cout << "Case #" << tt << ": " << ans << "\n";
}

signed main() {
    ll t = 1;
    cin >> t;
    init();
    for (ll tt = 1; tt <= t; tt++) {
        solve(tt);
    }
}
