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

int cmap(char c) { return int(c)-32; }

vvi res;

constexpr int K = 96;
struct Vertex {
    std::array<int, K> next;
    bool terminal = false;
    vi terminal_indices;
    int p = -1;
    char pch;
    int depth = 0;
    int link = 0;
    int next_terminal = 0;
    std::array<int, K> go;

    Vertex(int p, char ch, int depth) : p(p), pch(ch), depth(depth) {
        std::fill(next.begin(), next.end(), 0);
        std::fill(go.begin(), go.end(), 0);
    }
};

class AhoCorasick {
public:
    AhoCorasick() : t(1, {-1, '$', 0}) {}

    void add_string(std::string const& s, int idx) {
        int v = 0;
        for (char ch : s) {
            int c = cmap(ch);
            if (!t[v].next[c]) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch, t[v].depth + 1);
            }
            v = t[v].next[c];
        }
        t[v].terminal = true;
        t[v].terminal_indices.pb(idx);
    }

    void push_links() {
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            auto& cur = t[v];
            auto& link = t[cur.link];
            q.pop();
            cur.next_terminal = link.terminal ? cur.link : link.next_terminal;

            for (int c = 0; c < K; c++) {
                if (cur.next[c]) {
                    t[cur.next[c]].link = v ? link.next[c] : 0;
                    q.push(cur.next[c]);
                } else {
                    cur.next[c] = link.next[c];
                }
            }
        }
    }

    int transition(int idx, char c) {
        return t[idx].next[cmap(c)];
    }

    Vertex const& getInfo(int idx) {
        return t[idx];
    }

private:
    std::vector<Vertex> t;
};

int main()
{
    IOS
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */
    ll ntc=1;
    cin>>ntc;
    rep(tc,1,ntc+1)
    {
        //cout<<"Case #"<<tc<<": ";
        string text;
        cin>>text;
        int n;
        cin>>n;
        AhoCorasick aho;
        for(int i=0;i<n;i++)
        {
            string str;
            cin>>str;
            aho.add_string(str,i);
        }
        bool pres[n];
        memset(pres,false,sizeof(pres));
        int cur=0;
        for(int i=0;i<text.length();i++)
        {
            cur=aho.transition(cur,text[i]);
            int temp=cur;
            while(temp){
                if(aho.getInfo(temp).terminal){
                    for(auto u:aho.getInfo(temp).terminal_indices){
                        pres[u]=true;
                    }
                }
                temp=aho.getInfo(temp).next_terminal;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(pres[i])
                cout<<"y\n";
            else cout<<"n\n";
        }
    }
    return 0;
}
