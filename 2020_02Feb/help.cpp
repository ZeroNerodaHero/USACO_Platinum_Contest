#include <bits/stdc++.h>
#include <array>
using namespace std;

#define P 1000000007
#define M 11
#define MX 100005
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

ifstream in("help.in");
ofstream out("help.out");

int N, K; 
int dp[M][MX<<2];
int lazy[MX<<2];
PI seg[MX];
int r[MX << 1];

static inline void init(int * a){
    for(int i = 0; i <= K; i++){
        a[i] = 0;
    }
}

void upd(int i, int s, int e){
    if(lazy[i] == 1) return;
    for(int j = 0; j <= K; j++){
        dp[j][i] = ((ll)dp[j][i] * lazy[i])%P; 
    }
    if(s != e){
        lazy[2*i] = ((ll) lazy[2*i] * lazy[i])%P;
        lazy[2*i+1] = ((ll) lazy[2*i+1] *lazy[i])%P;
    }
    lazy[i] = 1;
}

int c[M+1][M+1];
void inc(int * a){
    for(int i = K; i >= 0; i--){
        c[i][i] = a[i];
        for(int j = i+1; j <= K; j++){
            c[i][j] = c[i][j-1] + c[i+1][j]; MOD(c[i][j]);
        }
    }
    for(int i = 0; i <= K; i++){
        a[i] = c[0][i];
    }
}

void add(int i, int s, int e, int *  a, int pos){
    //if(pos < s || pos > e) return;

    upd(i,s,e);
    for(int j = 0; j <= K; j++){
        dp[j][i] += a[j]; MOD(dp[j][i]);
    }
    if(s != e){
        int mid = (s + e)/2;
        if(pos <= mid) add(2*i,s,mid,a,pos);
        else add(2*i+1,mid+1,e,a,pos);
    }
}

void sum(int i, int s, int e, int * a, int lo, int hi){
    if(hi < s || lo > e) return;
    upd(i,s,e);
    if(lo <= s && hi >= e){
        for(int j = 0; j <= K; j++){
            a[j] += dp[j][i]; MOD(a[j]);
        }
        return;
    }
    int mid = (s+e)/2;
    sum(2*i,s,mid,a,lo,hi);
    sum(2*i+1,mid+1,e,a,lo,hi);
}

void mul(int i, int s, int e, int pos){
    upd(i,s,e);       
    if(pos > e) return;
    if(s >= pos){
        lazy[i] = 2;
        upd(i,s,e);       
        return;
    }

    int mid = (s+e)/2;
    mul(2*i,s,mid,pos);
    mul(2*i+1,mid+1,e,pos);

    for(int j = 0; j <= K; j++){
        dp[j][i] = dp[j][2*i] + dp[j][2*i+1]; MOD(dp[j][i]);
    }
}

void solv(int a, int b){
    int u[M], v[M]; init(u); init(v);
    sum(1,0,N,u,0,a); inc(u);
    sum(1,0,N,v,a+1,b); 
    for(int i = 0; i <= K; i++){
         u[i] += v[i]; MOD(u[i]);
    }

    add(1,0,N,u,b);
    mul(1,0,N,b+1);
}

int main(){
    in >> N >> K;
    for(int i = 1; i <= N; i++){
        in >> seg[i].first >> seg[i].second;
        r[i] = seg[i].second;
    }
    int f[M]; init(f);
    f[0] = 1;
    add(1,0,N,f,0);

    sort(seg+1,seg+N+1); sort(r+1,r+N+1);
    for(int i = 2*N, j = N; i > 0; i--) r[i] = (i == r[j]) ? j-- : j; 
    for(int i = 0; i <= (N<<2); i++) lazy[i] = 1;
    for(int i = 1; i <= N; i++){
        solv(r[seg[i].first],r[seg[i].second]);
    }
    int ans[M]; init(ans);
    sum(1,0,N,ans,0,N);
    out << ans[K] << endl;
}
