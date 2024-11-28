#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using ll = long long ;
const int N = 4e5+100,M=2*N;
int h[N], e[M], ne[M], idx;
int c[N];
int sz[N];
int dfn[N],dfp[N],now;
void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
void dfs_time(int u,int fa)
{
    dfn[u] = ++now;
    dfp[now] = u;
    for(int i = h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(j==fa)continue;
        dfs_time(j,u);
    }
}
void dfs_sz(int u,int fa)
{
    sz[u]++;
    for(int i = h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(j==fa)continue;
        dfs_sz(j,u);
        sz[u]+=sz[j];
    }
}
struct Node
{
    int l,r;
    ll cs;
    int lazy;
}tr[N*4];
void push_up(int u)
{
    tr[u].cs = tr[u<<1].cs|tr[u<<1|1].cs;
}
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    if(root.lazy)
    {
        left.cs = 1ll<<root.lazy;
        right.cs = 1ll<<root.lazy;
        left.lazy = right.lazy = root.lazy;
        root.lazy = 0 ;
    }
}
void build(int u,int l,int r)
{
    tr[u] = {l,r,1ll<<c[dfp[r]],0};
    if(l==r)return ;
    int mid = l+r >> 1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int l ,int r,int d)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].cs = 1ll<<d;
        tr[u].lazy = d;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)modify(u<<1,l,r,d);
    if(r>mid)modify(u<<1|1,l,r,d);
    push_up(u);
}
ll query(int u,int l ,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].cs;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    ll ans = 0;
    if(l<=mid)
    {
        ans |= query(u<<1,l,r);
    }
    if(r>mid)
    {
        ans |= query(u<<1|1,l,r);
    }
    return ans;
}
int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for(int i = 1;  i <= n ; i ++)
    {
        scanf("%d", &c[i]);
    }
    for(int i = 1 ; i<n ; i ++)
    {
        int u,v;
        scanf("%d%d", &u, &v);
        add(u,v);
        add(v,u);
    }
    dfs_time(1,0);
    dfs_sz(1,0);
    build(1,1,n);
    while (m -- )
    {
        int op;
        scanf("%d", &op);
        int v ;
        scanf("%d", &v);
        if(op==1)
        {
            int x;
            scanf("%d", &x);
            modify(1,dfn[v],dfn[v]+sz[v]-1,x);
        }else 
        {
            ll ans = query(1,dfn[v],dfn[v]+sz[v]-1);
            int cnt = 0;
            while(ans)
            {
                cnt += ans&1;
                ans>>=1;
            }
            cout << cnt << endl;
        }
    }
}