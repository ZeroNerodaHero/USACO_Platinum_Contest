#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  152;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P
#define f first
#define s second

const unsigned int MXH = (1<<16);

struct node{
    int v, b, val;
};
struct htable{
    int v, s;
    int  a[MXH];
    node h[MXH];

    htable() {v=1;s=0;}
    void clear(){
        s = 0;
        v++;
    }

    void add(int key, int val){
        if(h[key].v != v){
            h[key].v = v;
            h[key].val = val;
            a[s++] = key;
        } else {
            h[key].val += val;
			MOD(h[key].val);
		}
    }
	
    int size() {
        return s;
    }
};

int N, Q, T, K,a,b=1;
char ar[MX][MX], br[MX];
int c[MX][MX], id=1, c1[MX];
int p[MX];
//VI f[MX], g[MX], s, t;
//set<int> st[2];
//PI loop[2];
ll ans;
PI d[MX*MX];
VI v;
htable m[2][4];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=1; i<=N; ++i) {
        cin>> (ar[i]+1);
    }
    v.reserve(MX*MX);
    for(int i=1; i<=N; ++i) {
        v.clear(); for (int j=0; j<4; ++j) m[b][j].clear();
        for (int j = 1; j<=N; ++ j) {
            if(ar[i][j] == 'G') {
                if(ar[i][j-1]=='G') {
                    c[i][j] = c[i][j-1];
                } else {
                    c[i][j] = id;
                    d[id].f=j;
                    v.push_back(id);
                    id++;
                }
                d[c[i][j]].s=j;
            }
        }

        for(auto j:v) {
            int l=d[j].s-d[j].f+1;
            ans += (l*(l+1))/2; MOD2(ans);
            for (int k=0; k<l; ++k) {
                for (int x=d[j].f, y=x+k;y<=d[j].s; x++, y++) {
                    int z= (x<<8)|y;
					m[b][0].add(z,1);
                }
            }
        }

        int x, y,z, x1, y1, x2, y2, x3,y3;
        for (int j=0; j<4; ++j) {
            for (int u=0; u<m[a][j].size(); u++) {
				int key = m[a][j].a[u];
				node * pt = &m[a][j].h[key];
				int val = pt->val;
                x= (key>>8)&0xff;
                y = key&0xff;
                for(int w=x; w<=y;++w) {
                    if(c[i][w]<=0 || c[i][w] ==pt->b) continue;
                    pt->b=c[i][w];
                    x1 = d[pt->b].f;
                    y1 = d[pt->b].s;

                    if((j&1)&&(y1>y)) y1=y;
                    if((j&2) && (x1<x)) x1=x;

                    int l=y1-x1+1;
                    long long total = (l*(l+1))/2;
                    if(x1<x) {
                        l = x-x1;
                        total -= l*(l+1)/2;
                    }
                    if(y1>y) {
                        l = y1-y;
                        total -= l*(l+1)/2;
                    }
                    ans += total*val;
                    MOD2(ans);


                    if(j==0) {
                    for(x2=x1; x2<=x; ++x2) {  //00
                        for(y2=y; y2<=y1; ++y2) {
                            z= (x2<<8)|y2;
                            m[b][0].add(z, val);
                        }
                    }

                    y3 = min(y-1, y1);
                    for(x2=x1; x2<=x; ++x2) { //01
                        for(y2=x; y2<=y3; ++y2) {
                            z= (x2<<8)|y2;
                            m[b][1].add(z, val);
                        }
                    }

                    x3 = max(x+1, x1);
                    for(x2=x3; x2<=y; ++x2) { //10
                        for(y2=y; y2<=y1; ++y2) {
                            z= (x2<<8)|y2;
                            m[b][2].add(z, val);
                        }
                    }

                    x1 = max(x+1, x1);
                    y1 = min(y-1, y1);
                    } else if (j==1) {

                    for(x2=x1; x2<=x; ++x2) { //01
                        for(y2=x; y2<=y1; ++y2) {
                            z= (x2<<8)|y2;
                            m[b][1].add(z, val);
                        }
                    }
                    x1 = max(x+1, x1);
                    } else if (j==2) {

                    for(y2=y; y2<=y1; ++y2) {
                        for(x2=x1; x2<=y; ++x2) { //10
                            z= (x2<<8)|y2;
                            m[b][2].add(z, val);
                        }
                    }

                    y1 = min(y-1, y1);
                    }

                    for(x2=x1; x2<=y1; ++x2) { //11
                        for(y2=x2; y2<=y1; ++y2) {
                            z= (x2<<8)|y2;
                            m[b][3].add(z, val);
                        }
                    }
                }
            }
        }
        a=a^1;b=b^1;
    }

    cout << ans << endl;
}
