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

struct node{
    struct node* next[2];
    bool endpoint;
    int ending_index;
};

struct node* create_node(){
    struct node* temp=new struct node;
    for(int i=0;i<2;i++)
    {
        temp->next[i]=nullptr;
    }
    temp->endpoint=false;
    return temp;
}

vvi subtract;

void process(string &s, struct node* root, int idx){
    struct node *cur=root;
    for(int i=0;i<s.length();i++)
    {
        if(cur->endpoint){
            subtract[cur->ending_index].pb(idx);
        }
        int num=s[i]-'0';
        if(cur->next[num]!=nullptr){
            cur=cur->next[num];
        }
        else{
            cur->next[num]=create_node();
            cur=cur->next[num];
        }
    }
    cur->endpoint=true;
    cur->ending_index=idx;
}

bool compare(string &a, string &b){
    return a.length()<b.length();
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
    while(1)
    {
    	//cout<<"Case #"<<tc<<": ";
        struct node *root=create_node();
        ll n,m;
        cin>>n>>m;
        if(n==0&&m==0){
            exit(0);
        }
        set<string> st;
        for(int i=0;i<n;i++)
        {
            string str;
            cin>>str;
            str.pop_back();
            st.insert(str);
        }
        st.insert("");
        n=st.size();
        vt(string) v;
        for(string s:st){
            v.pb(s);
        }
        subtract.assign(n,vi());
        sort(all(v),compare);
        map<string,int> mapp;
        for(int i=0;i<n;i++)
        {
            mapp[v[i]]=i;
        }
        for(int i=0;i<n;i++)
        {
            if(v[i].length()<=m)
                process(v[i],root,i);
        }
        unsigned ll res[n];
        for(int i=n-1;i>=0;i--)
        {
            if(v[i].length()>m){
                res[i]=0;
            }
            else{
                ll exponent=m-v[i].length();
                if(exponent<=62){
                    unsigned ll ini=(ll)1<<exponent;
                    for(int u:subtract[i]){
                        ini-=res[u];
                    }
                    res[i]=ini;
                }
                else{
                    unsigned ll ini=(ll)1<<62;
                    for(int u:subtract[i]){
                        ini-=res[u];
                    }
                    unsigned ll add=(ll)1<<62;
                    if(exponent==63){
                        ini+=add;
                    }
                    else{
                        ini+=add;
                        ini+=add;
                        ini+=add;
                    }
                    res[i]=ini;
                }
            }
        }
        int q;
        cin>>q;
        while(q--){
            string str;
            cin>>str;
            str.pop_back();
            cout<<res[mapp[str]]<<"\n";
        }
        cout<<"\n";
    }
    return 0;
}
