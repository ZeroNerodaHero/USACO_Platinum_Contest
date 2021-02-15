#include "grader.h"
#include <bits/stdc++.h>
using namespace std;
const int MX = 1000005;
int c[MX],q[MX];
bool done;

void helpBessie(int ID)
{
    if(done) return;
    int N = getTrainLength();
    int K = getWindowLength();
    int i = getCurrentCarIndex();
    int p = getCurrentPassIndex();
    if(p){
        int f =0, e = -1;
        for(int x = 0; x < N; x++){
            while(e >= f && c[x] <= c[q[e]]){
                e--;
            }
            q[++e] = x;
            if(x >= K-1){
                shoutMinimum(c[q[f]]);
                if(q[f] <= (x-K+1)) f++;
            }
        }
        done = 1;
    } else{
        c[i] = ID;
    }
       
}
#if 0
int main(){
    cin >> N >> K;
    for(i = 0; i < N; i++){
        int x;
        cin >> x;
        helpBessie(x);
    }
    p = true;
    for(i = 0; i < N; i++){
        helpBessie(i);
    }
}
#endif
