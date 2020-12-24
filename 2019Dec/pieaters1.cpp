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
int dp[MX][MX],z[MX][MX][MX];

int main(){
    fin >> N >> M;
    //cout << N << ' ' << M << endl;
    for(int i = 1; i <= M; i++){
        int l,r, x;
        fin >> x >> l >> r;
        dp[l][r] = x;
        for(int j = l; j <= r; j++){
            z[j][l][r] = x;
        }
    }
    for(int i = 1; i <= N; i++){
        for(int j = i; j > 0; j--){
            for(int k = i; k <= N; k++){
                z[i][j][k] = max(z[i][j][k],z[i][j][k-1]);
                z[i][j][k] = max(z[i][j][k],z[i][j+1][k]);
            }
        }
    }

    for(int l = 2; l <= N; l++){
        for(int i = 1, j = i+l-1; j <= N; i++, j++){
            for(int k = i; k <= j; k++){
                dp[i][j] = max(dp[i][j], dp[i][k-1]+dp[k+1][j]+z[k][i][j]);
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
17.3mb
13ms
*
3
17.3mb
5ms
*
4
17.3mb
17ms
*
5
17.3mb
5ms
*
6
17.3mb
14ms
*
7
17.3mb
5ms
*
8
17.3mb
13ms
*
9
17.3mb
13ms
*
10
35.4mb
27ms
*
11
53.5mb
37ms
*
12
69.5mb
77ms
*
13
87.6mb
132ms
*
14
104.4mb
215ms
*
15
104.4mb
183ms
*
16
104.4mb
252ms
*
17
104.4mb
262ms


*/
