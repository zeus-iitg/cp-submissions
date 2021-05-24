# Sack (DSU on tree) - Explanation
#### based on Codeforces blog at [Link](https://codeforces.com/blog/entry/44351) by [Arpa](https://codeforces.com/profile/Arpa)
With DSU on tree, we can answer queries of this type:

> How many vertices in the subtree of vertex v have some property in O(nlog n) time (for all queries)?

For example:

> Given a tree, in which every vertex has a color. How many vertices in subtree of vertex v are colored with color c?

Let's see how we can solve this problem and similar problems.</br>
First, we have to calculate the size of the subtree of every vertex.</br>
It can be done with simple dfs:
```cpp
int sz[maxn];
void getsz(int v, int p){
    sz[v] = 1;  // every vertex has itself in its subtree
    for(auto u : g[v])
        if(u != p){
            getsz(u, v);
            sz[v] += sz[u]; // add size of child u to its parent(v)
        }
}
```
Now we have the size of the subtree of vertex v in sz[v].</br>
The naive method for solving this problem is this code.</br>
(Since we perform dfs for every node over its subtree, the time complexity of this code is O(n<sup>2</sup>))
```cpp
int cnt[maxn];
// here a third parameter x is also taken
// this enables us to add details of the subtree of a node (x = 1)
// as well as to remove details of the subtree of a node (x = -1)
void add(int v, int p, int x){
    cnt[col[v]] += x;
    for(auto u: g[v])
        if(u != p)
            add(u, v, x)
}
void dfs(int v, int p){
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    add(v, p, -1);
    for(auto u : g[v])
        if(u != p)
            dfs(u, v);
}
```
Now, how to improve it? There are several styles of coding for this technique.

## 1. easy to code but O(nlog<sup>2</sup>n).
```cpp
map<int, int> *cnt[maxn];
void dfs(int v, int p){
    // bigChild stores child with biggest subtree size
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p){
           dfs(u, v);
           if(sz[u] > mx)
               mx = sz[u], bigChild = u;
       }
    // if current node has a bigChild, we set the pointer of map of current node
    // equal to the pointer of map of bigChild
    // if current node has no children, we set the pointer of map of current node
    // to a new map
    if(bigChild != -1)
        cnt[v] = cnt[bigChild];
    else
        cnt[v] = new map<int, int> ();
    // increment the count of color of vertex v
    (*cnt[v])[col[v]] ++;
    // merge maps of all small children to the map of current node
    for(auto u : g[v])
       if(u != p && u != bigChild){
           // iterate over map of small child
           // map contains (key, value) pairs where
           // key denotes color
           // value denotes frequency
           for(auto x : *cnt[u])
               // increment count of color denoted by x.first
               // by its frequency in small child (x.second)
               (*cnt[v])[x.first] += x.second;
       }
    //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.

}
```
## 2. easy to code and O(nlog n).
```cpp
vector<int> *vec[maxn];
int cnt[maxn];
// keep denotes whether we want to keep the data of the subtree rooted at v
// inside cnt after the function call ends
// first, we solve the problem for each small child without storing their data
// in cnt, i.e., cnt resets after each function call to small child ends
// making sure each small child is solved independently
// bigChild is also solved independently since cnt is reset before dfs is called
// for bigChild. The only difference is that we keep the data of bigChild in cnt
// and merge data of every small child in cnt in the next step to get data for
// subtree rooted at v
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
           mx = sz[u], bigChild = u;
    // first solve all small children without storing their data
    for(auto u : g[v])
       if(u != p && u != bigChild)
           dfs(u, v, 0);
    // if bigChild exists, solve for bigChild but do not remove its data from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int> ();
    // add data of node v
    vec[v]->push_back(v);
    cnt[col[v]]++;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           // *vec[u] contains all nodes in subtree of small child u
           // add color of all nodes to cnt
           for(auto x : *vec[u]){
               cnt[col[x]]++;
               vec[v] -> push_back(x);
           }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    if(keep == 0)
        for(auto u : *vec[v])
            cnt[col[u]]--;
}
```
## 3. heavy-light decomposition style O(nlog n).
```cpp
int cnt[maxn];
bool big[maxn];
// add() adds (x = 1) or removes (x = -1) the data of current node
// and of its small children from cnt
void add(int v, int p, int x){
    cnt[col[v]] += x;
    for(auto u: g[v])
        if(u != p && !big[u])
            add(u, v, x)
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    // add data of v and its small children to cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    // in order to remove data of entire subtree, we will have to set
    // big[bigChild] to zero indicating that it is not a bigChild
    // Now, add() will remove data of bigChild as well
    // If this had not been done, data of only v and small children would be
    // removed leaving the data of bigChild in cnt and hence the task of removing
    // data of entire subtree of v would have failed
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(v, p, -1);
}
```
## 4. My invented style O(nlog n).
This implementation for "DSU on tree" technique is new and invented by me. This implementation is easier to code than others.</br>
Let **st[v]** be the dfs starting time of vertex v, **ft[v]** be it's dfs finishing time and **ver[time]** is the vertex whose starting time is equal to time.
```cpp
int cnt[maxn];
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
    for(auto u : g[v])
    	if(u != p && u != bigChild)
    	    // all nodes with starting time in the range [st[u], ft[u])
    	    // belong to the subtree of small child u
    	    // increment their color in cnt
    	    for(int p = st[u]; p < ft[u]; p++)
    		    cnt[col[ver[p]]]++;
    cnt[col[v]]++;
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(keep == 0)
        // removing subtree rooted at v is equivalent to removing all
        // vertices with starting time in the range [st[v], ft[v])
        for(int p = st[v]; p < ft[v]; p++)
	        cnt[col[ver[p]]]--;
}
```
But why is it O(nlog n)? You know why DSU has O(qlog n) time (for q queries). The code uses the same method: Merge smaller to larger.</br>
If you have heard heavy-light decomposition, you will see that function add will go through light edges only. Because of this, code works in O(nlog n) time.</br>
Any problems of this type can be solved with same dfs function and just differs in add function.

## Problems that can be solved with this technique:
Kindly refer to the original blog at [https://codeforces.com/blog/entry/44351](https://codeforces.com/blog/entry/44351) for problems related to the topic
