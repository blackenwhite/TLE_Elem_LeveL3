// leetcode 719 Hard
// level Hard

class Solution {
    vector<int>v;
    int k;

    int bin_search(int start, int end, int tar) {
        int lo = start, hi = end;
        int ans = start;
        while(lo<=hi) {
            int mid = (lo+hi)/2;
            if(v[mid]<=tar){
                ans = mid;
                lo  = mid+1;
            } else {
                hi = mid-1;
            }
        }
        return ans;
    }

    bool check(int guess){
        // cout<<"checking for "<<guess<<"\n";
        int ans = 0;
        int n = v.size();

        for(int i=0;i<n-1;i++){
            int target = v[i] + guess;
            int j = bin_search(i,n-1,target);
            ans += j-i;
        }
        // cout<<"total pairs = "<<ans<<"\n";
        return (ans>=(k));
    }
public:
    int smallestDistancePair(vector<int>& nums, int K) {
        sort(nums.begin(), nums.end());
        v = nums;
        k = K;
        int lo = 0, hi = 1e6;
        int ans = -1;
        while(lo<=hi) {
            int mid = (lo+hi)/2;
            if(check(mid)){
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid+1;
            }
        }
        return ans;
    }
};
