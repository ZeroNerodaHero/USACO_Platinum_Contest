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
vector<PI> g[MX];
int t[MX];
map<int,set<int> > m[MX];
set<int> ans, best[MX];
int p[MX], c[MX], f[MX], l[MX],l1[MX];

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
            e[j] = e[i];
            g[u].push_back(PI(v,j));
            g[v].push_back(PI(u,j));
            j++;
        }
    }   
}

void dfs(int x, int y){
    p[x] = y;
    for(auto i: g[x]){
        if(i.first != y){
            t[x]++;
            l[i.second] = i.first;
            l1[i.first] = i.second;
            m[x][c[i.first]].insert(i.second);
            dfs(i.first, x);
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
    dfs(1,0);
    for(int i = 1; i <=N; i++){
        if(t[i] == 0) continue;
        for(auto j : m[i]){
            best[i].insert(*j.second.begin());
        }
        auto j = best[i].begin();
        if(c[i] == c[l[*j]]) j++;
        if(j != best[i].end()){
            f[i] = *j;
            ans.insert(*j);
        } else f[i]= -1;
    }


    while(Q--){
        int a,b,b1;
        cin >> a >> b;
        b1 = c[a];
        c[a] = b;

        if(p[a]){
            int i = p[a];
            int j = l1[a];

            best[i].erase(*m[i][b1].begin());
            m[i][b1].erase(j);
            if(m[i][b1].size() > 0) best[i].insert(*m[i][b1].begin());
            else m[i].erase(b1);
    
            if(m[i][b].size() > 0){
                best[i].erase(*m[i][b].begin());
            }
            m[i][b].insert(j);
            best[i].insert(*m[i][b].begin());
            
            if(f[i]>=0) ans.erase(f[i]);
            auto k = best[i].begin();
            if(c[i] == c[l[*k]]) k++;
            if(k != best[i].end()) {
                f[i] = *k;
                ans.insert(*k);
            } else f[i] = -1;
        }

        if(t[a]){
            if(f[a]>=0) ans.erase(f[a]);
            auto j = best[a].begin();
            if(c[a] == c[l[*j]]) j++;
            if(j != best[a].end()) {
                f[a] = *j;
                ans.insert(*j);
            } else f[a] = -1;

        }
        cout << e[*ans.begin()].first << endl;
    }
}
