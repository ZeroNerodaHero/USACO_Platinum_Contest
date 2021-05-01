#include <bits/stdc++.h>
using namespace std;

const int MX=5e5+100;
typedef vector<int> VI;

VI g[MX];
int sz[MX], fa[MX], dep[MX], son[MX], top[MX];

void dfs(int u,int father)
{
    sz[u]=1;
    dep[u]=dep[father]+1;
    fa[u]=father;
    for(auto v: g[u]) {
        if(v==father) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}

void dfs2(int u,int topx)
{
    top[u]=topx;
    if(son[u]==0) return;
    dfs2(son[u],topx);
    for(auto v: g[u]) {
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}

// online algorithm to find LCA of u,v
// faster than parent pointer
int lca(int u,int v)
{
    while(top[u]!=top[v]) {
        if(dep[top[u]] < dep[top[v]]){
            swap(u,v);
        }
        u=fa[top[u]];
    }

    return dep[u]<dep[v]?u:v;
}

int main(void)
{
    int N, M, root;

    cin.tie(0);std::ios::sync_with_stdio(false);
    cin>>N>>M>>root;

    for(int i=1;i<N;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(root,0);
    dfs2(root,root);
  
    while(M--) {
        int u,v;
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }

    return 0;
}
