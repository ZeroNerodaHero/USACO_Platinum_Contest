#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");
const int MX = 302;
int N,M;
int w[MX][MX],dp[MX][MX],z[MX][MX];

int main(){
    fin >> N >> M;
    //cout << N << ' ' << M << endl;
    for(int i = 1; i <= M; i++){
        int l,r, x;
        fin >> x >> l >> r;
        z[l][r] = w[l][r] = dp[l][r] = x;
    }

    for(int l = 2; l <= N; l++){
        for(int i = 1, j = i+l-1; j <= N; i++, j++){
            for(int k = i; k <= j; k++){
                z[i][k] = max(z[i][k], max(z[i+1][k],w[i][j]));
                dp[i][j] = max(dp[i][j], dp[i][k-1]+dp[k+1][j]+z[i][k]);
            }
        }
    }
    fout<< dp[1][N] << endl;
}

/*
*
1
1.3mb
1ms
*
2
1.4mb
9ms
*
3
1.4mb
10ms
*
4
1.4mb
1ms
*
5
1.4mb
1ms
*
6
1.4mb
1ms
*
7
1.4mb
1ms
*
8
1.4mb
9ms
*
9
1.4mb
9ms
*
10
1.6mb
2ms
*
11
1.8mb
4ms
*
12
1.9mb
15ms
*
13
2.1mb
26ms
*
14
2.3mb
48ms
*
15
2.3mb
21ms
*
16
2.3mb
63ms
*
17
2.3mb
66ms


*/
