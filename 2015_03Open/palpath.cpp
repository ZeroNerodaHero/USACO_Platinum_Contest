#include <bits/stdc++.h>

using namespace std;
const int MX = 505;
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

int N;
char g[MX][MX];
int dp[2][MX][MX];

void printg(){
    for(int i = 1; i <= N; i++){
        cout << (g[i]+1) << endl;
    }
}

void printdp(int a){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cout << dp[a][i][j] << ' ';
        }
        cout << endl;
    }
        cout << endl;
}

int main(){
cio("palpath");
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> (g[i]+1);
    }
//printg();
    for(int i = 1; i <= N; i++){
        dp[0][i][i] = 1;
    }
    int a = 0, b = 1;
//printdp(a);
    for(int l = 1; l < N; l++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                dp[b][i][j] = 0;
            }
        }
        for(int i = 1; i <= N; i++){
            for(int j = i; j <= N; j++){
                int y = N+1-i-l;
                int y1 = N+1-j+l;
//cout << i << ", " << y << " -- " << j << ", " << y1 << endl;
                if(y < 1 || y1 > N) continue;
                if(y > y1) continue;
                if(g[i][y] != g[j][y1]) continue;
//cout << "point: " << i << ", " << y << " -- " << j << ", " << y1 << g[i][y] << g[j][y1]<< endl;
                if(i < N){
                    if(i+1 <= j && y <= y1-1) {
                        dp[b][i][j] += dp[a][i+1][j]; 
                        MOD(dp[b][i][j]);
//cout << "\t" << (i+1) << ", " << y << " -- " << j << ", " << (y1-1) <<" " << dp[a][i+1][j] << ", " << dp[b][i][j] << endl;
                    }
                    if(i+1 <= j-1) {
                        dp[b][i][j] += dp[a][i+1][j-1];
                        MOD(dp[b][i][j]);
//cout << "\t" << (i+1) << ", " << y << " -- " << (j-1) << ", " << (y1) <<" " << dp[a][i+1][j-1] << ", " << dp[b][i][j] << endl;
                    }
                }
                if(y+1 <= y1-1) {
                    dp[b][i][j] += dp[a][i][j];
                    MOD(dp[b][i][j]);
//cout << "\t" << (i) << ", " << (y+1) << " -- " << (j) << ", " << (y1-1) <<" " << dp[a][i][j] << ", " << dp[b][i][j] << endl;
                }
                if(i <= j-1 && y+1 <= y1) {
                    dp[b][i][j] += dp[a][i][j-1];
                    MOD(dp[b][i][j]);
//cout << "\t" << (i) << ", " << (y+1) << " -- " << (j-1) << ", " << (y1) <<" " << dp[a][i][j-1] << ", " << dp[b][i][j] << endl;
                }
            }
        }
        a ^= 1, b ^= 1;
//printdp(a);
    }
    cout << dp[a][1][N] << endl;
}
