#include <bits/stdc++.h>
using namespace std;

#define SIZE 7505 
#define MODS(x) if(x<0) x+=M
#define MOD(x) if(x >= M) x-=M
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

ifstream in("exercise.in");
ofstream out("exercise.out");

typedef unsigned long long ull;
typedef __uint128_t L;

struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};

FastMod F(1),B(1);

int N,M,m;
int t = 1;
int b[SIZE],s[SIZE][SIZE],dp[2][SIZE];
bool p[SIZE];

void init(){
    for(int i = 1; i <= N; i++){
        t = F.reduce((ll)t*i);
        s[i][i-1] = 1;
        for(int j = i; j <= N; j++){
            s[i][j] = F.reduce((ull)s[i][j-1]* j);
        }
    }

    int n = sqrt(N)+1;
    for(int i = 2; i <= N; i++){
        if(p[i]) continue;
        for(int j = i; j <= N; j += i){
            p[j] = 1;
        }
        b[m++] = i;
    }
}

ull modp(ull b, int y){
    ull z= 1;
    while(y){
        if(y & 1) z = B.reduce(z*b);
        b = B.reduce(b*b);
        y >>= 1;
    }
    return z;
}

int cnt(int x){
    memset(dp,0,sizeof(dp));
    int sum = 1;
    dp[0][0] = dp[1][0] = 1;

    for(int i = 1, j = 1; i <= N; i++, j++){
        if(j == x) j = 0;
        if(i >= x){
            dp[1][j] = F.reduce((ull)dp[1][j] * s[i-x+1][i-1]);
        }

        dp[0][i] = sum - dp[1][j]; MODS(dp[0][i]);
        dp[1][j] = F.reduce(sum + (ull)dp[1][j] * (i-1));
        sum = F.reduce((ll)sum * i + dp[0][i]);
    }
    sum = t - dp[0][N]; MODS(sum);
    return sum;
}

int main(){
    in >> N >> M;
    B = FastMod(M--);
    F = FastMod(M);

    init();
    ull ans = 1;
    for(int i = 0; i < m; i++){
        int exp = 0;
        for(int j = b[i]; j <= N; j *= b[i]){
            exp += cnt(j); MOD(exp);
        }
        ans = B.reduce(ans * modp(b[i],exp));
    }
    out << ans << endl;
}
