#include <bits/stdc++.h>
using namespace std;

int N, K;
int ans = 0;
#define MX 20005
const int P = 1e9+7;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) do {if(x>=P) x%=P;} while(0)

bool noc =false;
int s[MX], t[MX];

typedef pair<int, int> PI;

long long comb2(long long c){
    c*=(c-1);
    c/= 2;
    MOD2(c);
    return c;
}

long long comb3(long long c){
    long long tmp;
    if(c%3 == 0){
        tmp = (c-1)*(c-2)/2;
        c /= 3;
    } else{
        tmp = (c-1)*(c-2)/6;
    }
    MOD2(tmp);
    c*= tmp;
    MOD2(c);
    return c;
}

int countpt(vector<PI>& a){
    int c = 0;
    for(auto i: a){
        c += i.second-i.first+1;
    }
    return c;
}

int countseg(vector<PI>& x)
{
    int c=countpt(x);
    int c1 = comb3(c);
    return c1;
}

void halve(vector<PI>& x, vector<PI>& x1, vector<PI>& x2, int b){
    int mask = b-1;    

    for (auto f:x) {
        if(f.second<b) {
            x1.push_back(f);
        } else if(f.first>=b) {
            x2.push_back(make_pair(f.first&mask,f.second&mask));
        } else {
            x1.push_back(make_pair(f.first, b-1));
            x2.push_back(make_pair(0, f.second&mask));
        }
    } 
}

void dfs(vector<PI>& a, vector<PI>& b, int c, int d){
    long long tmp;
    if(a.size() == 0) return;
    if(b.size() == 0){
        tmp = comb2(c) * countpt(a);
        MOD2(tmp);
        ans += tmp;
        MOD(ans);
        return;
    }
    vector<PI> full; full.push_back(PI(0,d-1));
    if(b == full){
        c+=((d-1)&K);
        MOD(c);
        tmp = countpt(a); tmp*= comb2(c);
        MOD2(tmp);
        ans += tmp;
        MOD(ans);
        return;
    }
    d >>= 1;

    vector<PI> x0[2],x1[2];
    halve(a,x0[0],x0[1],d);
    halve(b,x1[0],x1[1],d);
     
    if(K & d){
        for(int i = 0; i < 2; i++){
            tmp = c+countpt(x1[i]);
            MOD(tmp);
            dfs(x0[i],x1[i^1],tmp,d);
        }
    } else{
        for(int i = 0; i < 2; i++){
            dfs(x0[i],x1[i],c,d);
        }
    }
}

void countxor(vector<PI>& x, int b)
{
    int c1, c2; 
    vector<PI> x1,x2;

    halve(x,x1,x2,b);

    c1 = countpt(x1);
    c2 = countpt(x2);
    if(c1>2){
        ans+= comb3(c1);
        MOD(ans);
    }
    if(c2>2){
        ans+= comb3(c2);
        MOD(ans);
    }
    
    dfs(x1,x2,0,b);
    dfs(x2,x1,0,b);
}

void getcnt(vector<PI>& x, int b)
{
    int c = 0;

    if(noc || x[0].first >= b ||
        x[x.size()-1].second<b) { 
        c = countseg(x); 
        ans += c;
        MOD(ans);
    } else {
        countxor(x,b);
    }
}

int main()
{
    vector<PI> x;
    int mask, rmask, BBB, half, dp0;

    cin >> N >> K;
    for (int i = 0; i< N; ++i) {
        cin >> s[i] >> t[i];

    }

    int b = ++K;
    if(b&(b-1)) {
        while(b&(b-1)) b = b&(b-1);
        b <<=1;
    } else {
        noc = true;
    }


    mask = b-1;
    rmask = ~mask;
    int u, v;
    while(b^(1<<BBB)) BBB++;

    half = b>>1;
    K -= half;
    long long tmp = b*comb2(K)+2*comb3(half); MOD2(tmp);
    dp0 = tmp;

    for (int i = 0; i< N; ) {
        u = s[i]&rmask;
        v = u+b;
        x.clear();

        if ((s[i] == u) && (t[i]>=(v-1))) {
            x.push_back(make_pair(0, mask));

            long long cnt = t[i]-s[i]+1;
            cnt >>= BBB;
            if((t[i]&mask) == mask) {
                i++;
            } else {
                s[i] = t[i]&rmask;
            }

            tmp = cnt * dp0; MOD2(tmp);
            ans += tmp; MOD(ans);

            continue;
        }

        for (; i<N; ++i) {
            if(s[i]>=v) {
                break;
            } else if(t[i] >=v) {
                x.push_back(make_pair(s[i]&mask, mask));
                s[i] = v;
                break;
            } else {
                x.push_back(make_pair(s[i]&mask, t[i]&mask));
            }
        } 
        getcnt(x,half);
    }

    cout << ans << endl;
}
