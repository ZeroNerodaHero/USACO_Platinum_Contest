#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <set>

using namespace std;

ifstream fin("snowcow.in");
ofstream fout("snowcow.out");
const int MX = 10e5+5;
int N,Q;
int t[MX],e[MX],s[MX], bit[2][MX];
set<int> co[MX];
vector<int> g[MX]; 
int p;

void add(int i, int x, int v){
    int *b = bit[i];
    while(x <= N){
        b[x] += v;
        x += x&(-x);
    }
}

int sum(int i, int x){
    int ret = 0;
    int *b = bit[i];
    while(x){
        ret += b[x];
        x -= x&(-x);    
    }
    return ret;
}

int query(int l, int r){
    return sum(1,r)-sum(1,l);
}

void dfs(int x){
    t[x] = ++p;
    for(auto i : g[x]){
        if(t[i] == 0) dfs(i);
    }
    e[t[x]] = p;
    s[t[x]] = p-t[x]+1;
}

void update(int x, int v){
    add(0,x,v);
    add(0,e[x]+1,-v);
    add(1,x,v*s[x]);
}

int main(){
    fin >> N >> Q;
    for(int i = 1; i < N; i++){
        int a, b;
        fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1);

    for(int i = 0; i < Q; i++){
        int a,x,c;
        fin >> a >> x;
        x = t[x];
        if(a == 1){
            fin >> c;
            auto it = co[c].upper_bound(x);
            if(it != co[c].begin() && e[*(prev(it))] >= e[x]) continue;
            while(it != co[c].end() && *it <= e[x]){
                update(*it,-1);
                co[c].erase(it++);
            }
            co[c].insert(x);
            update(x,1);
        } else{
            int ans = sum(0,x) * s[x] + query(x,e[x]);            
            fout << ans << endl;
        }
    }
}
