#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  152;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P
#define f first
#define s second

int N, ans, a,b=1;
int dp[2][2][2][MX][MX];
int sum[2][2][2][MX][MX];
char ar[MX][MX];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=1; i<=N; ++i) {
        cin>> (ar[i]+1);
    }

    for (int r = 1; r <= N; r++) {
	    memset(dp[b], 0, sizeof(dp[b]));
		memset(sum, 0, sizeof(sum));

        for (int y = 1; y <= N; y++) {
            for (int x = y; x > 0; x--) {
                for (int j = 0; j < 2; j++) {
                    sum[0][0][j][x][y] = dp[a][0][j][x][y];
                    if (x < y) {
                        sum[0][0][j][x][y] += sum[0][0][j][x+1][y]; MOD(sum[0][0][j][x][y]);
                    }
                }
            }
            for (int x = 1; x <= y; x++) {
                for (int j = 0; j < 2; j++) {
                    sum[0][1][j][x][y] = sum[0][1][j][x-1][y] + dp[a][0][j][x-1][y]; MOD(sum[0][1][j][x][y]);
                    sum[0][1][j][x][y] += dp[a][1][j][x][y]; MOD(sum[0][1][j][x][y]);
                }
            }
        }
            
        for (int x = 1; x <= N; x++) {
            for (int y = x; y <= N; y++) {
                for (int i = 0; i < 2; i++) {
                    sum[1][i][0][x][y] = sum[0][i][0][x][y];
                    if (y > x) {
                        sum[1][i][0][x][y] += sum[1][i][0][x][y-1]; MOD(sum[1][i][0][x][y]);
                    }
                }
            }

            for (int y = N; y >= x; y--) {
                for (int i = 0; i < 2; i++) {
                    sum[1][i][1][x][y] = sum[0][i][1][x][y] + sum[0][i][0][x][y+1]; MOD(sum[1][i][1][x][y]);
                    sum[1][i][1][x][y] += sum[1][i][1][x][y+1]; MOD(sum[1][i][1][x][y]);
                }
            }
        }
            
        for (int x = 1; x <= N; x++) {
            bool cc = true; //connected component
            for (int y = x; y <= N; y++) {
                cc = cc && (ar[r][y]=='G');
                if (cc) {
                    dp[b][0][0][x][y] = sum[1][0][0][x][y]+1; MOD(dp[b][0][0][x][y]);
                    dp[b][0][1][x][y] = sum[1][0][1][x][y] - sum[1][0][1][y+1][y+1]; MODS(dp[b][0][1][x][y]);
                    dp[b][0][1][x][y] -= dp[a][0][0][y+1][y+1]; MODS(dp[b][0][1][x][y]);

                    dp[b][1][0][x][y] = sum[1][1][0][x][y];
                    dp[b][1][1][x][y] = sum[1][1][1][x][y];
                } else {
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            dp[b][i][j][x][y] = 0;
                        }
                    }
                }
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        ans += dp[b][i][j][x][y]; MOD(ans);
                    }
                }
            }
        }
        a^=1,b^=1;
    }
    cout << ans << endl;
}

