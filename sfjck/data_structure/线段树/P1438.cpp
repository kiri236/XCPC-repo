//luogu P1438
//区间加上等差数列
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
}
ll query(int u,int p)
{
    int l=tr[u].l,r=tr[u].r;
	if(l==r){
		tr[u].w+=tr[u].k;
		tr[u].k=0;tr[u].d=0;
		return tr[u].w;
	}
	push_down(u);
	int mid=(l+r)>>1;
	if(p<=mid) return query(u<<1,p);
	else return query(u<<1|1,p); 
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
            int p;
            scanf("%d", &p);
            cout << query(1,p) << endl;
        }
    }
}