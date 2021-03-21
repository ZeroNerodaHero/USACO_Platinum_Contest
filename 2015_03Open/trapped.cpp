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

int N, ans, f[MX], t[MX]; //trapped
PI a[MX];

int find(int x){
    if(f[x] != x){
        f[x] = find(f[x]);
    }
    return f[x];
}

bool check(int k){
    int l=k, r=k+1;
    while((l>0) && (r<=N)) {
        int d = a[r].f - a[l].f;
        if(d > a[l].s) f[l]=find(l-1), l=f[l];
        else if (d > a[r].s) r++;
        else{
            // any point in range [k,r) is trapped.
            for (int i=k; i<r; i++) t[i]= 1, f[i]=l;
            return true;
        }
        //if (1 == t[l]) return false;
    }
    return false;
}

int main(){
    cio("trapped");
    cin >> N;
    for (int i=1; i<=N; f[i]=i, i++) cin >> a[i].s >> a[i].f;
    sort(a+1, a+N+1);
    for (int i=1; i<N; i++){
        if (t[i]) { //trapped
            ans += a[i+1].f-a[i].f;
            continue;
        }
        if (check(i)) ans += a[i+1].f-a[i].f;
    }

    cout << ans << endl;
}

