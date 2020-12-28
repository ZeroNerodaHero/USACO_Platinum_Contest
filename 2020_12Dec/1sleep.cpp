#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 3000;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P

int N, c;
int ans = 0;
const int P = 1e9+7;

int s[MX], t[MX];
int dp[2][MX][2];
bool cow[2*MX];

void prep(void)
{
    c = 0;
    int i=1, j=1;

    while(j<=N&&t[j]<s[i]) ++j;
    while(j<=N){
        for (; i<=N&&s[i]<=t[j]; i++) {
            cow[c++] =1;
        }

        if(i<=N) {
            for(;j<=N && t[j]<s[i];j++) {
                c++;
            }
        } else {
            c+= N-j+1;
            j=N+1;
        }
    }
    N = i-1;
}

int main()
{
    cin >> N;
    for (int i = 1; i<= N; ++i) cin >> s[i];
    for (int i = 1; i<= N; ++i) cin >> t[i];
    sort(s+1, s+N+1);
    sort(t+1, t+N+1);
    prep();

    int a = 0,b = 1;
    dp[0][0][0] = 1;
    for(int i = 0; i < c; i++){
        memset(dp[b],0,sizeof(dp[b]));
        if(cow[i]){
            for(int j = 0; j < N; j++){
                for(int k = 0; k < 2; k++){
                    dp[b][j+1][k] += dp[a][j][k]; MOD(dp[b][j+1][k]);
                    dp[b][j][1] += dp[a][j][k]; MOD(dp[b][j][1]);
                }
            }
        } else{
            for(int j = 0; j < N; j++){
                for(int k = 0; k < 2; k++){
                    if(j > 0){
                        dp[b][j-1][k] += ((long long)j*dp[a][j][k])%P;
                        MOD(dp[b][j-1][k]);
                    }
                }
                dp[b][j][0] += dp[a][j][0]; MOD(dp[b][j][0]);
            }
        }
        a ^= 1;
        b ^= 1;
    }

    ans = dp[a][0][0] + dp[a][0][1]; MOD(ans);
    cout << ans << endl;
}
