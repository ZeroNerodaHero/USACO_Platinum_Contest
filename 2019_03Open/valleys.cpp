#include <bits/stdc++.h>

using namespace std;
const int MX = 755;
const int MX1 = MX * MX;
const int INF = 1000005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N, M;
int v[MX][MX], id[MX][MX];
pair<int,PI> d[MX1];
int f[MX1], E[MX1], V[MX1], C[MX1];

int find(int x){
    if(f[x] == 0){
        return x;
    }
    f[x] = find(f[x]);
    return f[x];
}

void merge(int x, int p){
    x = find(x);
    if(p != x){
        f[x] = p;
        V[p] += V[x];
        E[p] += E[x];
        C[p] += C[x];
    }
}

int main(){
    cio("valleys");
    cin >> N;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> d[M].first; 
            d[M].second.first = i;
            d[M].second.second = j;
            id[i][j] = ++M;
            V[M] = 1;
        }       
    }
    sort(d,d+M); 
    ll ans = 0;
    for(int i = 0; i < M; i++){
        int x = d[i].second.first;
        int y = d[i].second.second;
        int c = id[x][y];
        v[x][y] = 1;
        if(v[x-1][y]) E[c]++, merge(id[x-1][y],c);
        if(v[x][y-1]) E[c]++, merge(id[x][y-1],c);
        if(v[x+1][y]) E[c]++, merge(id[x+1][y],c);
        if(v[x][y+1]) E[c]++, merge(id[x][y+1],c);
        
        if(v[x-1][y] && v[x][y-1] & v[x-1][y-1]) C[c]++;
        if(v[x+1][y] && v[x][y-1] & v[x+1][y-1]) C[c]++;
        if(v[x+1][y] && v[x][y+1] & v[x+1][y+1]) C[c]++;
        if(v[x-1][y] && v[x][y+1] & v[x-1][y+1]) C[c]++;

        if(E[c]-V[c]-C[c] == -1){
            ans += V[c];
        } 
    }
    cout << ans << endl;
}
