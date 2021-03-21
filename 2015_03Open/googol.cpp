#include <bits/stdc++.h>

using namespace std;
const int MX = 100005;
typedef long long ll;
typedef pair<int, int> PI;
typedef vector<int> VI;

#define f first
#define s second
const string start("1"), stop("0");

ll countwith(const string &m, ll c) {
    if(m==stop) return 0;
    string l, r;
    cout << m << endl;
    cin >> l >> r;
    ll lc,rc;

    if (c&1) {
        rc = (c-1)/2;
        lc = countwith(l, rc);
    } else {
        lc = c/2;
        rc = countwith(r, lc-1);
    }
    return rc+lc+1;
}

ll count(const string &m) {
    if(m==stop) return 0;
    string l, r;
    cout << m << endl;
    cin >> l >> r;
    ll rc = count(r);
    ll lc = countwith(l, rc);
    return rc+lc+1;
}

int main(){
    ll ans = count(start);
    cout << "Answer " << ans << endl;
}

