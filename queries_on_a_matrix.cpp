// no update between queries

// LINK TO PROBLEM: https://www.codechef.com/COW42020/problems/COW3E

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

ll arr[1001][1001];

ll ini[1001][1001];

int main() {
    IOS
    ll n,m,u,q;
    cin>>n>>m>>u>>q;
    memset(arr, 0, sizeof(arr));

    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<m;j++)
        {
            cin>>ini[i][j];
        }
    }

    for(ll i=0;i<u;i++){
        ll k,r1,c1,r2,c2;
        cin>>k>>r1>>c1>>r2>>c2;
        //r1--;c1--;r2--;c2--;
        arr[r1][c1]+=k;
        arr[r2+1][c1]-=k;
        arr[r1][c2+1]-=k;
        arr[r2+1][c2+1]+=k;
    }

    /*for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }*/

    for(ll i=1;i<m;i++)
        arr[0][i]+=arr[0][i-1];

    for(ll i=1;i<n;i++)
        arr[i][0]+=arr[i-1][0];

    for(ll i=1;i<n;i++){
        for(ll j=1;j<m;j++){
            arr[i][j] +=(arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1] );
        }
    }

    for(ll i=1;i<m;i++){
        arr[0][i]+=arr[0][i-1];
        ini[0][i]+=ini[0][i-1];
    }

    for(ll i=1;i<n;i++){
        arr[i][0]+=arr[i-1][0];
        ini[i][0]+=ini[i-1][0];
    }


    for(ll i=1;i<n;i++){
        for(ll j=1;j<m;j++){
            arr[i][j] +=(arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1] );
            ini[i][j] +=(ini[i-1][j] + ini[i][j-1] - ini[i-1][j-1] );
        }
    }

    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<m;j++)
        {
            arr[i][j]+=ini[i][j];
        }
    }

    for(ll i=0;i<q;i++)
    {
        ll r1,c1,r2,c2;
        cin>>r1>>c1>>r2>>c2;
        //r1--;c1--;r2--;c2--;
        ll res=arr[r2][c2];
        if(r1>0){
            res-=arr[r1-1][c2];
        }
        if(c1>0){
            res-=arr[r2][c1-1];
        }
        if(r1>0&&c1>0){
            res+=arr[r1-1][c1-1];
        }
        cout<<res<<"\n";
    }
    return 0;
}
