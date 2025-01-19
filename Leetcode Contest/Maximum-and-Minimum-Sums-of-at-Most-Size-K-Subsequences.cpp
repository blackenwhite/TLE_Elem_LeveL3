/*
You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.

A non-empty subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Since the answer may be very large, return it modulo 109 + 7.
*/

const int MOD = 1e9+7;
#define ll long long

class Solution {
public:
    ll modPow(ll x, ll y, int mod) {
        ll res = 1;
        while(y>0) {
            if(y%2) res = res*x%mod;
            x = x*x %mod;
            y>>=1;
        }
        return res;
    }

    void getFactorials(vector<ll>&fact, vector<ll>&invFact, int n) {
        fact[0] = invFact[0] = 1;
        for(int i=1;i<=n;i++) {
            fact[i] = fact[i-1]*i%MOD;
        }

        invFact[n] = modPow(fact[n], MOD-2, MOD); // fermat's little theorem

        for(int i=n-1;i>=1;i--) {
            invFact[i] = invFact[i+1] * (i+1) % MOD;
        }
    }

    ll nCr(int n, int r, vector<ll>&fact, vector<ll>&invFact) {
        if(r>n || r<0) return 0;
        return fact[n]*invFact[r] % MOD * invFact[n-r] % MOD;
    }

    int minMaxSums(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<ll>fact(n+1), invFact(n+1);

        getFactorials(fact, invFact, n);

        ll result = 0;
        for(int i=0;i<n;i++){
            for(int size=1;size<=k;size++) {
                ll minContri = nums[i]*nCr(n-i-1, size-1, fact, invFact) % MOD;
                ll maxContri = nums[i]*nCr(i, size-1, fact, invFact) % MOD;

                result = (result + maxContri + minContri)%MOD;
            }
        }

        return (int) result;
    }
};
