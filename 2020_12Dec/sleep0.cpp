#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = (1<<22);
const unsigned int MK = MX-1;
const unsigned int MV = ~MK;
#define MOD(x) do {if(x>=P) x-=P;} while(0)
#define MOD2(x) do {if(x>P) x%=P;} while(0)

#define hasher(x) ((x^((x&MV)>>11))&MK)

struct node{
    node * next;
    int st, v;
};
struct htable{
    node a[MX];
    node h[MX];

    int v, s;

    void clear(){
//cout << v << " hash table " << s << endl;
        s = 0;
        v++;
    }

    node * get(int st){
        int hash = hasher(st);
        if(h[hash].v != v){
            h[hash].next = NULL;
            h[hash].v = v;
        } else{
            for(node * it = h[hash].next; it != NULL; it = it->next){
                if(it->st == st){
                    return it;
                }
            }
        }
        node * n = &a[s++];
        n->st =st;
        n->v = 0;
        n->next = h[hash].next;
        h[hash].next = n;
        return n;
    }
};

int N, C, B;
int ans = 0;
const int P = 1e9+7;

int s[3000], t[3000], s1[3000];
htable dp[2];
const int mask = (1<<16)-1;

const int z = 1600;
long long  perm[z][z];
int comb[z][z];

void setperm()
{
    for (int i = 0; i <z; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                perm[i][j] = 1;
            else {
                perm[i][j] = perm[i-1][j] +  j*perm[i-1][j-1];
                MOD2(perm[i][j]);
            }
        }
    }

    for (int i = 0; i <z; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                comb[i][j] = 1;
            else{
                comb[i][j] = comb[i-1][j] +  comb[i-1][j-1];
                MOD(comb[i][j]);
            }
        }
    }

/*
    for (int i = 0; i< z; i++) {
        for (int j = 0; j <= z; j++) {
            cout << perm[i][j] << ' ';
        } cout << endl;
    } cout << endl << "comb" << endl;


    for (int i = 0; i< z; i++) {
        for (int j = 0; j <= z; j++) {
            cout << comb[i][j] << ' ';
        } cout << endl;
    } cout << endl;
*/
}


void print()
{
    cout << "\nN " << N << endl;
    for (int i = 0; i<= N; ++i) cout << s[i] << ' '; cout << endl;
    for (int i = 0; i<= N; ++i) cout << t[i] << ' '; cout << endl;
    for (int i = 0; i<= N; ++i) cout << s1[i] << ' '; cout << endl;
    cout <<endl;
}

void prep(void)
{
    int c = 0;
    int i=1, j=1;

    for(;j<=N&&t[j]<s[i]; ++j);
    //cout << j << endl;
    while(j<=N){
        s[c] = t[c] = 0;
        for (; i<=N&&s[i]<=t[j]; i++) {
            //cout << s[i] << ",";
            s[c]++;
        }

        if(i<=N) {
            for(;j<=N && t[j]<s[i];j++) {
                t[c]++;
            }
        } else {
            t[c] = N-j+1;
            j=N+1;
        }
        c++;

    }
    N=c;
    reverse(s, s+N);
    reverse(t, t+N);
}

int main()
{
    cin >> N; //cout << N << endl;
    for (int i = 1; i<= N; ++i) cin >> s[i];
    for (int i = 1; i<= N; ++i) cin >> t[i];
    //F = FastMod(P);
//    print();
    sort(s+1, s+N+1);
    sort(t+1, t+N+1);
//    print();
    prep();
    setperm();

    for(int i=N-1; i>=0; --i) {
        C += s[i];
        B += t[i];
        s1[i] = C;
    }

//    cout << B << " C " << C << endl;
//    print();

    int a = 0,b = 1;
    node * na = dp[0].get(0);
    na->v = 1;
    for(int i = 0; i < N; i++){
        dp[b].clear();
//cout << dp[a].v << " " << dp[b].v << " " << dp[a].s << endl;
        for(int j = 0; j < dp[a].s; j++){
            node& na = dp[a].a[j];
            int m = (na.st & mask);
            int o = (na.st >> 16);

            o += t[i];
            int n = min(s[i],m+o);
            int n1 = n - o;
            for(int k = max(0,n1); k <= min(n,m); k++){
                int m1 = m-k, o1 = ((o-n+k)<<16);
                if (m1>s1[i+1]) continue;
                int state = (o1|m1);
                node* nb = dp[b].get(state);
                long long ms = perm[s[i]][k] * comb[m][k]; MOD2(ms);
                long long os = perm[s[i]-k][n-k] * comb[o][n-k]; MOD2(os);
                nb->v += (os * ((ms * na.v)%P))%P;
                MOD(nb->v);
            }

            m += o;
            for(int k = 0; k < n; k++){
                int m1 = m-k;
                if (m1>s1[i+1]) continue;
                node* nb = dp[b].get(m1);
                long long ms = perm[s[i]][k] * comb[m][k]; MOD2(ms);
                nb->v += (ms * na.v)%P;
                MOD(nb->v);
            }
        }
        a ^= 1;
        b ^= 1;
    }

    ans = 0;
    for(int i = 0; i < dp[a].s; i++){
        node& n = dp[a].a[i];
//cout << (n.st&mask) << ' ' << (n.st>>16) << ' ' << n.v << endl;
        if((n.st&mask)==0){
            ans += n.v;
            if(ans >= P) ans -= P;
        }
    }

    cout << ans << endl;
}
