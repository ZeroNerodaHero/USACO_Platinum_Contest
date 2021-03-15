#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 100005;
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

int N, M, T, u,v, ans, d[MX], d1[MX];
MI m[MX];
VI g[MX];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
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

        ans = N-1; if(d1[1] == 2) ans++;
        if(d1[1] == 0|| ans ==N){
            cout << ans << endl;
            continue;
        }
        int D = 0;
        for(int i = 1; i <= N; i++) D = max(D, d[i]);
        for(int i = 1; i <= D; i++) m[i].clear();
        for(int i = 1; i <= N; i++) m[d[i]][d1[i]]++;

        int a = 1, b=0;
        for(int i = 2; i <= D; i++){
            m[b].clear();
            for(auto& j: m[i]){
                auto best = m[i-1].find(j.f-1); // increasing
                auto must = m[a].find(j.f+1); // decreasing
                if(best == m[i-1].end()) { // not set by increasing parent d1
                    if(must != m[a].end()) {
                        if(must->s >0) { 
                            if (j.s<must->s) ans+= must->s-j.s;
                        } else {
                            ans -= min(-must->s, j.s);
                        }
                    }

                    if(j.f==i+1) {
                        ans+=(j.s+1)/2;
                    } else {
                        m[b][j.f] = j.s;
                    }
                } else { // set by increasing parent d1
                    if(must != m[a].end()) {
                        int v = min(abs(must->s), j.s);
                        if(must->s>0) ans += must->s;
                        if(j.f==i+1) {
                            ans += (v+1)/2-v;
                        } else { // I must depend on best one
                            m[b][j.f] = -v;  // optimize via loop
                        }
                    }
                }
            }

            a^=1; b^=1;
        }

        cout << ans << endl;
    }
}
