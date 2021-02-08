#include <bits/stdc++.h>
using namespace std;
 
int N, M, Q;

typedef pair<int, int> PI;
const unsigned int MX = 2002; 
char a[MX][MX];
int ox[MX][MX], oy[MX][MX];
int sp[MX][MX], vp[MX][MX], hp[MX][MX];
bool vis[MX][MX];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int x, y, x2, y2;

bool in(int u, int v, int nx, int ny) {
    if (!(nx>0 && ny>0 && nx <= N + 1 && ny <= M + 1)) return false;
    if (nx == u + 1) return a[u][v] != a[u][v - 1];
    if (nx == u - 1) return a[nx][v] != a[nx][v - 1];
    if (ny == v + 1) return a[u][v] != a[u - 1][v];
    return a[u][ny] != a[u - 1][ny];
}
 
bool out(int u, int v) {
    int c = ox[u][v], d = oy[u][v];
    if (c > x && c <= x2 && d > y && d <= y2 && !vis[c][d]) {
        vis[c][d] = true;
        return true;
    }
    return false;
}
 
void restore(int u, int v) {
    int a = ox[u][v], b = oy[u][v];
    vis[a][b] = false;
}
 
void trav(int u, int v) {
    queue<PI> q;
    q.push(PI(u,v));

    while(!q.empty()) {
        u = q.front().first;
        v = q.front().second; q.pop();

        for(int i=0; i< 4; ++i) {
            int nx = u + dx[i], ny = v + dy[i];
            if (in(u, v, nx, ny)) {
                if (nx == u + 1) vp[u][v] = 1;
                else if (nx == u - 1) vp[nx][v] = 1;
                else if (ny == v + 1) hp[u][v] = 1;
                else hp[u][ny] = 1;
 
                if (!ox[nx][ny]) {
                    ox[nx][ny] = ox[u][v];
                    oy[nx][ny] = oy[u][v];
                    q.push(PI(nx, ny));
                }
            }
        }
    }
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> N >> M >> Q;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) cin >> a[i][j];
    for(int i=1; i<=N + 1; i++) for(int j=1; j<=M + 1; j++) if (!ox[i][j]) {
        sp[i][j] = 1;
        ox[i][j] = i; oy[i][j] = j;
        trav(i, j);
    }
    for(int i=1; i<= N + 1; i++) for(int j=1; j<=M + 1; j++) {
        sp[i][j] += sp[i - 1][j] + sp[i][j - 1] - sp[i - 1][j - 1];
        vp[i][j] += vp[i - 1][j] + vp[i][j - 1] - vp[i - 1][j - 1];
        hp[i][j] += hp[i - 1][j] + hp[i][j - 1] - hp[i - 1][j - 1];
    }
 
    while (Q--) {
        cin >> x >> y >> x2 >> y2;
        if (x > x2) swap(x, x2);
        if (y > y2) swap(y, y2);
 
        int E = vp[x2][y2] - vp[x2][y] - vp[x - 1][y2] + vp[x - 1][y] +
                hp[x2][y2] - hp[x2][y - 1] - hp[x][y2] + hp[x][y - 1];
        int V = (x2 - x) * (y2 - y);
        int C = sp[x2][y2] - sp[x2][y] - sp[x][y2] + sp[x][y];
 
        for(int i=x; i<=x2 + 1; i++) {
            if (out(i, y2 + 1)) C--;
            if (out(i, y)) C--;
        }
        for(int i=y; i<= y2 + 1; i++) {
            if (out(x2 + 1, i)) C--;
            if (out(x, i)) C--;
        }
        for(int i=x; i<= x2 + 1; i++) {
            restore(i, y2 + 1);
            restore(i, y);
        }
        for(int i=y; i<= y2 + 1; i++) {
            restore(x2 + 1, i);
            restore(x, i);
        }
 
        cout << E - V + C + 1 << '\n';
    }
    return 0;
}
