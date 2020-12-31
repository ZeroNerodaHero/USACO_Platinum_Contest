#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#define SIZE 100001
using namespace std;
ifstream in("deleg.in");
ofstream out("deleg.out");

int N, K;
vector<int> r[SIZE];
vector<int> n[SIZE];


void dfs(int x, int p){
    for(auto i : r[x]){
        if(i != p){
            dfs(i,x);
            n[x].push_back(i);
        }
    }
    r[x].resize(n[x].size());
}

bool match(vector<int>& v, int skip){
    int l = 0, r = v.size()-1;
    while(l < r){
        if(l == skip) l++;
        if(r == skip) r--;
        if(v[l] + v[r] < K) return 0;
        l++, r--;
    }
    return 1;
}

int dfs(int x){
    int ret = 0;
    vector<int>& v = r[x];
    v.clear();
    for(auto i: n[x]){
        ret = dfs(i);
        if(ret < 0) return -1;
        v.push_back(ret+1);
    }
    if(v.size() == 0) return 0;

    sort(v.begin(), v.end());

    if(x == 1){
        if(v.size() & 1){
            if(v.back() < K) return -1; 
            v.pop_back();
        }
        return match(v,-1) ? 0 : -1;
    }

    bool ok = match(v,(v.size() & 1) ? 0 : -1);
    if(!ok) return -1;
    if((v.size() & 1) == 0){
        if(v.back() < K) return 0;
        v.pop_back();
    }

    int left = 0, right = v.size()-1;
    while(left < right){
        int mid = (left + right+1)/2;
        if(match(v,mid)){
            left = mid;
        } else{
            right = mid-1;
        }
    }   

    return v[left];
}

int main(){
    in >> N;
    for(int i = 1; i < N; i++){
        int a,b;
        in >> a >> b;
        r[a].push_back(b);
        r[b].push_back(a);
    }
    dfs(1,0);

    int left = 1, right = N;
    while(left < right){
        K = (left+right+1)/2;

        if(dfs(1) >= 0){
            left = K;
        } else{
            right = K-1;
        }
    }
    out << left << endl;
}
    
