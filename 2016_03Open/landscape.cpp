#include <bits/stdc++.h>

using namespace std;
const int MX = 100005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;
#define f first
#define s second 

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N,Z,u,v,a;
ll ans, cost[2];
priority_queue<PI> s[2];

int main(){
    cio("landscape");
    cin >> N >> cost[0] >> cost[1] >> Z;
    for(int i = 1; i <= N; i++){
        cin >> u >> v;
        a = v - u;
        if(a == 0) continue;
        if(a < 0){
            u = 1;
            a = -a;
        } else{
            u = 0;
        }
        v = 1^u;
        if(!s[v].empty() && ((i * Z - s[v].top().f) >= cost[u])) s[v].pop();
        if(!s[u].empty() && ((i * Z - s[u].top().f) >= cost[v])) s[u].pop();
        while(a > 0){
            if(!s[v].empty() && ((i * Z - s[v].top().f) < cost[u])){
                int tmp = s[v].top().f;
                int tmps = s[v].top().s;
                int newcost = (i * Z - tmp);
                int t = min(a,tmps);
                ans += newcost * t;
                a -= t; tmps -= t;
                s[v].pop();
                if(tmps > 0) s[v].push(PI(tmp,tmps));
                s[u].push(PI(i * Z + newcost,t));
            }
            else{
                s[u].push(PI(i*Z + cost[u],a));
                ans += cost[u]*a;
                a = 0;
            }
        }
    }   

    cout << ans << endl;
}
