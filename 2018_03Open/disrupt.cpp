#include <bits/stdc++.h>

using namespace std;
const int MX = 50005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}
int N, M;
vector<PI> t[MX];
set<ll> e[MX];
int ans[MX];

int dfs(int c, int p, set<ll> &s){
    for(auto i : t[c]){
        if(i.first != p){
            ans[i.second] = dfs(i.first,c,e[c]);
        }
    } 
    int r = -1;
    if(e[c].size() > 0){
        r = (*e[c].begin())>>32;
    }
    set<ll> *a, *b;
    bool ch = false;
    if(s.size() < e[c].size()){
        a = &s;
        b = &e[c];
        ch = true;
    } else{
        a = &e[c];
        b = &s;
    }

    for(auto i : *a){
        auto it = b->find(i);
        if(it != b->end()){
            b->erase(it);
        } else {
            b->insert(i);
        }
    }
    if(ch) s.swap(e[c]);
    return r;
}

int main(){
    cio("disrupt");
    cin >> N >> M;
    for(int i = 1 ; i < N; i++){
        int a, b;
        cin >> a >> b;
        t[a].push_back(PI(b,i));
        t[b].push_back(PI(a,i));
    }
    for(int i = 1; i <= M; i++){
        ll a,b,w;
        cin >> a >> b >> w;
        w = ((w<<32) | i);
        e[a].insert(w);
        e[b].insert(w);
    }
    set<ll> s;
    dfs(1,0,s);
    for(int i = 1; i < N; i++){
        cout << ans[i] << endl;
    }
}
