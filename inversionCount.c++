//leetcode problem link: https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/1272713596/

#include<bits/stdc++.h>
using namespace std;

class SegTree {
    public:
        vector<int> seg;
        int size;
        SegTree(int n) {
            size = n;
            seg.resize(4*n+1);
        }
        void Build(int index, int low, int high, vector<int> &arr) {
            if(low == high) {
                seg[index] = arr[low]; return;
            }
            int mid = (low + high)/2;
            Build(2*index+1, low, mid, arr);
            Build(2*index+2, mid+1, high, arr);
            seg[index] = seg[2*index+1] + seg[2*index+2];
        }
        void update(int index, int low, int high, int pos, int val) {
            if(low == high) {
                seg[index]+=val; return;
            }
            int mid = (low + high)/2;
            if(pos<=mid) update(2*index+1, low, mid, pos, val);
            else update(2*index+2, mid+1, high, pos, val);
            seg[index] = seg[2*index+1] + seg[2*index+2];
        }
        int query(int index, int low, int high, int left, int right) {
            if(high<left || right<low) return 0;
            if(left<=low && high<=right) return seg[index];
            int mid = (low+high)/2;
            int l = query(2*index+1, low, mid, left, right);
            int r = query(2*index+2, mid+1, high, left, right);
            return l + r;
        }
};
int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> v(n);
        int maxi = INT_MIN, mini = INT_MAX;
        for(int i=0;i<n;i++) {
            cin>>v[i];
            maxi = max(maxi, v[i]);
            mini = min(mini, v[i]);
        }
        if(maxi<0) maxi = 0;
        if(mini>0) mini = 0;
        vector<int> pos(maxi+1, 0);
        vector<int> neg(abs(mini)+1, 0);
        for(int i=0;i<n;i++) {
            if(v[i]>=0) pos[v[i]]++;
            else neg[-v[i]]++;
        }
        SegTree po(maxi+1), ne(abs(mini)+1);
        po.Build(0, 0, maxi, pos);
        ne.Build(0, 0, abs(mini), neg);
        vector<int> result;
        for(int i=0;i<n;i++) {
            int ans = 0;
            if(v[i]>=0) {
                po.update(0, 0, maxi, v[i], -1);
                ans += po.query(0, 0, maxi, 0, v[i]-1);
                if(mini!=INT_MAX and mini<0) ans += ne.query(0, 0, abs(mini), 0, abs(mini));
            }
            else {
                ne.update(0, 0, abs(mini), abs(v[i]), -1);
                ans += ne.query(0, 0, abs(mini), abs(v[i])+1, abs(mini));
            }
            result.emplace_back(ans);
        }
        for(int ele : result) {
            cout<<ele<<endl;
        }
    }
}
