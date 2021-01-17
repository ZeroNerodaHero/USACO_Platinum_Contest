#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const unsigned int MX = 50005;
const unsigned int MY = 20;
const int P = 1e9+7;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
#define IV2 ((P-1)/2)

int N, K, Q;
int a[MX];
int v[MX][MY], iv[MX][MY];
int m[MY][MY], im[MY][MY];

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int main()
{
    setIO("nondec");
    cin >> N >> K;
    for(int i = 1; i <= N; i++){
        cin >> a[i]; a[i]--;
    }
    for(int i = 0; i < K; i++){
        m[i][i] = im[i][i] = 1;
    }
    iv[0][0] = 1;
    for(int i = 1, x = a[i]; i <= N; x=a[++i]){
        for(int j = 0; j < K; j++){
            for(int k = x; k >= 0; k--){
                m[j][x] += m[j][k]; MOD(m[j][x]);
            }
        }
        for(int j = 0; j < K; j++){
            for(int k = 0; k < K; k++){
                v[i][j] += m[j][k]; MOD(v[i][j]);
            }
        }
        for(int j = 0; j <= x; j++){
            for(int k = 0; k < K; k++){
                im[j][k] += ((ll)im[x][k] * IV2)%P; MOD(im[j][k]);
            }   
        }
        for(int j = 0; j < K; j++){
            iv[i][j] = im[0][j];
        }
    }
    cin >> Q;
    for(int i = 0; i < Q; i++){
        int l, r;
        int ans = 0;
        cin >> l >> r; l--;
        for(int j = 0; j < K; j++){
            ans +=  ((ll)iv[l][j] * v[r][j])%P; MOD(ans);
        }
        cout << ans << endl;
    }
}
