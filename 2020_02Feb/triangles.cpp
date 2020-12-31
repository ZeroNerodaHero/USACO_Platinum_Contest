#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
#define SIZE 605
using namespace std;
ifstream in("triangles.in");
ofstream out("triangles.out");

int N, m;
bool a[SIZE][SIZE];
bool b[SIZE][SIZE];
int p[SIZE][SIZE];
int ans;

int main(){
    in >> N;
    for(int i = 1; i <= N; i++){
        string s;
        in >> s;
        for(int j = 1; j <= N; j++){
            if(s[j-1] == '*'){
                a[i+j][i-j+N] = true;
            }
        }
    }
    m = 2*N;

    //find three points with equal Chebyshev dist
    for(int i = 1, s = N; i <= m; i++){
        for(int j = s ? s: -s; j <= m; j++){
            p[i][j] = a[i][j] + p[i][j-1];
        }
        s--;
    }

    for(int i = 1, s = N; i <= m; i++){
        for(int j = s ? s : -s, m1 = m-j; j <= m1; j++){
            if(a[i][j]){
                for(int l = 2; l+j <= m1; l+= 2){
                    int k = l+j;
                    if(a[i][k]){
                        if(i > l){
                            ans+=p[i-l][k] - p[i-l][j-1];
                        }
                        if(i+l <= m){
                            ans+= p[i+l][k] - p[i+l][j-1];
                        }
                    }
                }
            }
        }
        s--;
    }

    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= m; i++){
            p[i][j] = a[i][j] + p[i-1][j];
        }
    }
    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= m; i++){
            if(a[i][j]){
                for(int l = 2; l+i <= m; l+=2){
                    int k = l+i;
                    if(a[k][j]){
                        if(j-l > 0){
                            ans+=p[k-1][j-l] - p[i][j-l];
                        }
                        if(j+l <= m){
                            ans+= p[k-1][j+l] - p[i][j+l];
                        }
                    }
                }
            }
        }
    }

    out << ans << endl;
}
 
