#include "grader.h"
#include <bits/stdc++.h>

using namespace std;
const int MX = 100005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

VI g[MX];
int f[MX], d[MX], s[MX];
int x[MX],y[MX];

void addRoad(int a, int b){
    g[a].push_back(b);
    g[b].push_back(a);
}

int dfs(int u, int p){
    s[u] = 1;
    d[u] = d[p]+1;

    for(auto i: g[u]){
        if(i == p) continue;
        f[i] = u;
        s[u] += dfs(i,u);
    }
    return s[u];
}

void dfs2(int u, int px, int py){
    x[u] = px, y[u] = py;
    setFarmLocation(u,px,py++);
    px += s[u]-1;
    
    for(auto i: g[u]){
        if(i == f[u]) continue;
        dfs2(i, px-s[i]+1, py);
        px -= s[i];
        py += s[i];
    }
}

void buildFarms(){
    dfs(0,0);
    dfs2(0,1,1);
}

int lca(int a, int b, int& C){
    while(d[a] > d[b]){
        a = f[a];
    }

    while(a != b){
        C = b;
        a = f[a];
        b = f[b];
    }
    return b;
}

void notifyFJ(int a, int b){
    if(d[a] < d[b]) return notifyFJ(b,a);
    int C = b, c = lca(a,b, C);
    addBox(x[c],y[c],x[a],y[a]);
    if(c != b) addBox(x[C],y[C],x[b],y[b]);
}

#if 0
int N,Q;
int getN() {return N;}
int getQ() {return Q;}
void setFarmLocation(int ID, int X, int Y){
    cout << ID << ' ' << X << ' ' << Y << endl;
}
void addBox(int X1, int Y1, int X2, int Y2){
    cout << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << endl;
}

int main(){
    cin >> N >> Q;

    for(int i = 1; i < N; i++){
        int a,b;
        cin >> a >> b;
        addRoad(a,b);
    }
    buildFarms();
    for(int i = 0; i < Q; i++){
        int a,b;
        cin >> a >> b;
        notifyFJ(a,b);
    }
}
#endif
