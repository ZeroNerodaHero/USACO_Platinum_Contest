#include <bits/stdc++.h>
using namespace std;

#define P 1000000007
#define SIZE 100005
#define MOD(x, y) if(x>=y) x-=y
#define MODS(x, y) if(x<0) x+=y
#define MOD2(x, y) if(x>=y) x%=y
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

ifstream in("circus.in");
ofstream out("circus.out");

template<const int mod=P, const int iv = 1>
class mint{
    public:
        mint(){ v = iv;}
        mint(int _v) {v = _v; MOD2(v,mod);}
        mint(ll _v) {MOD2(_v,mod); v = _v;}

        friend mint operator+(mint a, mint b){
            a += b;
            return a;
        }
        mint operator+=(mint b){
            v += b.v; MOD(v,mod);
            return *this; 
        }
        friend mint operator-(mint a, mint b){
            a-=b;
            return a;
        }
        mint operator-=(mint b){
            v -= b.v; MODS(v,mod);
            return *this;
        }
        friend mint operator*(mint a, mint b){
            a *= b;
            return a;
        }
        friend mint operator*(mint a, int b){
            a.v = (a.v * ll(b))%mod;
            return a;
        }
        mint operator*=(mint b){
            v = (ll(b.v) * v)%mod;
            return *this; 
        }
        friend mint operator~(mint a){
            return a.inv(a.v);
        }
        operator int const(){return v;}
        mint operator ==(mint b){ return v == b.v;}
        friend ostream& operator <<(ostream& os, mint& a){
            os << a.v;
            return os;
        }

    private:
        int v;
        void exgcd(int a, int b, int& x, int& y){
            if(b == 0){
                x = 1;
                y = 0;
            } else{
                exgcd(b,a%b,y,x);
                y -= (a/b)*x;
            }
        }

        int inv(int a){
            int x,y;
            exgcd(mod,a,y,x); MODS(x,mod);
            return x;
        }
};
typedef mint<> mi;

struct chain{
    int a,b,l;
    void assign(int _a, int _b, int _l){ a=_a,b=_b,l=_l;}
    bool operator < (const chain& o) const{
        return l < o.l;
    }
};

int N, m, p[SIZE];
vector<int> g[SIZE];
chain c[SIZE];  //chains
unordered_map<int,PI> cc; //connected components
mi ans[SIZE], fac[SIZE],ifac[SIZE];

void init(){
    for(int i = 2; i <= N; i++) fac[i] = fac[i-1] * i;
    ifac[N] = ~fac[N]; for(int i =N; i > 2; i--) ifac[i-1] = ifac[i] * i;
}

void dfs(int b, int y, int l, int a){
    if(g[b].size() != 2){
        cc[b] = PI(g[b].size(),0);
        if(a != 0){
            c[m++].assign(a,b,l);
        }
        l = 1; a = b;
    }
    for(auto i: g[b]){
        if(i != y){
            dfs(i,b,l+1,a);
        }
    }
}

int find(int x){
    if(p[x] == 0) return x;
    p[x] = find(p[x]);
    return p[x];
}

int main(){
    in >> N;
    for(int i = 1; i < N; i++){
        int a,b;
        in >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    init();
    int root = 1;
    while(g[root].size() == 2) root++;
    dfs(root,0,0,0);
    sort(c,c+m);
    ans[0] = fac[N];
    for(int k = 1, i = 0; k < N; k++){ //k free nodes
        while(i < m && k > c[i].l){  //merge 2 cc
            int a = find(c[i].a), b = find(c[i].b);
            cc[a].first += cc[b].first - 2;
            cc[a].second += cc[b].second + c[i].l-1;
            p[b] = a;
            cc.erase(b);
            i++;    
        }
        if(i == m) break;
        ans[k] = fac[N-k];
        for(auto& j: cc){ //compute size of cyclic groups
            ans[k] *= ifac[(k-1) * (j.second.first-1) + j.second.second];
        }
    }
    for(int i = N-1; i >= 0; i--) out << ans[i] << endl;
}
