#include <bits/stdc++.h>

using namespace std;
const int MX = 262244;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N,ans = 1;
int a[MX];
int dp[60][MX];

int main(){
    cio("262144");
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
        dp[a[i]][i] = i+1;
    }
    for(int i = 2; i <= 58; i++){
        for(int j = 1; j <= N; j++){
            if(!dp[i][j]){
                dp[i][j] = dp[i-1][dp[i-1][j]];
            }
            if(dp[i][j]) ans = i;
        } 
    }
    cout << ans << endl;
}
