#include <bits/stdc++.h>
#define fi first
#define se second
#define endl '\n'
#define pb push_back
#define times clock() * 1.0 / CLOCKS_PER_SEC
#define pi 3.1415926535897932384626433832795
#define cntbit(x) __builtin_popcount(x)
//#define double long double
//#define int long long
#define all(x) x.begin(), x.end()
#define x1 lolkekmem
#define y1 kekmemlol
#define STRESS

// oxxxy vseravno pobedil

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int alp = 26, NMAX = 100000;

int go[alp][NMAX], term[NMAX];
int cur = 1;

void clear_bor() {
    for (int i = 0; i < 26; i++) {
        fill(go[i], go[i] + NMAX, -1);
    }
    fill(term, term + NMAX, 0);
    cur = 1;
}

void add_string(const string & s) {
    int v = 0;
    for (auto t : s) {
        if (go[t - 'a'][v] == -1) {
            go[t - 'a'][v] = cur++;
        }
        v = go[t - 'a'][v];
    }
    ++term[v];
}

void out_string(string & s, int v) {
    for (int i = 0; i < term[v]; i++) {
        cout << s << ' ';
    }
    for (int i = 0; i < 26; i++) {
        if (go[i][v] != -1) {
            s += static_cast<char>(i + 'a');
            out_string(s, go[i][v]);
            s.pop_back();
        }
    }
}

int main() {
    srand((unsigned int) time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#if __APPLE__
    freopen("/Users/macbook/ClionProjects/untitled1/a.in", "r", stdin);
    freopen("/Users/macbook/ClionProjects/untitled1/a.out", "w", stdout);
#else
    //    freopen("cinema.in", "r", stdin);
    //    freopen("cinema.out", "w", stdout);
#endif
    vector<string> v;
    string s;
    clear_bor();
    while (cin >> s) {
        add_string(s);
        v.pb(s);
    }
    string p = "";
    out_string(p, 0);
    cout << '\n';
    sort(all(v));
    for (auto t : v) {
        cout << t << ' ';
    }
    cout << endl;
}