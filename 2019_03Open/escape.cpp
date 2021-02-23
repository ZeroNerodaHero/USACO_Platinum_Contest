#include <bits/stdc++.h>

using namespace std;
const int MX = 30005;
const int MXS = 160;
const int MXH = (1<<18);
typedef long long ll;
typedef pair<ll, int> PI;
typedef vector<int> VI;

#define P 1000000007
#define MOD(x) if(x>=P) x-=P
#define OO(x) x
#define OP(x)

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int hs[MXH];
int N, K, C;
int lc[MX][8], dc[MX][8];
ll cost[2][MXS];
int cnt[2][MXS];

int st[MXS][8], v[MXS];
int tx[MXS][8][2][2];
char c[8], t[8], f[8], q[MXS][8];

#if 0
void print(int a[], int b)
{
    for (int i=0; i<=b;++i) cout << a[i]<<' ';cout << endl;
}

#endif

void dfs(int k, int s)
{
    if(k > K) {
        hs[s] = ++C;
        v[C] = s;
        *(ll *)q[C] = *(ll *)c;
        for(int i = 1; i <= K; i++) {
            st[C][i] = (t[i] == 1 && c[i] == i);
        }
        return;
    }

    for(char l = k-1, i = l; i >= 0; i--) {
        if(i > l) {
            i = l;
        }
        if(c[i] == i) {
            if(i == 0) {
                t[k] = 1;
                c[k] = k;
            } else {
                c[k] = i;
                t[i]++;
            }
            dfs(k+1, s + (c[k]<<f[k]));
            if(i != 0) t[i]--;
            c[k] = 0;
        }
        l = min(l,c[i]);
    }
}

void setup()
{
    for(int k = 1; k<= K; k++)
    for(int s = 1; s <= C; s++)
    for(char d = 0; d < 2; d++) // down plug
    for(char l = 0; l < 2; l++){ // left plug
        int ns=v[s];
        if( d == 0 && l == 0){
            ns += (k-q[s][k])<<f[k];
            if(q[s][k] == k){
                int m = K+1;
                for(int i = k+1; i <= K; i++) if(q[s][i] == k){
                    m = min(m,i);
                }
                for(int i = k+1; i <= K; i++) if(q[s][i] == k){
                    ns += (m-q[s][i])<<f[i];
                }
            }
        } else if( d == 1 && l == 1){
            int u = q[s][k], v = q[s][k-1];
            int z = min(u,v);
            for(int i = 1; i <= K; i++) if(q[s][i] == u || q[s][i] == v) {
                ns += (z-q[s][i])<<f[i];
            }
        } else if(l == 1){ // actually it is l==1, and d==0
            ns += (q[s][k-1]-q[s][k])<<f[k];
            if(q[s][k] == k){
                int m = K+1;
                for(int i = k+1; i <= K; i++) if(q[s][i] == k){
                    m = min(m,i);
                }
                for(int i = k+1; i <= K; i++) if(q[s][i] == k){
                    ns += (m-q[s][i])<<f[i];
                }
            }
        }
        tx[s][k][d][l] = hs[ns];
        if(k == 1) l++;
    }
}

int main()
{
    cio("escape");
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j < K; j++) cin >> lc[i][j];
    for(int j = 1; j <= K; j++)
        for(int i = 1; i < N; i++) cin >> dc[i][j];
    for(int i = 2; i <= K; i++) f[i] = f[i-1]+3;
    dfs(1,0);
    setup();

    memset(cost[0], 1, sizeof(cost[0]));
    cost[0][C] = 0;
    cnt[0][C] = 1;

    int a = 0, b = 1;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= K; j++){
            memset(cost[b], 1, sizeof(cost[b]));
            for(int s = 1; s <= C; s++) if(cnt[a][s]){
                for(char d = 0; d < 2; d++){
                    if(d == 0 && i != 1 && st[s][j]) continue;
                    for(char l = 0; l < 2; l++){
                        int ns = tx[s][j][d][l];
                        if(ns == 0) continue;
                        ll nc = cost[a][s];
                        if(l) nc += lc[i][j-1];
                        if(d) nc += dc[i-1][j];
                        if(cost[b][ns] == nc){
                            cnt[b][ns] += cnt[a][s]; MOD(cnt[b][ns]);
                        } else if(cost[b][ns] > nc){
                            cost[b][ns] = nc;
                            cnt[b][ns] = cnt[a][s];
                        }
                        if(j == 1) l++;
                    }
                    if(i == 1) d++;
                }
            }
            a^=1, b^=1;
        }
    }
    cout << cnt[a][1] << endl;
}
