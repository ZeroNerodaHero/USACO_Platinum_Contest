#include <bits/stdc++.h>

using namespace std;
const int MX = 30005;
typedef long long ll;
typedef pair<ll, int> PI;
typedef vector<int> VI;

#define P 1000000007
#define MOD(x) if(x>=P) x-=P

int N, K;
unordered_map<int, int> m;
char f[16], b[16], id[16];
int tot;

void print(char a[], int sz)
{
    for(int i = 0; i <sz; i++) cout << int(a[i]) << ' ';cout << endl;
}

char find(char x){
    if(x == f[x]) return x;
    return find(f[x]);
}

int encode()
{
    for(int i = 0; i < K; i++){
        f[i] = b[i];
    }
    for(int i = 0; i < K; i++){
        f[i] =find(f[i]);
    }
    //cout << "f: "; print(f,K);
    memset(id, -1, sizeof(id));
    for(int i = 0; i < K; i++){
        if(id[f[i]] == -1) id[f[i]] = i;
    }
    for(int i = 0; i < K; i++){
        f[i] =id[f[i]];
    }
    //cout << "f: "; print(f,K);
    int tmp = 0;
    for(int i = K-1; i >= 0; i--){
        tmp <<= 4;
        tmp |= f[i];
    }
    return tmp;
}

void insert() {
    int st = encode();
    auto it = m.find(st);
    if(it == m.end()){
        cout << "f: "; print(f,K);
        tot++;
    }
    m[st]++;
}

void dfs(int i) {
    if(i == K){
        //cout << "b: "; print(b,K);
        insert();
        return;
    }


#if 0
    for (int j=i; j>=0; --j) {
       b[i] = j;
       dfs(i+1);
    }
#else
	b[i] = i;
    char cc = i;
    for(int j=i; j>=0; j--)
    {
        cc = min(cc, b[j]);
        if(b[j]==cc)
        {
			b[i] = cc;
            dfs(i+1);
        }
    }
#endif
}

int main(){
    K=6;
    dfs(0);
    cout << tot << ":" << m.size() << endl;
}
