#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 102;
typedef vector<int> VI;
typedef pair<int, int> PI;
typedef map<int, int> MI;

const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P

#define f first
#define s second

int N, M, T, u,v, d[MX], d1[MX];
MI m[MX];
VI g[MX];
ll comb[MX][MX], pow2[MX*MX];
ll mpow[MX][MX];

void init(){
    pow2[0] = 1; comb[0][0]=1;
    for(int i=1; i<MX*MX; ++i) {pow2[i] = pow2[i-1]<<1; MOD(pow2[i]);}
    for(int i=1; i<MX; ++i) {
        comb[i][0] = 1;
        for(int j=1; j<=i; ++ j) {
            comb[i][j] = comb[i-1][j-1]+comb[i-1][j]; MOD(comb[i][j]);
        }
    }

    for(int i = 0; i < MX; i++) {
        mpow[i][0] = 1;
        for(int j = 1; j < MX; j++) {
            mpow[i][j] = ((pow2[i]-1) * mpow[i][j-1]) % P; MODS(mpow[i][j]);
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
	init();
    for(int t =1; t<=T; t++) {
        cin >> N >> M;
        for(int i = 1; i<=N; ++i) g[i].clear(), d[i]=d1[i]=0;
        for(int i = 1; i<=M; ++i) {
            cin >> u>> v;
            g[u].push_back(v);
            if(u!=v) g[v].push_back(u);
        }

        queue<PI> q;
        d[1] = 1;
        q.push(PI(1,2));
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            for (auto v: g[u.f]) {
                if(d[v] == 0) {
                    d[v] = u.s;
                    q.push(PI(v, d[v]+1));
                } else if (d1[v] == 0){
                    if(((d[v]^u.s)&1) !=0) {
                        d1[v] = u.s;
                        q.push(PI(v, d1[v]+1));
                    }
                }
            } 
        }

        int D = 0, E=0, F0=2*N, F=0;
        for(int i = 1; i <= N; i++) D = max(D, d[i]), E = max(E, d1[i]), F0=min(F0,d[i]+d1[i]), F=max(F,d[i]+d1[i]);
        for(int i = 1; i <= F; i++) m[i].clear();
        for(int i = 1; i <= N; i++) m[d[i]][d1[i]]++;

        ll ans = 1;
        if(d1[1] == 0){
            for(int i=3; i<=D; ++i) {
                ans*=mpow[m[i-1].begin()->s][m[i].begin()->s]; MOD2(ans);
            }
            cout << ans << endl;
            continue;
        }

        for (int y=F0; y<=F; y+=2) {
            vector<ll> dp;
            for(int l=y/2, r=l+1; l>0 && r<=E; l--, r++) {
                vector<ll> dp1(m[l][r]+1);
                if(l==y/2) { // first one
                    for(int i=0; i<=m[l][r]; i++) {
                        for(int j=0; j<=i; j++) {
                            if((i^j)&1) dp1[i] -= comb[i][j] * pow2[(j*(j+1))/2];
                            else dp1[i] += comb[i][j] * pow2[(j*(j+1))/2];
                            dp1[i] %= P;
                        }
                        dp1[i] *= comb[m[l][r]][i];
                        dp1[i] %= P;
                    }
                } else {
                    for(int i=0; i<=m[l+1][r-1]; i++) {
                        for(int j=0; j<=m[l][r]; j++) {
                            ll ways = 0;
                            for(int k=0; k<=m[l+1][r-1]-i; k++) {
                                if((m[l+1][r-1]-i^k)&1) ways -= comb[m[l+1][r-1]-i][k] * mpow[i+k][j];
                                else ways += comb[m[l+1][r-1]-i][k] * mpow[i+k][j];
                                ways %= P;
                            }
                            dp1[j] += ((comb[m[l][r]][j] * dp[i]) % P) * ways;
                            dp1[j] %= P;
                        }
                    }
                }

                if(l==1) { // last one
                    dp = dp1;
                } else {
                    vector<ll> dp2(m[l][r]+1);
                    for(int i=0; i<=m[l][r]; i++) {
                        for(int j=m[l][r]-i; j<=m[l][r]; j++) {
                            dp2[j] += ((comb[i][i+j-m[l][r]] * mpow[m[l-1][r-1]][j]) % P) * dp1[i];
                            dp2[j] %= P;
                        }
                    }
                    dp = dp2;
                }
            }
            if(dp.size()>0) {
                ans *= dp.back(); ans %= P;
            }
        }
        MODS(ans);
        cout << ans << endl;
    }
}

