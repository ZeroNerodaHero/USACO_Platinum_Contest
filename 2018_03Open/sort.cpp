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

int N;
int a[MX],c[MX],t[MX];

int main(){
    cio("sort");
    cin >> N;
    for(int i = 1; i<= N; i++){
        cin >> a[i];
        c[i] = i;
    }

    sort(c+1,c+N+1,[](int x, int y) { return (a[x] == a[y]) ? (x < y) : (a[x] < a[y]); });

    for(int i = 1, mx = 0; i <= N; i++){
        mx = max(mx, c[i]);
        t[i] = mx - i;
    }
    ll ans = 0;
    for(int i = 1; i <= N; i++){
        int x = max(t[i],t[i-1]);
        if(x == 0) ans++;
        else ans += x;
    }
    cout << ans << endl;
}
