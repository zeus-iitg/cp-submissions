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

#define o_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
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

vll a;

int main()
{
    IOS
    ll n,q,u;
    cin>>n>>q>>u;
    a.resize(n);
    for(ll i=0;i<n;i++)
    {
        cin>>a[i];
    }

    ll block_size = 2000;
    ll number_of_blocks = (n + block_size - 1) / block_size;
    o_set m[number_of_blocks];
    for (ll i=0; i<n; ++i)
        m[i / block_size].insert(a[i]);

    for (ll itr=0;itr<q;itr++) {
        ll l, r, v, p;
        cin>>l>>r>>v>>p;
        l--;r--;p--;
        ll block_left=l/ block_size;
        ll block_right= r/ block_size;
        ll noe=0;
        if(block_left==block_right){
            for(ll i=l;i<=r;i++)
            {
                if(a[i]<v)
                    noe++;
            }
        }
        else{
            for(ll i=l;i/block_size==l/block_size;i++)
            {
                if(a[i]<v)
                    noe++;
            }
            for(ll i=r;i/block_size==r/block_size;i--)
            {
                if(a[i]<v)
                    noe++;
            }
            for(ll block=block_left+1;block<block_right;block++){
                noe=noe+m[block].order_of_key(v);
            }
            ll new_val=((ll)u*(ll)noe)/(ll)(r-l+1);
            if(a[p]!=new_val){
                ll block=p/block_size;
                ll old_val=a[p];
                m[block].erase(m[block].find_by_order(m[block].order_of_key(old_val)));
                a[p]=new_val;
                m[block].insert(new_val);
            }
        }
    }
    for(ll i=0;i<n;i++)
    {
        cout<<a[i]<<"\n";
    }
    return 0;
}
