#include<bits/stdc++.h>
using namespace std;

ifstream fin("treedepth.in");
ofstream fout("treedepth.out");
const unsigned int MX = 302;
typedef long long ll;

#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P

int N, K, P;
int ans[MX];

int dp[MX][MX*MX/2],dp1[MX][MX*MX/2];
int a[MX], sa[MX], b[MX], sb[MX];

int main()
{
    fin >> N >> K >> P;
    dp[0][0]=1;
    for(int i=1; i<=N; ++i){
        for(int j=0; j<=K; j++ ) {
            dp[i][j] += dp[i-1][j]; MOD(dp[i][j]);
            if(j>=i){
                dp[i][j] -= dp[i-1][j-i]; MODS(dp[i][j]);
            }
            dp[i][j+1] = dp[i][j];
        }
    }

    dp1[N+1][0]=1;
    for(int i=N; i>=1; --i){
        for(int j=0; j<=K; j++){
            dp1[i][j] += dp1[i+1][j]; MOD(dp1[i][j]);
            if(j>=i){
                dp1[i][j] -= dp1[i+1][j-i]; MODS(dp1[i][j]);
            }
            dp1[i][j+1] = dp1[i][j];
        }
    }


    for(int i=1; i<=N; ++i){
        for(int j=0; j<=K; j++ ) {
            a[i] = ((ll)dp[i-1][j]*dp1[i+1][K-j]+a[i])%P;
            if(j<=(K-(i-1))){
                b[i] = ((ll)dp[i-1][j]*dp1[i+1][K-(i-1)-j] + b[i])%P;
            }
        }

        sa[i] = sa[i-1]+a[i]; MOD(sa[i]);
        sb[i] = sb[i-1]+b[i]; MOD(sb[i]);
    }

    for(int i=1; i<=N; ++i){
        ans[i] = ((ll)dp[N][K] + P*2+ sa[i] - sa[1] +sb[N-i+1] - sb[1])%P;
    }

    fout << ans[1];
    for(int i=2; i<=N; ++i) fout << " " << ans[i];
    fout << endl;
}
