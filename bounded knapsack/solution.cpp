//Link to problem: https://cses.fi/problemset/task/1159/
//Approach: https://codeforces.com/blog/entry/2257

#include <bits/stdc++.h>
#include <time.h>
#include <stdlib.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pb push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define ull unsigned long long
#define gcd(a,b) __gcd((a),(b))
#define lcm(a,b) ((a)*(b))/__gcd((a),(b))
#define clr(x) x.clear()
#define vi vector<int>
#define vll vector<long long>
#define vvi vector<vi>
#define mp make_pair
#define hell 1000000007
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define vpll vector<pll>
#define all(a) a.begin(),a.end()
#define ign cin.ignore();

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

int n,W;

vi val, wt;

int KnapSack()
{
    int dp[W+1];

    memset(dp, 0, sizeof(dp));

    for(int i=0; i < n; i++)
        for(int j=W; j>=wt[i]; j--)
            dp[j] = max(dp[j] , val[i] + dp[j-wt[i]]);

    return dp[W];
}

int main()
{
    IOS
    cin>>n>>W;
    int h[n],s[n],k[n];
    for(int i=0;i<n;i++)
    {
        cin>>h[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>k[i];
    }
    for(int i=0;i<n;i++)
    {
        int cur=1;
        while(2*cur+1<=k[i]){
            cur=2*cur+1;
        }
        if(cur!=k[i]){
            val.pb((k[i]-cur)*(s[i]));
            wt.pb((k[i]-cur)*(h[i]));
        }
        int temp=1;
        while(temp<=cur){
            val.pb(temp*s[i]);
            wt.pb(temp*h[i]);
            temp=temp*2;
        }
    }
    n=val.size();
    cout<<KnapSack();
    return 0;
}
