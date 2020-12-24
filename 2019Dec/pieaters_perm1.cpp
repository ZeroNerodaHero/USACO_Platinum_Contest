#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

ifstream fin("pieaters.in");
ofstream fout("pieaters.out");
const int MX = 45600;
int N,M;
int w[MX],l[MX],r[MX], a[MX];
int ans = 0;

void print(){
    for(int i = 1 ; i <= M; i++){
        cout << a[i] << ' ';
    } cout << endl;
}

void dfs(int i){
//    cout << i << endl;
    if(i > M){
        vector<int> v(N+1, 1);
        int total = 0;
        for(int k = 1; k <= M; k++){
            bool eat = 0;
            for(int m = l[a[k]]; m <= r[a[k]]; m++){
                if(v[m]){
                    v[m] = 0;
                    eat = true;
                }
            } 
            if(eat) total += w[a[k]];
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
        fin >> w[i] >> l[i] >> r[i];
        a[i] = i;
    }

    dfs(1);
    fout<< ans << endl;
}
