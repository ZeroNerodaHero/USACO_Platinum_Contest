#include <bits/stdc++.h>

using namespace std;
const int MX = 200005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N, M, K, Q;
pair<int, PI> e[MX];
int c[MX], f[MX], l[MX], ans[MX];

// record query on each node
// last query, last color, prev/next query in this node
struct node {
    int l, c, p, n;
};
vector<node> q[MX];

int find(int x){
    if(f[x] == 0){
        return x;
    }
    f[x] = find(f[x]);
    return f[x];
}

void Krusal(){
    for(int i = 0, j = 0; j < N-1; i++){
        int u = e[i].second.first, v = e[i].second.second;
        int pu = find(u), pv = find(v);
        if(pu != pv){
            f[pu] = pv;
            e[j++] = e[i];
        }
    }
}

void skip(int x, int v){
    int p = q[x][v].p, n = q[x][v].n, t = find(q[x][v].l);

    // try to skip query v
    if(q[x][n].l <= t) {
        q[x][p].n = n;
        q[x][n].p = p;
        if(q[x][p].c == q[x][n].c) { //skip same color
             q[x][p].n = q[x][n].n;
             q[x][q[x][p].n].p = p;
        }
    }
}

int main(){
    cio("grass");
    cin >> N >> M >> K >> Q;
    for(int i = 0; i < M; i++){
        cin >> e[i].second.first >> e[i].second.second >> e[i].first;
    }
    for(int i = 1; i <= N; i++){
        cin >> c[i];
    }
    sort(e,e+M);
    Krusal();

    for(int i = 1, a, b; i <= Q; i++) {
        cin >> a >> b;
        int s = q[a].size();
        q[a].push_back((node){l[a], c[a], s-1, s+1});
        c[a] = b; l[a] = i; f[i] = 0;
    }

    for(int i = 1; i <= N; i++) {
        int s = q[i].size();
        q[i].push_back((node){l[i], c[i], s-1, s+1});
        q[i].push_back((node){Q+1, 0, 0, 0});
    }
    f[Q+1] = 0;
    int tt = 0; //early exit
    for(int i = 0; tt<Q; i++) {
        int u = e[i].second.first, v = e[i].second.second;
        for(int j = find(1), a=0, b=0; j <= Q; j = find(j)) {
            for(int n = q[u][a].n; q[u][n].l <= j; n = q[u][n].n) a = n;
            for(int n = q[v][b].n; q[v][n].l <= j; n = q[v][n].n) b = n;

            if(q[u][a].c != q[v][b].c){
                ans[j] = e[i].first;
                f[j] = j+1;
                tt++;
            } else {
                j = min(q[u][q[u][a].n].l, q[v][q[v][b].n].l);
            }
            skip(u,a);
            skip(v,b);
        }
    }

    for(int i = 1; i <= Q; i++) cout << ans[i] << endl;
}
