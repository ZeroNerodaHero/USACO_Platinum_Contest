#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");
const int MX = 45600;
int N,M,l,r;
long long b[MX];
int  w[MX], a[MX];
int ans = 0;

void print(){
    for(int i = 1 ; i <= M; i++){
        cout << a[i] << ' ';
    } cout << endl;
}

void dfs(int i){
//    cout << i << endl;
    if(i > M){
        long long v = 1;
        v <<= (N+1);
        v--;
        int total = 0;
        for(int k = 1; k <= M; k++){
            if (v&b[a[k]]) {
                total += w[a[k]];
                v &= ~b[a[k]]; 
            } 
        }
        ans =  max(ans,total);
//print();
        return;
    }

    for(int j = i; j <= M; j++){
        swap(a[i],a[j]);
        dfs(i+1);
        swap(a[i],a[j]);
    }
}

int main(){
    fin >> N >> M;
    //cout << N << ' ' << M << endl;
    for(int i = 1; i <= M; i++){
        fin >> w[i] >> l >> r;
        long long tmp = 1;
        b[i] = (tmp<<(l-r+1))-1;
        b[i] <<= l;
        a[i] = i;
    }

    dfs(1);
    fout<< ans << endl;
}
