#include <bits/stdc++.h>

using namespace std;
const int MX = 30005;
typedef long long ll;
typedef pair<ll, int> PI;
typedef vector<int> VI;

#define P 1000000007
#define MOD(x) if(x>=P) x-=P

#define OO(x) x
//#define OO(x)

const unsigned int MXH = (1<<20);
const unsigned int MK = MXH-1;
const unsigned int MV = ~MK;
#define hasher(x) ((x>>4)&MK)
const ll INF=((1ll)<<60);

struct node{
    int st, cnt, v; ll cost;
    map<int, int> b;
};
struct htable{
    node h[MXH];
    int a[MX];

    int v, s;

    htable() {v=1;s=0;}
    void clear(){
        s = 0;
        v++;
    }

    node * find(int st){
        int hash = hasher(st);
        if(h[hash].v != v){
            h[hash].v = v;
            h[hash].st = st;
            h[hash].cost = INF;
            a[s++] = hash;
        }
        return &h[hash];
    }

    void insert(int st, int nst){
        int hash = hasher(st);
        if(h[hash].v != v){
            h[hash].v = v;
            h[hash].st = st;
            h[hash].cost = hash;
            a[s++] = hash;
            h[hash].b.clear();
        }
        h[hash].b[nst]++;
    }

    node *get(int i) {
        return &h[a[i]];
    }

    void print(){
        cout << " size " << s << endl;
        sort(a, a+s);
        for(int i=0; i<s; ++i){
            auto it = get(i);
            cout << hex << it->st << ": ";
            for (auto k:it->b) cout << "("<<k.first<< ' '<<k.second<<") "; cout << endl;
        } cout << dec<< endl;
    }
};


void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N, K, a, b, row;
int lc[MX][8], dc[MX][8];
htable m[3];
char f[16];
int const state = (0x543210);

#if 1

void print2(){
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < K; j++){
            cout << lc[i][j] << ' ';
        }   cout << endl;
        for(int j = 0; j < K; j++){
            cout << dc[i][j] << ' ';
        }   cout << endl;
    } cout << endl;
}
void prt(char a[], int sz)
{
    for(int i = 0; i <sz; i++) cout << int(a[i]) << ' ';cout << endl;
}
#endif

char find(char x){
    if(x == f[x]) return x;
    return find(f[x]);
}

int C;
char c[8], t[8], id[16];
ll* pt;
int encode()
{
    pt = (ll*) id;
    *pt++ = -1;
    *pt = -1;
    for(int i = 0; i < K; i++){
        if(id[t[i]] == -1) id[t[i]] = i;
    }
    for(int i = 0; i < K; i++){
        t[i] =id[t[i]];
    }
    int tmp = 0;
    for(int i = K-1; i >= 0; i--){
        tmp <<= 4;
        tmp |= t[i];
    }
    return tmp;
}

int oldst;
void insert(int st, ll cost){
    node * it = m[b].find(st);
    if(it->cost > cost){
        it->cost = cost;
        it->cnt = C;
    } else if(it->cost == cost){
        it->cnt += C; MOD(it->cnt);
    }
    m[2].insert(oldst,st);
}

void dfs(int i, ll cost, int flag){
    if(i == K){
        for(int j=K; j<2*K; ++j) {
            if (f[j] == j) t[j-K] = j;
            else t[j-K] = find(j);
        }
        int st = encode();
        insert(st,cost);
        return;
    }

    char* s = f+K;
    if(!flag) {
        if(c[f[i]] > 1){
            c[f[i]]--;
            s[i] = i+K;
            dfs(i+1,cost,false);
            if(i < K-1) dfs(i+1,cost+lc[row][i],true);
            c[f[i]]++;
        }
        s[i] = f[i];
        dfs(i+1,cost+dc[row][i],false);
        if(i < K-1) dfs(i+1,cost+lc[row][i]+dc[row][i],true);
    }   else{
        s[i] = s[i-1];
        if(c[f[i]] > 1){
            c[f[i]]--;
            dfs(i+1,cost,false);
            if(i < K-1) dfs(i+1,cost+lc[row][i],true);
            c[f[i]]++;
        }

        char u = find(s[i]), v = find(f[i]);
        if(u == v) return;
        int tmp = f[u];
        f[u] = v;

        dfs(i+1,cost+dc[row][i],false);
        if(i < K-1) dfs(i+1,cost+lc[row][i]+dc[row][i],true);

        f[u] = tmp;

    }
}

int main(){
    //cio("escape");
    cin >> N >> K;
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < K-1; j++){
            cin >> lc[i][j];
        }
    }
    for(int j = 0; j < K; j++){
        for(int i = 2; i <= N; i++){
            cin >> dc[i][j];
        }
    }
    node * it = m[0].find(state);
    it->cost = 0; it->cnt=1;
    a = 0, b = 1;
    for(row = 1; row <= N; row++){
        m[b].clear();
        m[2].clear();
        for(int i = 0; i< m[a].s; ++i) {
            auto it = m[a].get(i);
            C = it->cnt;
            oldst = it->st;
            int tmp, sta = it->st;
            *(ll *)c=0;
            for(int j = 0; j < K; j++){
                tmp = sta & 0xF;
                f[j] = tmp;
                sta >>= 4;
                c[tmp]++;
            }
            dfs(0,it->cost,false);
        }
        //cout << row << " row "; m[2].print();
        a ^= 1, b^=1;
    }
    it = m[a].find(0);
    cout << it->cnt << endl;
    OO(m[2].print();)
}

