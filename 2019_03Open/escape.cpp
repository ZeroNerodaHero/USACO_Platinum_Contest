#include <bits/stdc++.h>

using namespace std;
const int MX = 30005;
typedef long long ll;
typedef pair<ll, int> PI;
typedef vector<int> VI;

#define P 1000000007
#define MOD(x) if(x>=P) x-=P

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N, K, a, b, row;
int lc[MX][6], dc[MX][6];
unordered_map<int, PI> m[2];
char f[12];
int const state = (0x543210);

void print(){
    for(auto i : m[b]){
        cout << hex << i.first << ": " << i.second.first << ' ' << i.second.second << endl;
    } cout << endl;
}
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

void insert(int st, ll cost){
    auto it = m[b].find(st);
    if(it == m[b].end()){
//cout << hex << st << " add new " << cost << endl;
        m[b][st] = PI(cost,C);
    } else{
//cout << hex << st << " old " << cost << endl;
        if(it->second.first >  cost){
            it->second.first = cost;
            it->second.second = C;
        } else if(it->second.first == cost){
            it->second.second += C; MOD(it->second.second);
        }
    }
}

void dfs(int i, ll cost, int flag){
//cout << i << " cost " << cost << " " << flag <<endl;
    if(i == K){
//prt(f, 2*K);
//prt(c, K);
        for(int j=K; j<2*K; ++j) {
            if (f[j] == j) t[j-K] = j;
            else t[j-K] = find(j);
        }
//prt(t, K);
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
//    cio("escape");
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
    //print2();
/*
    int mask = 1<<(4*K); mask--;
    m[0][state & mask] = PI(0,1);
*/
    m[0].reserve(4096);
    m[1].reserve(4096);
    m[0][state] = PI(0,1);
    a = 0, b = 1;
    for(row = 1; row <= N; row++){
        m[b].clear();
        for(auto s : m[a]){
            C = s.second.second;
            int tmp, sta = s.first;
            pt = (ll *)c;
            *pt = 0;
            for(int j = 0; j < K; j++){
                tmp = sta & 0xF;
                f[j] = tmp;
                sta >>= 4;
                c[tmp]++;
            }
//cout << "f "; prt(f, K);
//prt(c, K);
            dfs(0,s.second.first,false);
        } 
//cout << "row " << row << " " << m[b].size() << endl;
//cout << "row " << row << endl;
//print();
        a ^= 1, b^=1;
    }
    cout << m[a][0].second << endl;
}
