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
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

struct MCMF {
	using F = ll; using C = ll; // flow type, cost type
	struct Edge {
	    int to;
	    F flo, cap;
	    C cost;
    };
	int N;
	vector<C> p, dist;
	vector<int> pre;
	vector<Edge> eds;
	vector<vector<int>> adj;
	void init(int _N) {
	    N = _N;
		p.resize(N), dist.resize(N), pre.resize(N), adj.resize(N);
    }
	void ae(int u, int v, F cap, C cost) {
	    assert(cap >= 0);
		adj[u].pb(eds.size()); eds.pb({v,0,cap,cost});
		adj[v].pb(eds.size()); eds.pb({u,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool ckmin(C& a, const C& b) {
        return b < a ? a = b, 1 : 0;
    } // set a = min(a,b)
	bool path(int s, int t) { // find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max();
		for(int i=0;i<N;i++){
		    dist[i] = inf;
		}
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo;
		todo.push({dist[s] = 0,s});
		while (todo.size()) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.first > dist[x.second]) continue;
			for (auto& e: adj[x.second]) {
                const Edge& E = eds[e]; // all weights should be non-negative
				if (E.flo < E.cap && ckmin(dist[E.to],x.first+E.cost+p[x.second]-p[E.to]))
					pre[E.to] = e, todo.push({dist[E.to],E.to});
			}
		} // if costs are doubles, add some EPS so you
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) {
	    assert(s != t);
		for(int i=0;i<N;i++){
		    for(int e=0;e<(int)eds.size();e++) {
                const Edge& E = eds[e]; // Bellman-Ford
                if (E.cap)
                    ckmin(p[E.to],p[eds[e^1].to]+E.cost);
            }
		}
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			for(int i=0;i<N;i++){
                    p[i] += dist[i]; // don't matter for unreachable nodes
			}
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; ckmin(df,E.cap-E.flo);
            }
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, eds[pre[x]^1].flo -= df;
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};

int n, m, k;

MCMF flow_network;

vi path;

void print_path(int num){
    path.pb(num);
    if(num == n)
        return;
    for(auto u:flow_network.adj[num]){
        if((flow_network.eds[u]).flo == 1){
            (flow_network.eds[u]).flo = 0;
            print_path(flow_network.eds[u].to);
            return;
        }
    }
}

int main()
{
    IOS
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */
    ll ntc=1;
    //cin>>ntc;
    rep(tc,1,ntc+1)
    {
        //cout<<"Case #"<<tc<<": ";
        cin>>n>>m>>k;
        flow_network.init(n+2);
        flow_network.ae(0, 1, k, 0);
        flow_network.ae(n, n+1, k, 0);
        for(int i=0;i<m;i++){
            int u, v;
            cin>>u>>v;
            flow_network.ae(u, v, 1, 1);
        }
        pll res = flow_network.calc(0, n+1);
        if(res.first == k){
            cout<<res.second<<"\n";
            for(auto u:flow_network.adj[1]){
                if((flow_network.eds[u]).flo == 1){
                    path.pb(1);
                    print_path(flow_network.eds[u].to);
                    cout<<path.size()<<"\n";
                    for(auto v:path){
                        cout<<v<<" ";
                    }
                    cout<<"\n";
                    path.clear();
                }
            }
        }
        else cout<<"-1\n";
    }
    return 0;
}
