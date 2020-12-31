#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
#define SIZE 2005
using namespace std;

#define P 1000000007
#define INV2 ((P+1)/2)
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

ifstream in("sprinklers2.in");
ofstream out("sprinklers2.out");

int N, t, sum, ans;
bool a[SIZE][SIZE];
ll b[SIZE][SIZE];
ll r[SIZE][SIZE];

int pow(int e){
    if(e < 30) return 1 << e;
    long long tmp = pow(e/2);
    tmp *= tmp; MOD2(tmp);
    if(e & 1){
        tmp <<= 1; MOD(tmp);
    }
    return tmp;
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
    sum = pow(t);

    r[0][1] = sum;
    b[1][0] = sum;

    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= N; j++){
            r[i][j+1] += r[i][j]; MOD(r[i][j+1]);
            if(!a[i+1][j]){ b[i+1][j] += (r[i][j]* INV2); MOD2(b[i+1][j]); }

            b[i+1][j] += b[i][j]; MOD(b[i+1][j]);
            if(!a[i][j+1]){ r[i][j+1] += (b[i][j] * INV2); MOD2(r[i][j+1]); }
        }
    }
    ans = r[N][N] + b[N][N]; MOD(ans);
    out<< ans << endl;
}
