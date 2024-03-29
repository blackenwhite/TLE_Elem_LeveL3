// CSES https://cses.fi/problemset/task/1081/

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



class UF {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	UF(int size) : parents(size+1), sizes(size+1, 1) {
		for (int i = 1; i <= size; i++) { parents[i] = i; }
	}

	
	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

	
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	
	bool connected(int x, int y) { return find(x) == find(y); }

    set<int> getSet(int m){
        set<int> res;
        for(int i=1;i<=m;i++) {
            // cout<<"parent of i = "<<i<<" "<<parents[i]<<"\n";
            res.insert(parents[i]);
        }
        return res;
    }
};

int n;
vector<int>v;

void solve() {
    cin>>n;
    v.resize(n);
    int maxx = -1;
    unordered_map<int,int> mp;

    for(int i=0;i<n;i++) {
        cin>>v[i];
        mp[v[i]]++;
        maxx = max(maxx,v[i]);
    }

    for(int i = maxx;i>=1;i--) {
        int cnt = 0;
        for(int j = i;j<=maxx;j+=i) {
            cnt+=mp[j];
        }
        if(cnt>=2) {
            cout<<i<<"\n";
            return;
        }

    }


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
