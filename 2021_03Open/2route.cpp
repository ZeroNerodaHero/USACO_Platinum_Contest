#include <bits/stdc++.h>
using namespace std;

const unsigned int MX =  102;
typedef vector<int> VI;
typedef pair<int, int> PI;
const int P = 1e9+7;
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MODS(x) if(x<0) x+=P
#define MOD2(x) if(x>=P) x%=P
#define f first
#define s second

int N, M, T, K;
char a[MX][MX], b[MX];
int c[MX], c1[MX];
int p[MX];
VI f[MX], g[MX];
map<int, int> s, t;
ll ans;
PI loop[2];
int din[MX], dout[MX], d[MX], perm[MX], e[MX*10];
bool vis[MX], used[2];

int dfs(map<int, int> &m, int res, int k);

int dfs1(map<int, int> m, int res, int z, int x, int de=0) {
	if (z==x) {
cout << de << " dfs1 return " << z << " " << x << endl;
		return dfs(m, res, 1);
	}

cout << de << " dfs1 " << z << " " << x << endl;
	int sum = 0;
    m[z]--;
	d[z]++;
	for(auto i:g[z]) {
//cout << "\t" <<  de << " dfs1 " << i << "/" <<e[i] << " " << vis[i] << endl;

		if(vis[i] || e[i]>x) continue;
        vis[i]=true;
        m[e[i]]++;
		sum += dfs1(m, res+1, e[i], x, de+1); MOD(sum);
        m[e[i]]--;
        vis[i]=false;
	}
	d[z]--;
	//m[z]++;

	return sum;
}

int checkloop(map<int, int> m, int res, int k) {
	int sum =0;
	for(int i=0; i<K; ++i) {
		if(used[i]) continue;
        int x=loop[i].f, y=loop[i].s;
        d[x]++;
        vis[y]=true;
        m[x]--;
        m[e[y]]++;
		sum+=dfs1(m, res+1, e[y], x); MOD(sum);
cout << " checkloop sum= " << sum << " " << k << endl;
        vis[y]=false;
        m[x]++;
        m[e[y]]--;
        d[x]--;
	}

cout << "checkloop " << sum << endl;
	return sum;
}

int dfs(map<int, int> &m, int res, int k)
{
    int R=res;
cout << k << " dfs " << res << " " << k << endl;

    map<int, int> d1, st[2];
    vector<int> v1;
    ll mu=1, sum = 0;

    int a=0, b=1;
    bool change = true;
    st[0] = m;
    while(change) {
        change = false;
        st[b].clear();
cout << "state: ";for(auto i:st[a]) cout << i.f << ","<<i.s<<"+"<<d[i.f]<<"="<<din[i.f]<<" ";cout << endl;
        for (auto i:st[a]) {
            if(i.s <= 0) continue;
            if((i.s+d[i.f]) == din[i.f]) {
                change = true;
                mu *= perm[i.s]; MOD2(mu);
cout << i.f << ": " << d[i.f] << "," << i.s << " / " << mu << " :: ";
                for(auto j:g[i.f]) {
                    if(vis[j]) continue;
cout << e[j] << " ";
                    st[b][e[j]]++;

                    d1[i.f]+=i.s;
                    d[i.f]+=i.s;
                    res++;
                    vis[j] = true;
                    v1.push_back(j);
                }
cout << endl;
            } else {
                st[b][i.f]+=i.s;
            }
        }

        a^=1,b^=1;
    }

cout << k << " k/res " << res << " " << mu << endl;
    if(res!=M){
        sum = checkloop(st[a], res, k);
		if(k==0&&K==2&&used[0]==false&&used[1]==false) {
            used[0]=used[1]=true;
        	//sum -= checkloop2();
        	//sum += checkloop12();
        	//sum += checkloop21();
		}
        mu *= sum; MOD2(mu);
    }

    if(R!=0) {
        for(auto i:v1) vis[i]=false;
        for(auto i:d1) d[i.f]-=i.s;
    }
    return mu;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    perm[0]=perm[1]=1;
    for(int i=2; i<MX; i++) {
        ll lt=i; lt*=perm[i-1]; MOD2(lt); perm[i]=lt;
    }

    int k = 0;
    for (int tt=1; tt<=T; tt++) {
        cin >> N >> K;
        cin >> (b+1);
        s.clear(), t.clear(); M=k=0; used[0]=used[1]=0;
        for (int i=1; i<=N; ++i) g[i].clear(), din[i]=dout[i]=d[i]=0;

        for(int i = 1; i <= N; ++i) {
            if(b[i] == 'S') {
               s[i]=1;
               din[i]++;// d[i]++;
            } else if(b[i]=='R'){
               t[i]=1;
               dout[i]++;
            }
        }

        for (int i=1; i<=N; ++i) {
            cin >> (a[i]+1);
            for(int j = 1; j<=N; j++) {
                if(a[i][j] == '1') {
                    dout[i]++, din[j]++;
                    e[M] = j;
                    if(i>j) loop[k++]=PI(i,M);
                   	else g[i].push_back(M);
                    M++;
                }
            }
        }
if(tt!=1) continue;
cout << "\n\ncase" << tt << " " << N << " " << K << endl;
cout << "S: ";for (auto i:s) cout << i.f << " ";cout << endl;
cout << "R: ";for (auto i:t) cout << i.f << " ";cout << endl;
for (int i=1; i<N; ++i) {cout << i<<": ";for(auto j:g[i]) cout<<e[j]<<",";cout<<endl;}
cout << "loop ";for (int i=0; i<K; ++i) cout << i<<": " << loop[i].f << "/"<< loop[i].s << "/"<<e[loop[i].s] << " ";cout << endl;

        ans = 1;
        for (int i=1; i<=N; ++i) {
            //ans*=perm[dout[i]]; MOD2(ans);
            ans*=perm[din[i]]; MOD2(ans);
        }
        if(K>0) {
cout << M << " ans = " << ans << endl;
            for (int i=0; i<M; ++i) vis[i] = 0;
            ans -= dfs(s, 0, 0); MODS(ans);
        }
        cout << ans << endl;
    }
    return 0;
}
