#include "grader.h"
#include <bits/stdc++.h>

using namespace std;
const int MX = 100005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

VI g[MX];
int f[40][MX], d[MX], s[MX];
int x[MX],y[MX];

void addRoad(int a, int b){
    g[a].push_back(b);
    g[b].push_back(a);
}

int dfs(int u, int p){
    s[u] = 1;
    d[u] = d[p]+1;
    f[d[u]][u] = p;

    for(int j = 0; j< g[u].size(); j++) {
        int i = g[u][j];
        if(i == p){
            swap(g[u][j],g[u].back());
            g[u].pop_back();
            j--;
            continue;
        }
        s[u] += dfs(i,u);
    }
    return s[u];
}

void dfs2(int u, int px, int py){
    x[u] = px, y[u] = py;
    setFarmLocation(u,px,py++);
    px += s[u]-1;
    
    for(auto i: g[u]){
        //if(i == f[d[u]][u]) continue;
        dfs2(i, px-s[i]+1, py);
        px -= s[i];
        py += s[i];
    }
}

void buildFarms(){
    d[0] = -1;
    dfs(0,0);
    dfs2(0,1,1);
    for(int i = 1; i < s[0]; i++){
        f[d[i]+1][i] = i;
        for(int j = d[i]-1; j > 0; j--){
            int u = f[j+1][i];
            f[j][i] = f[d[u]][u];
        }
    }
}

int lca(int a, int b){
    if(a == b) return d[a]+1;
    int l= 0, r = min(d[a],d[b])+1;
    while(l < r){
        int m = (l + r + 1)/2;
        if(f[m][a] == f[m][b]){
            l = m;
        } else{
            r = m-1;
        }
    }
    return l;
}

void notifyFJ(int a, int b){
    if(d[a] < d[b]) return notifyFJ(b,a);
    int l= lca(a,b);
    int c = f[l][b]; 
    addBox(x[c],y[c],x[a],y[a]);
    if(c != b){
        int C = f[l+1][b];
        addBox(x[C],y[C],x[b],y[b]);
    }
}

#if defined(DEMO)
int N,Q;
int getN() {return N;}
int getQ() {return Q;}
char g1[100][100],g2[100][100];
void setup(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            g2[i][j] = g1[i][j];
        }
    }
}
void print(){
    for(int i = 1; i <= N; i++){
        cout << (g2[i]+1) << endl;
    }   
    cout << endl;
}
void init(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            g1[i][j] = ' ';
        }
    }
}

char conv(int i){
    return (i < 10) ? ('0'+i) : ('A'+i-10);
}

void setFarmLocation(int ID, int X, int Y){
    cout << ID << ' ' << X << ' ' << Y << endl;
    g1[X][Y] = conv(ID);
}
void addBox(int X1, int Y1, int X2, int Y2){
    cout << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << endl;
    int ax = min(X1,X2), bx = max(X1,X2);
    int ay = min(Y1,Y2), by = max(Y1,Y2);
    for(int i = ax; i <= bx; i++){
        g2[i][ay]= g2[i][by] = '*';
    }
    for(int i = ay; i <= by; i++){
        g2[ax][i]= g2[bx][i] = '*';
    }

    g2[X1][Y1] = '+';
    g2[X2][Y2] = '-';
}

int main(){
    cin >> N >> Q;

    for(int i = 1; i < N; i++){
        int a,b;
        cin >> a >> b;
        addRoad(a,b);
    }
    init();
    buildFarms();
    setup();
    print();
    for(int i = 0; i < Q; i++){
        int a,b;
        cin >> a >> b;
        setup();
        notifyFJ(a,b);
        print();
    }
}
#endif
