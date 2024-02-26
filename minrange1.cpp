///stealthyguy
#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3, unroll-loops")
#define pb push_back
#define f first
#define s second
#define MOD 1000000007
#define Task "MINRANGE"

using namespace std;

const int maxn = 100001;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n, m, a[maxn];
int tree[4*maxn], id[maxn];

void init(int node, int l, int r)
{
    if (l == r){
        tree[node] = a[r];
        id[r] = node;
        return;
    }
    int mid = (l + r)/2;
    init(node*2, l, mid);
    init(node*2 + 1, mid + 1, r);
    tree[node] = min(tree[node*2], tree[node*2 + 1]);
}

int get_min(int node, int l, int r, int u, int v)
{
    if (u > r || v < l) return MOD;
    if (l >= u && r <= v) return tree[node];

    int mid = (l + r)/2;
    int tleft = get_min(node*2, l, mid, u, v);
    int tright = get_min(node*2 + 1, mid + 1, r, u, v);

    return min(tleft, tright);
}

void update(int pos, int val)
{
    int node = id[pos];
    tree[node] = a[pos] = val;
    while (node > 1){
        node /= 2;
        tree[node] = min(tree[node*2], tree[node*2 + 1]);
    }
}

int main()
{
	ios_base::sync_with_stdio(0);
    //freopen(Task".inp", "r", stdin);
    //freopen(Task".out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    init(1, 1, n);
    for (int i = 1; i <= m; i ++)
    {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) update(u, v);
            else cout << get_min(1, 1, n, u, v) << endl;
    }

    return 0;
}
