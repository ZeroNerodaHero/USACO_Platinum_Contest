#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  200002;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define SMIN(x, y) ((b[x]<=b[y])? x:y)

int N, Q, u,v,l,r,m, ans;
int a[20][MX], b[MX], c[MX], c1[MX], d[MX];
int p[MX];
int f[MX];

int find(int l, int r)
{
    m = d[r-l+1];
    return SMIN(a[m][l], a[m][r-(1<<m)+1]);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> Q;

    for (int i = 1; i<=N; ++i) cin>>b[i], a[0][i] =i;
    for (int i = 1; (1<<i) <= N; ++i) { 
        d[1<<i] =i, v=i<<1, u=v>>1;
        for (int j =1; j+v<=N+1; j++) a[i][j] = SMIN(a[i-1][j], a[i-1][j+u]);
    }

    for (int i = 1; i<=N; ++i) {
        if(d[i] ==0) d[i] = d[i-1];
        p[i] = p[i-1], f[i]=1, u=b[i], v=0;
        if(u>b[i-1]) v = 1;
        else if(u<b[i-1]) {
            if(c[u] == 0) v=1;
            else {
                m = find(c[u], i);
                v = (b[m] != b[i]);
            }
        }

        if(v) c[u] = c1[u] = i, p[i]++;
        else  f[c1[u]] = 0, c1[u] = i;
    }
    for (int i = N; i>=1; --i) f[i] += f[i+1];

    while(Q--) {
        cin >> l >> r;
        int m = find(l, r);
        ans = p[r] - p[m] + f[l]-f[m] + 1;
        cout << ans << endl;
    }
}
