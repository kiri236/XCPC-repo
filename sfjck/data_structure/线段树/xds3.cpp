//区间加上等差数列，区间查询
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
using ll = long long ;
int n,m;
int a[N];
struct Node
{
    ll l,r,w,k,d;
    bool flag;
}tr[N*4];
void push_up(int u)
{
    tr[u].w = tr[u<<1].w+tr[u<<1|1].w;
}
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    if(root.flag)
    {
        left.flag = 1;
        left.k += root.k;
        left.d += root.d;
        right.k += root.k+(right.l-left.l)*root.d;
        right.d += root.d;
        right.flag = 1;
    }
    root.flag = 0;
    root.k = root.d = 0;
}
void build(int u,int l,int r)
{
    tr[u]={l,r,a[l]};
    if(l==r)return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int l,int r,int k,int d)
{
    int rl = tr[u].l,rr = tr[u].r;
    if(rl>=l&&rr<=r)
    {
        tr[u].flag = 1;
        tr[u].k += k+(rl-l)*d;
        tr[u].d += d;
        return ;
    }
    push_down(u);
    int mid = rl+rr>>1;
    if(l<=mid)modify(u<<1,l,r,k,d);
    if(r>mid)modify(u<<1|1,l,r,k,d);
    push_up(u);
}
ll query(int u,int l,int r)
{
    int l1=tr[u].l,r1=tr[u].r;
	if(l1==r1){
		tr[u].w+=tr[u].k;
		tr[u].k=0;tr[u].d=0;
		return tr[u].w;
	}
	push_down(u);
	int mid=(l1+r1)>>1;
	ll ans = 0 ;
	if(l<=mid) ans += query(u<<1,l,r);
	if(r>mid) ans += query(u<<1|1,l,r);
	return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n ; i ++)
    {
        scanf("%d", &a[i]);
    }
    build(1,1,n);
    while (m -- )
    {
        int op;
        scanf("%d", &op);
        if(op==1)
        {
            int l,r,k,d;
            scanf("%d%d", &l, &r);
            scanf("%d%d", &k, &d);
            modify(1,l,r,k,d);
        }else 
        {
            int l,r;
            scanf("%d%d", &l, &r);
            cout << query(1,l,r) << endl;
        }
    }
}