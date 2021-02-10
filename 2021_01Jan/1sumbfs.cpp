#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  50002;
const unsigned int MX1 = 100002;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P

int K, ans, n[MX], sum[MX], prd[MX];
VI g[MX1];
long long dp[2][MX];

#define MM (1<<16)
#define MASK (MM-1)
int d[MM][32];
int x=1;
queue<PI> q;
unordered_set<string> m;

static PI A;
void dfs(int k, string ha)
{
    if(k==K) {
        if(m.find(ha) == m.end()){
             m.insert(ha);
             ans+=A.second;
             q.push(PI(x,A.second+1));
             int b=x+1; //if(b== MM) b = 0;
             for(int j=0; j<K; ++j) {
                d[b][j] = d[x][j];

             }
             x=b;
        }
        return;
    }

    VI *f = g+sum[k];
    int i = A.first;
    for(auto a:f[d[i][k]]) {
        d[x][k] = a;
        string ha1 = ha+to_string(a)+",";
        dfs(k+1, ha1);
    }
}

int main()
{
    cin >> K;
    int u=0, v=1, z;
    for(int i = 0; i<K; ++i) {
        cin >> n[i]>>z;
        VI* f = g+u;
        sum[i] = u, prd[i]=v;
        for (int j =0; j<z; ++j) {
            int a, b;
            cin >> a>>b;a--, b--;
            f[a].push_back(b);
            if(b!=a) f[b].push_back(a);
        }
        u+=n[i], v*=n[i];
    }
    //print();

    q.push(PI(0,1));
    string a;
    for(int i=0; i<K;++i) a+="0,";
    m.insert(a);
    while(!q.empty()) {
        A =q.front(); q.pop();
        dfs(0, "");
    }

    cout << ans << endl;
}
