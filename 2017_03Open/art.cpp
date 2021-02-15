#include <bits/stdc++.h>

using namespace std;
const int MX = 1002;
const int MX1 = 1000002;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

void cio(string fname){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((fname+".in").c_str(),"r",stdin);
    freopen((fname+".out").c_str(),"w",stdout);
}

int N, M;
int x[MX1],y[MX1],x2[MX1],y2[MX1];
int m[MX1],v[MX1],s[MX1];
int a[MX][MX],p[MX][MX];

int main(){
    cio("art");
    cin >> N;
    memset(x,MX1,sizeof(x));
    memset(y,MX1,sizeof(y));
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int k;
            cin >> k;
            if(k == 0) continue;
            if(v[k] == 0){
                v[k] = 1;
                m[M++] = k;
            }
            a[i][j] = k;
            x[k] = min(x[k],i);
            y[k] = min(y[k],j);
            x2[k] = max(x2[k],i);
            y2[k] = max(y2[k],j);
        }
    }
    if(M == 1){
        cout << (N * N -1) << endl;
        return 0;
    }
    for(int i = 0; i < M; i++){
        int k = m[i];
        p[x[k]][y[k]]++;
        p[x2[k]+1][y[k]]--;       
        p[x[k]][y2[k]+1]--;
        p[x2[k]+1][y2[k]+1]++;       
    }   

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            p[i][j] += p[i][j-1] + p[i-1][j] - p[i-1][j-1];
        }   
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(a[i][j] == 0) continue;
            if(p[i][j] > 1){
               s[a[i][j]] = 1; 
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= N * N; i++) {
        if(s[i] == 0) ans++;
    } 
    cout << ans << endl;
}
