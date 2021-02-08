#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  50002;
const unsigned int MX1 = 100002;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P

int K, ans, n[MX], sum[MX], vis[MX1];
VI g[MX1];
ll dc[2],cc[2];

set<int> ba[MX][2], fw[MX][2],cb[MX];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> K;
    int u=0, z; 
    for(int i = 0; i<K; ++i) {
        cin >> n[i]>>z;
        VI* f = g+u;
        sum[i] = u;
        for (int j =0; j<z; ++j) {
            int a, b; 
            cin >> a>>b;a--, b--;
            f[a].push_back(b);
            if(b!=a) f[b].push_back(a);
        }
        u+=n[i];
    }

    for (int k = 0; k<K; ++k){
        fw[k][0].insert(0);
        ba[k][0].insert(0);
        cb[k].insert(0);
    }
    int a = 0, b=1;
    dc[a] = 1;
    for (int l = 1; ;++l) {
        int s=0;
        for (int k = 0; k<K; ++k) {
            VI *f = g+sum[k];
            int *v = vis+sum[k];
            fw[k][b].clear();
            int va = 1<<a;
            int vb = 1<<b;
            for (auto i:fw[k][a]) {
                for(auto j:f[i]) {
                    if((v[j]&va)==0) {
                        v[j] |= va;
                        fw[k][b].insert(j);
                        ba[k][b].insert(j);
                        cb[k].insert(j);
                    }
                }
            }
            s+= fw[k][b].size();
        }
        if(s==0) break;

        cc[b] = 1;
        ll p = 1;
        for (int k = 0; k<K; ++k) {
            p*= ba[k][b].size(); MOD2(p);
            cc[b]*= (ba[k][b].size() + ba[k][a].size() - cb[k].size()); MOD2(cc[b]); 
        }
        

        ll tt = p - dc[b] -(cc[b]-cc[a]) + P * 2;
        tt = tt * l + ans; MOD2(tt);
        dc[b] = p;
        ans = tt;

        a^=1;b^=1;
    }

    cout << ans << endl;
}
