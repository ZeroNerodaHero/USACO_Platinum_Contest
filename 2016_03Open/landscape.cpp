#include <bits/stdc++.h>

using namespace std;
const int MX = 100005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N,Z,T,u,v,a[MX];
ll ans, cost[2];
priority_queue<int> s[2];

int main(){
    cio("landscape");
    cin >> N >> cost[0] >> cost[1] >> Z;
    T = cost[0] + cost[1]; 
//cout << "cost 0 " << cost[0] << " - " << cost[1] << endl;
    for(int i = 1; i <= N; i++){
        cin >> u >> v;
        a[i] = v - u;
//cout << i << " : " << a[i] << endl;
        if(a[i] == 0) continue;
        if(a[i] < 0){
            u = 1;
            a[i] = -a[i];
        } else{
            u = 0;
        }
        v = 1^u;
        for(int j = 1; j <= a[i]; j++){
            if(!s[v].empty() && ((i * Z - s[v].top()) < cost[u])){
                int tmp = s[v].top();
                if((i * Z - tmp) < cost[u]){
                    ans += i * Z - tmp;
                    s[v].pop();
                    s[u].push(2* i * Z - tmp);
                }
            }
            else{
                s[u].push(i*Z + cost[u]);
                ans += cost[u];
            }
        }
    }   

    cout << ans << endl;
}
