/**

Given 𝑛
 pairs of positive integers (𝑎1,𝑏1),(𝑎2,𝑏2),…,(𝑎𝑛,𝑏𝑛)
. Select 𝑘
 (1≤𝑘≤𝑛
) of them 𝑖1,𝑖2,…,𝑖𝑘
 so that the ratio 𝑎𝑖1+𝑎𝑖2+⋯+𝑎𝑖𝑘𝑏𝑖1+𝑏𝑖2+⋯+𝑏𝑖𝑘
 is maximum possible.

Input
The first line contains integers 𝑛
 and 𝑘
 (1≤𝑘≤𝑛≤105
). The next 𝑛
 lines contain pairs of integers 𝑎𝑖,𝑏𝑖
 (1≤𝑎𝑖,𝑏𝑖≤105
).

Output
Print the required maximum ratio. The answer will be considered correct if the relative or absolute error does not exceed 10−6
.
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

ll n, k;
vector<pii> v;

bool check(ld mid) {
    priority_queue<ld> pq;
    ld sum = 0;
    for (ll i = 0; i < n; i++) {
        ld temp = v[i].ff * 1.0 - v[i].ss * mid;
        pq.push(-temp);
        sum += temp;
        if (pq.size() > k) {
            ld out = -pq.top();
            pq.pop();
            sum -= out;
        }
    }
    return sum >= 0;
}

void solve(ll tt) {
    cin >> n >> k;
    v.assign(n, {});
    for (ll i = 0; i < n; i++) {
        cin >> v[i].ff >> v[i].ss;
    }

    ld lo = 0.0, hi = 1e5;
    for (ll i = 0; i < 50; i++) {
        ld mid = (lo + hi) / 2.0;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << fixed << setprecision(7) << lo << "\n";
}

signed main() {
    ll t = 1;
    // cin >> t;
    for (ll tt = 1; tt <= t; tt++) {
        solve(tt);
    }
}
