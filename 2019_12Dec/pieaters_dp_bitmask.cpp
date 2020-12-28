#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");
const int MX = 45600;
int N,M,l,r;
long long b[MX];
int  w[MX];
unordered_map<long long, int> m;

int dfs(long long mask){
    auto it = m.find(mask);
    if(it != m.end()){
        return it->second;
    }
    int ans = 0;
    for(int k = 1; k <= M; k++){
        if (mask&b[k]) {
            ans =  max(ans, dfs(mask&(~b[k]))+w[k]);
        } 
    }
    m[mask] = ans;

    return ans;
}

int main(){
    fin >> N >> M;
    //cout << N << ' ' << M << endl;
    for(int i = 1; i <= M; i++){
        fin >> w[i] >> l >> r;
        long long tmp = 1;
        b[i] = (tmp<<(r-l+1))-1;
        b[i] <<= l;
    }

    long long v=1;
    v <<= (N+1);
    int ans = dfs(v-1);
    fout<< ans << endl;
}
