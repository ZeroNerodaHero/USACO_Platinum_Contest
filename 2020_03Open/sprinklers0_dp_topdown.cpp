#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <cstring>
#include <utility>
#define SIZE 2005
using namespace std;
ifstream in("sprinklers2.in");
ofstream out("sprinklers2.out");

int N, t, sum;
bool a[SIZE][SIZE];
int ans;
#define P 1000000007
#define INV2 ((P+1)/2)
typedef long long ll;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
int dp[2][SIZE][SIZE];

int pow(int e){
    if(e < 30) return 1 << e;
    long long tmp = pow(e/2);
    tmp *= tmp; MOD2(tmp);
    if(e & 1){
        tmp <<= 1; MOD(tmp);
    }
    return tmp;
}   

int dfs(int x, int y, bool red){
    if(dp[red][x][y] >= 0) return dp[red][x][y];
    if(x == N && y == N){
        dp[red][x][y] = sum;
        return sum;
    }

    int total = 0;

    if(red){
        if((y+1) <= N){
            total += dfs(x,y+1,red); MOD(total);
        }
        if((x+1) <= N && !a[x+1][y]){    //put red here
            ll tmp = dfs(x+1,y,0);
            tmp *= INV2; MOD2(tmp);
            total += tmp; MOD(total);
        }
    } else{
        if((x+1) <= N){
            total += dfs(x+1,y,red); MOD(total);
        }
        if((y+1) <= N && !a[x][y+1]){
            ll tmp = dfs(x,y+1,1);
            tmp *= INV2; MOD2(tmp);
            total += tmp; MOD(total);
        }
    }
    dp[red][x][y] =total;
    return total;
}

int main(){
    in >> N;
    for(int i = 1; i <= N; i++){
        string s;
        in >> s;
        for(int j = 1; j <= N; j++){
            if(s[j-1] == '.'){
                t++;
            } else{
                a[i][j] = 1;
            }
        }
    }
    memset(dp,-1,sizeof(dp));
    sum = pow(t);
    ans = dfs(1,0,0)+ dfs(0,1,1); MOD(ans);
    out<< ans << endl;
    
}
