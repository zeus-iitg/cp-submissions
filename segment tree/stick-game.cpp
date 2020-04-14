//link to problem
//https://toph.co/p/stick-game

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

#define MAXN 200000

ll n;

ll t[4*MAXN],lazy[4*MAXN];

void push(ll v,ll tl,ll tm,ll tr) {
    t[v*2] += (ll)(tm-tl+1)*lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += (ll)(tr-tm)*lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(ll v, ll tl, ll tr, ll l, ll r, ll addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v] += (ll)(tr-tl+1)*addend;
        lazy[v] += addend;
    } else {
        ll tm = (tl + tr) / 2;
        push(v,tl,tm,tr);
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = t[v*2]+t[v*2+1];
    }
}

ll query(ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r)
        return 0;
    if (l <= tl && tr <= r)
        return t[v];
    ll tm = (tl + tr) / 2;
    push(v,tl,tm,tr);
    ll res=query(v*2, tl, tm, l, min(r, tm))+query(v*2+1, tm+1, tr, max(l, tm+1), r);
    return res;
}

int main()
{
    IOS
    memset(t,0,sizeof(t));
    memset(lazy,0,sizeof(lazy));
    ll k;
    cin>>n>>k;
    set<pair<pll,ll>> s;
    for(ll i=0;i<n;i++)
    {
        s.insert(mp(mp(i,i),i+1));
    }
    for(ll i=0;i<k;i++)
    {
        ll type;
        cin>>type;
        if(type==1){
            ll l,r;
            ll a;
            cin>>l>>r>>a;
            l--;r--;
            set<pair<pll,ll>>::iterator itr=s.lower_bound(mp(mp(l,INT_MIN),INT_MIN));
            bool flag_left=false;
            bool flag_right=false;
            pair<pll,ll> to_push,push2;
            if(itr==s.end()||itr->first.first>l){
                itr--;
                to_push= *itr;
                flag_left=true;
                to_push.first.second=l-1;
            }
            update(1,0,n-1,max(l,itr->first.first),min(r,itr->first.second),abs(a-itr->second));
            if(itr->first.second<r)
                itr=s.erase(itr);
            while(itr!=s.end()){
                if(itr->first.second>=r){
                    if(itr->first.second>r){
                        push2=*itr;
                        flag_right=true;
                        push2.first.first=r+1;
                    }
                    if(itr->first.first>l){
                        update(1,0,n-1,max(l,itr->first.first),min(r,itr->first.second),abs(a-itr->second));
                    }
                    itr=s.erase(itr);
                    break;
                }
                update(1,0,n-1,max(l,itr->first.first),min(r,itr->first.second),abs(a-itr->second));
                itr=s.erase(itr);
            }
            s.insert(mp(mp(l,r),a));
            if(flag_left){
                s.insert(to_push);
            }
            if(flag_right){
                s.insert(push2);
            }
        }
        else{
            ll l,r;
            cin>>l>>r;
            l--;r--;
            cout<<query(1,0,n-1,l,r)<<"\n";
        }
    }
    return 0;
}
