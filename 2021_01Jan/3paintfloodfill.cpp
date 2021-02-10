#include <bits/stdc++.h>
using namespace std;

const unsigned int MX = 1002;
const int P = 1e9+7;
#define MOD(x) if(x>=P) x-=P
#define MOD2(x) if(x>=P) x%=P
typedef pair<int,int> PI;

struct node {
    int x,y,x2,y2,i;
    bool operator <(const node &o) const {
        return (x<o.x) ||((x==o.x)&&(y<o.y));
    }
};

int N, M, Q,C,D,u;
int ans[MX];
node q[MX];

char a[MX][MX];
int id[MX][MX], p[MX*MX], v[MX][MX];

int find(int x)
{
    if(p[x] ==0) return x;
    p[x] = find(p[x]);
    return p[x];
}

int solve(int x, int y, int x2, int y2);
char b[MX][MX], e[MX*MX];
int s[MX][MX];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int x, y, x2, y2;

int flood(int c, int d){
    queue<PI> q;
    q.push(PI(c,d));
    char ch = a[c][d];
    v[c][d] = u;

    int t = 1;

    while(!q.empty()){
        PI cur = q.front();
        q.pop();
        for(int i = 0; i < 4; i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx >= x && ny >= y && nx <= x2 && ny <= y2
                && v[nx][ny] != u && a[nx][ny] == ch){
                v[nx][ny] = u;
                if(!(nx == x || nx == x2 || ny == y || ny == y2)){
                    if(b[nx][ny] == 1) t= 0;
                }
                q.push(PI(nx,ny));
            }
        }
    }
    return t;
}

void doit()
{
    int t = solve(1,1,N,M);

    for(int i=1; i<=N; ++i) {
    for(int j=1; j<=M; ++j) {
        id[i][j] = find(id[i][j]);
        if(!e[id[i][j]]) e[id[i][j]]=1, b[i][j]=1;
    }
    }

    for (int i=1; i<=N; i++) {
    for (int j=1; j<=M; j++)
        s[i][j] = s[i-1][j] + s[i][j-1]
                - s[i-1][j-1] + b[i][j];
	}
    for (int k = 1; k< C; ++k) {
        node & z=q[k];
        x = z.x, y =z.y, x2 = z.x2, y2 = z.y2;
        int t= s[x2-1][y2-1] - s[x][y2-1] - s[x2-1][y] + s[x][y];
        u++;

        for(int j = y; j <= y2; j++){
            if(v[x][j] != u && flood(x,j)) t++;
            if(v[x2][j] != u && flood(x2,j)) t++;
        }

        for(int i = x+1; i < x2; i++){
            if(v[i][y] != u && flood(i,y)) t++;
            if(v[i][y2] != u && flood(i,y2)) t++;
        }
        ans[z.i] = t;
    }
}

#define set(x,y) id[x][y] = t;p[++t] = 0
int solve(int x, int y, int x2, int y2)
{
    int total = (x2-x+1)*(y2-y+1);
    int t=1; p[t]=0;

    for(int i=x; i<=x2; i++) {
        set(i,y);
        if(i==x) {
            for(int j=y+1; j<=y2; j++) {
                if(a[i][j] == a[i][j-1]) {
                    id[i][j] = id[i][j-1]; total--;
                } else {
                    set(i, j);
                }
            }
            continue;
        }

        if(a[i][y] == a[i-1][y]) {
            int b=find(id[i-1][y]);
            p[b] = t-1;
            total--;
        }
        for(int j=y+1; j<=y2; j++) {
           if(a[i][j] == a[i][j-1]) {
                id[i][j] = id[i][j-1]; total--;
           } else {
                set(i, j);
           }

           if(a[i][j] == a[i-1][j]) {
               int b = find(id[i-1][j]);
               if(b != id[i][j]) {
                   p[b] = t-1;
                   total--;
               }
           }
        }
    }

    return total;
}

#define qqq 10
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M >> Q;
    for (int i = 1; i<= N; ++i) cin >> (&(a[i][1]));
    C=1, D=Q;
    for (int i = 1; i<= Q; ++i) {
        node & s=q[C];
        cin >> s.x >> s.y >> s.x2 >> s.y2; s.i=i;
        if((s.x2-s.x)<qqq || (s.y2-s.y)<qqq) {
            q[D].x=q[C].x;
            q[D].y=q[C].y;
            q[D].x2=q[C].x2;
            q[D].y2=q[C].y2;
            q[D].i = i;
            --D;
        } else C++;
    }
    for (int i = C; i<= Q; ++i) {
        node & s=q[i];
        ans[s.i] = solve(s.x , s.y , s.x2 , s.y2);
    }

    doit();

    for (int i = 1; i<= Q; ++i) {
        cout << ans[i] << endl;
    }

}
