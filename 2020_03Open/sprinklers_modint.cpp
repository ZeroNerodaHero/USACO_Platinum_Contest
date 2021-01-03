#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <utility>
#define SIZE 2005
using namespace std;

#define P 1000000007
#define MOD(x, y) if(x>=y) x-=y
#define MOD2(x, y) if(x>=y) x%=y
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

ifstream in("sprinklers2.in");
ofstream out("sprinklers2.out");

template<const int mod = P>
class mint{
    public:
        mint(){ v = 0;}
        mint(int _v) {v = _v; MOD2(v,mod);}
        mint(ll _v) {MOD2(_v,mod); v = _v;}

        friend mint operator+(mint a, mint b){
            a += b;
            return a;
        }
        mint operator+=(mint b){
            v += b.v; MOD(v,mod);
            return *this; 
        }
        friend mint operator-(mint a, mint b){
            a-=b;
            return a;
        }
        mint operator-=(mint b){
            v -= b.v;
            if(v < 0) v+= mod;
            return *this;
        }
        friend mint operator*(mint a, mint b){
            a *= b;
            return a;
        }
        friend mint operator*(mint a, int b){
            a.v = (a.v * ll(b))%mod;
            return a;
        }
        mint operator*=(mint b){
            v = (ll(b.v) * v)%mod;
            return *this; 
        }
        friend mint operator~(mint a){
            return a.inv(a.v);
        }
        operator int const(){return v;}
        mint operator ==(mint b){ return v == b.v;}
        friend ostream& operator <<(ostream& os, mint& a){
            os << a.v;
            return os;
        }

    private:
        int v;
        void exgcd(int a, int b, int& x, int& y){
            if(b == 0){
                x = 1;
                y = 0;
            } else{
                exgcd(b,a%b,y,x);
                y -= (a/b)*x;
            }
        }

        int inv(int a){
            int x,y;
            exgcd(mod,a,y,x);
            if(x < 0){
                x += mod;
            }
            return x;
        }
};
typedef mint<> mi;

int N, t, sum;
bool a[SIZE][SIZE];
mi b[SIZE][SIZE];
mi r[SIZE][SIZE];
mi INV2 = ~mi(2);

int pow(int e){
    if(e < 30) return 1 << e;
    mi tmp = pow(e/2);
    tmp *= tmp;
    if(e & 1){
        tmp *= 2; 
    }
    return int(tmp);
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
            r[i][j+1] += r[i][j]; 
            if(!a[i+1][j]){ b[i+1][j] += (r[i][j]* INV2);} 

            b[i+1][j] += b[i][j]; 
            if(!a[i][j+1]){ r[i][j+1] += (b[i][j] * INV2);}
        }
    }
    out << (r[N][N] + b[N][N]) << endl;
}
