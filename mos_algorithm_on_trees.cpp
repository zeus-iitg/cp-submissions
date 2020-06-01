#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pb push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/__gcd((a),(b))
#define vi vector<int>
#define vll vector<long long>
#define vvi vector<vi>
#define mt make_tuple
#define mp make_pair
#define hell 1000000007
#define mod 998244353
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define vpll vector<pll>
#define all(a) a.begin(),a.end()
#define ign cin.ignore();
#define g(a,b) get<a>(b)
#define vt(a) vector<a>
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define repi(i,a,b) for(ll i=b-1;i>=a;i--)
#define fi first
#define se second

#define o_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define o_setll tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
//to delete an element
//s.erase(s.find_by_order(s.order_of_key(ele)));
//where s is the name of the ordered_set
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

using namespace std;
using namespace __gnu_pbds;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef MY_PROJECT
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

struct query
{
    int l, r, lca, idx;
    bool flag;
};

const int N = 100000;
const int M = 100000;
const int l = ceil(log2(N));

int up[N][l+1], tin[N], tout[N];
int cnt[N], ans[M];
bool chk[N];
int wt[N];

vector<int> adj[N];
vector<int> euler;
vector<query> mo;

int n, q, u, v, timer=0;
int len;

void dfs(int v, int p)
{
    tin[v] = timer++;
    euler.pb(v);
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
    euler.pb(v);
    tout[v] = timer++;
}

bool is_ancestor(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

bool compare(query a, query b)
{
    if (a.l / len != b.l / len)
        return a.l / len < b.l / len;

    return ((a.l / len) & 1) ? (a.r < b.r) : (a.r > b.r);
}

query make_query(int a, int b, int idx)
{
    if (tin[a] > tin[b])
        swap(a, b);

    int _lca = lca(a, b);

    if (a == _lca)
        return {tin[a], tin[b], _lca, idx, 0};
    return {tout[a], tin[b], _lca, idx, 1};
}

int res;
void check(int node)
{
    //DO NOT COUNT NODE IF IT APPEARS TWICE
    if (!chk[node])
    {
        chk[node]=true;
        cnt[wt[node]]++;
        if (cnt[wt[node]] == 1)
            res++;
    }
    else
    {
        chk[node]=false;
        cnt[wt[node]]--;
        if (cnt[wt[node]] == 0)
            res--;
    }
}

void compute()
{
    res = 0;
    memset(cnt,0,sizeof(cnt));
    memset(chk,false,sizeof(chk));
    int l = 0, r = -1;
    for (query u : mo)
    {
        while (l > u.l)
            check(euler[--l]);
        while (r < u.r)
            check(euler[++r]);
        while (l < u.l)
            check(euler[l++]);
        while (r > u.r)
            check(euler[r--]);

        if (u.flag)
        {
            check(u.lca);
            ans[u.idx] = res;
            check(u.lca);
        }
        else
        {
            ans[u.idx] = res;
        }
    }
}

void compress(){
    map<int,int> m;
    for(int i=0;i<n;i++)
    {
        if(m.count(wt[i])){
            wt[i]=m[wt[i]];
        }
        else
        {
            int val=m.size();
            m[wt[i]]=val;
            wt[i]=val;
        }
    }
}

int main()
{
    IOS

    cin >> n >> q;


    for(int i=0;i<n;i++)
    {
        cin>>wt[i];
    }


    compress();

    rep(i,0,n-1)
    {
        cin >> u >> v;
        u--;
        v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, 0);

    int ql, qr;
    rep(i,0,q)
    {
        cin >> ql >> qr;
        ql--;
        qr--;
        mo.pb(make_query(ql, qr, i));
    }
    len = 500;
    sort(all(mo), compare);

    compute();

    for (int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
    return 0;
}
