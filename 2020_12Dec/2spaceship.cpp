#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 64;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P

struct query{
    int bs, s, bt, t;
};

int N,K,Q,NQ;
query q[MX];
int dp[2][2*MX][2*MX];
vector<int> g[MX], tg[MX];

int ans = 0;
const int P = 1e9+7;

int main()
{
    cin >> N >> K >> Q;
    NQ = N+Q;

    for(int i = 0; i < N; i++){
        string s;
        cin >> s;
        for(int j = 0; j < N; j++){
            if(s[j] == '1'){
                g[i].push_back(j);
                tg[j].push_back(i);
            }
        }
    }

    for(int i = 0; i < Q; i++){
        cin >> q[i].bs >> q[i].s >> q[i].bt >> q[i].t;
        q[i].bs--; q[i].s--; q[i].bt--; q[i].t--;
    }

    int a[NQ],b[NQ];

    for(int k = 0; k < K; k++){
        for(int m = 0; m < N; m++){
            memset(a,0,sizeof(a));           
            memset(b,0,sizeof(b));           
            
            a[m] = 1; 
            for(int p = 0; p < Q; p++){
                if(q[p].bs == k && q[p].s == m){
                    a[N+p] = 1;
                }       
            } 
            for(auto x: tg[m]){
                for(int i = 0; i < NQ; i++){
                    a[i] += dp[0][i][x]; MOD(a[i]);
                }
            }

            b[m] = 1;
            for(int p = 0; p < Q; p++){
                if(q[p].bt == k && q[p].t == m){
                    b[N+p] = 1;
                }
            }
            for(auto y: g[m]){
                for(int j = 0; j < NQ; j++){
                    b[j] += dp[0][y][j]; MOD(b[j]);
                }
            }

            for(int i = 0; i < NQ; i++){
                for(int j = 0; j < NQ; j++){
                    long long tmp = (long long) a[i] * b[j]; MOD2(tmp);
                    dp[1][i][j] += tmp; MOD(dp[1][i][j]);
                }
            }
        }

        for(int i = 0; i < NQ; i++){
            for(int j = 0; j < NQ; j++){
                dp[0][i][j] = dp[1][i][j];
            }
        }
    }
    for(int i = N; i < NQ; i++){
        cout << dp[0][i][i] << endl;
    }
}
