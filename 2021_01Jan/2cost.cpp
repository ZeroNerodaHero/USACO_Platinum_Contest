#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 200002;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P

struct node {
    int x,y;
    bool operator <(const node &o) const {
        return (y<o.y);
    }
};

struct nnn {
    int x, y;
    ll v;
};

int N,M,Q;
ll ans[MX];
nnn ok[MX];

ll c[MX];

node t[MX];
int m[MX], cnt[MX];

void cnt_sort()
{
    for (int i = 2; i<= Q; ++i){
        cnt[i] += cnt[i-1];
    }
    for (int i = 1; i<= Q; ++i){
        m[cnt[t[i].y]--] = i;
    }
}

long long dist(nnn &f, int x, int y) {
    return f.v + ((ll)x) * x * (y-f.y) + c[f.y]*(x-f.x);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 1; i<= M; ++i) cin >> c[i];
    cin>> Q;
    for (int i = 1; i<= Q; ++i) {cin >> t[i].x>>t[i].y;cnt[t[i].y]++;}
    //sort(t+1, t+Q+1);
    cnt_sort();
    ok[0].x=ok[0].y=1;

    for(int b=0, y=2, i=1; i<=Q; ) {
        int q = m[i];
        if (t[q].y<y) {
            if(t[q].x>=ok[b].x) {
                ans[q] = ok[b].v + c[t[q].y]*(t[q].x-ok[b].x);
                i++;continue;
            }
            int l = 0, r = b-1, m;
            while(l<r) {
                m=(l+r+1)/2;
                if (t[q].x >=ok[m].x) {
                    l = m;
                } else {
                    r = m-1;
                }
            }
            ans[q] = dist(ok[l], t[q].x, t[q].y);
            i++;continue;
        }

        for(;y<=t[q].y; y++) {
            int l, r = N, m;
            ll vi, vj, v;
            while(b > 0){
                vi = dist(ok[b], ok[b].x, y);
                vj = dist(ok[b], ok[b].x+1, y);
                if((vj-vi) <= c[y]) break;
                r=ok[b].x;
                b--;
            }
            l= ok[b].x;
            while(l < r){
                m = (l+r)/2;
                vi = dist(ok[b], m, y);
                vj = dist(ok[b], m+1, y);
                if((vj-vi) <= c[y]) {
                    l = m+1;
                } else {
                    r=m;
                }
            }
            nnn f = ok[b];
            if(l>ok[b].x) b++;
            ok[b].x = l, ok[b].y=y;
            ok[b].v = dist(f, l, y);
        }

    }

    for(int i =1; i<=Q;++i) {
        cout << ans[i] <<endl;
    }
}
