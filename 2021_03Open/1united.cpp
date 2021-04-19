#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  200002;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;

int N;
int a[MX], p[MX], f[MX], c[MX*4], lazy[MX*4];
ll ans, sum[MX*4];

ll query(int si, int ss, int se, int l, int r){ //sum
    if(lazy[si] != 0){
        sum[si] += c[si] * lazy[si];
        if(ss != se){
            lazy[si*2] += lazy[si];
            lazy[si*2+1] += lazy[si];
        }
        lazy[si] = 0;
    }

    if(r < ss || l > se) {
        return 0;
    }
    if(c == 0) return 0;
    if(ss >= l && se <= r) {
        return sum[si];
    }

    int m = (ss+se)/2;
    return query(si*2,ss,m,l,r)+ query(si*2+1,m+1,se,l,r);
}

ll query(int l, int r){
    return query(1,1,N,l,r);
}

int update(int si,int ss, int se, int i, int diff){ //c
    if(lazy[si] != 0){
        sum[si] += c[si] * lazy[si];
        if(ss != se){
            lazy[si*2] += lazy[si];
            lazy[si*2+1] += lazy[si];
        }
        lazy[si] = 0;
    }

    c[si] += diff;
    int s = 0;
    if(ss == se){
        if(diff < 0) {
            s = sum[si]; 
            sum[si] = 0;
        }
        return s;
    }
    if(ss != se){
        int m = (ss+se)/2;
        if(i <= m) s = update(2*si, ss,m,i,diff);
        else s = update(2*si+1,m+1,se,i,diff);
    }
    sum[si] -= s;
    return s;
}

void update(int i, int diff){
    update(1,1,N,i,diff);
}

void updaterange(int si, int ss, int se, int is, int ie, int diff){ //sum
    if(lazy[si] != 0){
        sum[si] += c[si] * lazy[si];
        if(ss != se){
            lazy[si*2] += lazy[si];
            lazy[si*2+1] += lazy[si];
        }
        lazy[si] = 0;
    }

    if(ie < ss || is > se) return;
    if(c[si] == 0) return;

    if(ss >= is && se <= ie){
        sum[si] += c[si] * diff;

        if(ss != se){
            lazy[si*2] += diff;
            lazy[si*2+1] += diff;
        }
        return;
    }

    int m = (ss+se)/2;
    updaterange(2*si,ss,m,is,ie,diff);
    updaterange(2*si+1,m+1,se,is,ie,diff);
    if(!(ss >= is && se <= ie))sum[si] = sum[si*2] + sum[si*2+1];
}

void updaterange(int is,int ie, int diff){
    return updaterange(1,1,N,is,ie,diff);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;

    for (int i = 1; i<=N; ++i) {
        cin>>a[i];
        f[i] = p[a[i]];
        p[a[i]] = i;
    }

    ans = 0;
    update(1,1);
    for(int i=2; i<=N; ++i) {
        int j = f[i]; update(i,1);
        if(i-j>2) {
            ans += query(j+1, i-1);
        }

        if(j+1 <= i-1) updaterange(j+1,i-1,1);
        if(j>0) {
            int k = f[j];
            if(k+1 <= j-1) updaterange(k+1,j-1,-1);
            update(j,-1);
        }

    }

    cout << ans << endl;
}
