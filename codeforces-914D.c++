//https://codeforces.com/contest/914/problem/D

#include<bits/stdc++.h>
using namespace std;

void fastio() {   
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class SegTree {
    public:
        vector<int> seg,place;
        int size;
        SegTree(int n) {
            size = n;
            seg.resize(n<<2+2);
            place.resize(n);
        }
        void Build(int index, int low, int high) {
            if(low == high) {
                cin>>seg[index]; return;
            }
            int mid = (low + high)>>1;
            Build(index<<1, low, mid);
            Build(index<<1|1, mid+1, high);
            seg[index] = __gcd(seg[index<<1], seg[index<<1|1]);
        }
        void update(int index, int low, int high, int pos, int val) {
            if(low == high) {
                seg[index] = val; return;
            }
            int mid = (low+high)>>1;
            if(pos<=mid) update(index<<1,low,mid,pos,val);
            else update(index<<1|1,mid+1,high,pos,val);
            seg[index] = __gcd(seg[index<<1], seg[index<<1|1]);
        }
        void query(int index, int low, int high, int left, int right, int& val, int x) {
           if(val>1) return;
           if(low == high) {
               val++; return;
           }
           int mid = (low + high)>>1;
           if(left<=mid && seg[index<<1]%x!=0) query(index<<1,low,mid,left,right,val,x);
           if(mid<right && seg[index<<1|1]%x!=0) query(index<<1|1,mid+1,high,left,right,val,x);
        }
};
int main() {
    fastio();
    int n;
    cin>>n;
    SegTree s(n);
    s.Build(1,1,n);
    int q;
    cin>>q;
    while(q--) {
        int type;
        cin>>type;
        if(type == 1) {
            int l,r,x,val=0;
            cin>>l>>r>>x;
            s.query(1,1,n,l,r,val,x);
            if(val>1) cout<<"NO"<<endl;
            else cout<<"YES"<<endl;
        }
        else {
            int i,x;
            cin>>i>>x;
            s.update(1,1,n,i,x);
        }
    }
}
