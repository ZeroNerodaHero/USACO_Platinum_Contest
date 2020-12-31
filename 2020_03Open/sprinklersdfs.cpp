#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
#define SIZE 2005
using namespace std;
ifstream in("sprinklers.in");
ofstream out("sprinklers.out");

int N, t;
bool a[SIZE][SIZE];
int ans;

void dfs(int x, int y, int r, int b, bool red){
    if(x > N || y > N) return;
    if(x == N && y == N){
        ans += (1<<(t-r-b));
        return;
    }

    if(red){
        dfs(x,y+1,r,b,red);
        if(!a[x+1][y]){    //put red here
            dfs(x+1,y,r+1,b,0);
        }
    } else{
        dfs(x+1,y,r,b,red);
        if(!a[x][y+1]){
            dfs(x,y+1,r,b+1,1);
        }
    }
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
    int sum = (1 << t);
    dfs(1,0,0,0,0);
    dfs(0,1,0,0,1);
    cout<< ans << endl;
}
