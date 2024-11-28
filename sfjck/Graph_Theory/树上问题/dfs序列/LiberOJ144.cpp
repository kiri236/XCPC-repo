#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int N = 1e6+10,M=2*N;
int v[N];
int dfn[N],now;
int dfp[N];
int n,m,r;
int h[N], e[M], ne[M], idx;
int sz[N];
struct Node
{
    int l,r;
    int sum;
}tr[N*4];
void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
void dfs(int u,int fa)
{
    dfn[u] = ++now;
    dfp[dfn[u]] = u;
    for(int i = h[u]; ~ i ;i = ne[i])
    {
        int j = e[i];
        if(j==fa)continue;
        dfs(j,u);
    }
}
void dfs_sz(int u ,int fa)
{
    sz[u]++;
    for(int i = h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(j==fa)continue;
        dfs_sz(j,u);
        sz[u] += sz[j];
    }
}
void push_up(int u)
{
    tr[u].sum = tr[u<<1].sum+tr[u<<1|1].sum;
}
void build(int u,int l,int r)
{
    tr[u] = {l,r,v[dfp[r]]};
    if(l==r)return ;
    int mid = l + r >> 1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int x,int v)
{
    if(tr[u].l==tr[u].r)
    {
        tr[u].sum += v;
        return ;
    }
    int mid = tr[u].l+tr[u].r>>1;
    if(x<=mid)modify(u<<1,x,v);
    if(x>mid)modify(u<<1|1,x,v);
    push_up(u);
}
int query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sum;
    }
    int mid = tr[u].l+tr[u].r>>1;
    int ans = 0;
    if(l<=mid)ans += query(u<<1,l,r);
    if(r>mid)ans += query(u<<1|1,l,r);
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> r;
    memset(h, -1, sizeof h);
    for(int i = 1;  i<= n ; i ++)
    {
        cin >> v[i];
    }
    for(int i = 1 ; i <n ; i ++)
    {
        int u,v;
        cin >> u >> v;
        add(u,v);
        add(v,u);
    }
    dfs(r,0);
    dfs_sz(r,0);
    build(1,1,n);
    while (m -- )
    {
        int op;
        cin >> op;
        int a;
        cin >> a;
        if(op==1)
        {
            int x;
            cin >> x;
            modify(1,dfn[a],x);
            //cout << query(1,dfn[a],dfn[a]) << endl;
        }else 
        {
            cout << query(1,dfn[a],dfn[a]+sz[a]-1) << endl;
        }
    }
}