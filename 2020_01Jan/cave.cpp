#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const unsigned int MX = 1005;
const unsigned int MX1 = 1005<<8;
const int P = 1e9+7;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P

int N, M, t, s = 1;
string g[MX];
int id[MX][MX], p[MX1], q[MX1];

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int find(int x){
    if(p[x] == 0) return x;
    p[x] = find(p[x]);
    return p[x];
}

int main()
{
    setIO("cave");
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        cin >> g[i];
    }

    for(int i = N-2; i > 0; i--){
        for(int j = 1; j < M-1; j++){
            if(g[i][j] == '#') continue;
            if(g[i][j-1] == '#'){
                id[i][j] = ++t;
                q[t] = 1;
            } else{
                id[i][j] = t;
            }
            if(g[i+1][j] == '.'){
                int par = find(id[i+1][j]);
                if(par != t){
                    p[par] = t;
                    q[t] = ((ll)q[t] * q[par])%P; 
                }
            }
        }
        //fill water at row i
        for(; s <= t; s++){
            q[s]++; MOD(q[s]);
        }
    }    

    ll ans = 1;
    while(t > 0){
        int par = find(t); 
        if(par == t){
            ans = (ans * q[t])%P; 
        }
        t--;
    }
    cout << ans << endl;
}
