#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  102;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P
#define f first
#define s second

int N, T, K;
char b[MX];
VI g[MX];
PI loop[2];
int din[MX], dout[MX], perm[MX], iv[MX];
ll ans, dp[MX];

int checkloop(int s, int e) { 
    for(int i=s; i>e; i--) dp[i]=0;
    dp[e] = 1;
    for (int i = e; i <= s; i++) {
        dp[i] *= iv[din[i]]; MOD2(dp[i]);
        for (auto j:g[i]) {
            dp[j] += dp[i]; MOD(dp[j]);
        }
    }
    return dp[s];
}

int checkloop2() {
    ll x = checkloop(loop[0].f, loop[1].s);
    x *= checkloop(loop[1].f, loop[0].s); MOD2(x);
    return x;
}

int inverse(ll b){
    ll z= 1;
    int y=P-2;
    while(y){
        if(y & 1) {z *= b;MOD2(z);}
        b = b*b; MOD2(b);
        y >>= 1;
    }
    return z;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    perm[0]=perm[1]=iv[0]=iv[1]=1;
    for(int i=2; i<MX; i++) {
        ll lt=i; lt*=perm[i-1]; MOD2(lt); perm[i]=lt; iv[i]=inverse(i);
    }

    for (int tt=1; tt<=T; tt++) {
        cin >> N >> K;
        cin >> (b+1);
        for (int i=1; i<=N; ++i) g[i].clear(), din[i]=dout[i]=0;

        int k=0;
        for(int i = 1; i <= N; ++i) {
            if(b[i] == 'S') {
               din[i]++;
            } else if(b[i]=='R'){
               dout[i]++;
            }
        }

        for (int i=1; i<=N; ++i) {
            cin >> (b+1);
            for(int j = 1; j<=N; j++) {
                if(b[j] == '1') {
                    dout[i]++, din[j]++;
                    if(i>j) loop[k++]=PI(i,j);
                    else g[i].push_back(j);
                }
            }
        }

        ans = 1;
        for (int i=1; i<=N; ++i) {
            //ans*=perm[dout[i]]; MOD2(ans);
            ans*=perm[din[i]]; MOD2(ans);
        }
        if(K>0) {
            ll x = checkloop(loop[0].f, loop[0].s);
            if(K==2) {
                ll y = checkloop(loop[1].f, loop[1].s);
                x -= (x-1)*y; x%=P;
                if(loop[0].f >= loop[1].s) {
                    x+=checkloop2();
                }
            }
            ans = ((1LL-x)*ans)%P; MODS(ans);
        }
        cout << ans << endl;
    }
    return 0;
}
