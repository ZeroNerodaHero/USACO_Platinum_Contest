#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const unsigned int MX = 200005;
const unsigned int MY = 20;
const int P = 1e9+7;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
#define IV2 ((P-1)/2)

int N, t;
int a[MX],q[MX];
int num[MX],den[MX];
int id[MX], s[MX];

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

ll ccw(int x, int y, int z){
    return (ll)(a[x] - a[z])*(y-z) - (ll)(a[y]-a[z])*(x-z);
}

int gcd(int x, int y){
    if(x == 0) return y;
    return gcd(y%x,x);
}

int main()
{
    setIO("falling");
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
        id[i] = i;
    }
    for(int i = 1; i <= N; i++){
        cin >> q[i];
    }

    sort(id+1,id+N+1,[&](int u, int v){return a[u] < a[v];});

    for(int i = N, x = id[i]; i > 0; i--,x = id[i]){
        while(t &&(s[t-1] < x)) t--;
        while(t > 1 && ccw(x,s[t-1],s[t-2]) >= 0) t--;

        s[t++] = x;
        if((a[q[x]] < a[x]) && (q[x] < s[0])){
            int l = 0, r = t-1;
            while(l < r){
                int m = (l+r)/2;
                int m1 = m+1;
                if(s[m1] < q[x]){
                    r = m;
                    continue;
                }
                ll c = ccw(s[m],s[m1],q[x]);
                if(c < 0) r = m;
                else if(c == 0) l = r = m;
                else l = m1; 
            }                  
            num[x] = a[s[l]] - a[q[x]];
            den[x] = s[l] - q[x];           
        }
    }
    t= 0;
    for(int i = 1,x=id[i]; i <= N; i++,x=id[i]){
        while(t && (s[t-1] > x)) t--;
        while((t > 1) && (ccw(x,s[t-1],s[t-2]) >= 0)) t--;
        s[t++] = x;

        if((a[q[x]] > a[x]) && (q[x] > s[0])){
            int l = 0, r = t-1;
            while(l < r){
                int m = (l+r)/2;
                int m1 = m+1;
                if(s[m1] > q[x]){
                    r = m; continue;
                }           
                ll c = ccw(s[m],s[m1],q[x]);
                if(c < 0) r = m;
                else if(c== 0) l= r = m;
                else l = m1;
            }
            num[x] = a[q[x]] - a[s[l]];
            den[x] = q[x]- s[l];           
        } 
    }
    for(int i = 1; i <= N; i++){
        if(num[i] == 0) cout << -1 << endl;       
        else{
            int g = gcd(num[i],den[i]);
            cout << (num[i]/g) << "/" << (den[i]/g) << endl;
        }
    }
}
