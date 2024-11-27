//区间修改为某个值,区间查询
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
int a[N];
struct Node
{
    int l,r;
    long long sum,lazy;
    bool change;//记录是否被修改
}tr[N*4];
//先pushdown再pushup,涉及到修改的都要pushup,从大区间到小区间就要pushdown
void push_up(int u)
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void push_down(int u)
{
    if(tr[u].change)
    {
        tr[u<<1].lazy = tr[u].lazy;
        tr[u<<1].sum = tr[u].lazy*1ll*(tr[u<<1].r-tr[u<<1].l+1);
        tr[u<<1].change = tr[u].change;
        tr[u<<1|1].lazy = tr[u].lazy;
        tr[u<<1|1].sum = tr[u].lazy*1ll*(tr[u<<1|1].r-tr[u<<1|1].l+1);
        tr[u<<1|1].change = tr[u].change;
        tr[u].change=0;
    }
}
void build(int u,int l,int r)
{
    tr[u]={l,r,a[r],0};
    if(l==r)
    {
        return;
    }
    int mid = l+r>>1;
    build(u<<1,l,mid);//建左子树
    build(u<<1|1,mid+1,r);//建右子树
    push_up(u);
}
void modify(int u ,int l,int r,int d)//将以u为根的树中[l,r]上的数更改为d
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].sum = (tr[u].r-tr[u].l+1)*1ll*d;//修改区间和
        tr[u].lazy = d;//更新当前节点的lazy tag
        tr[u].change = 1;
    }else //当前区间包含了目标区间
    {
        push_down(u);//大区间要pushdown
        int mid = tr[u].l+tr[u].r>>1;
        if(l<=mid)modify(u<<1,l,r,d);
        if(r>mid)modify(u<<1|1,l,r,d);
        push_up(u);//修改完记得要pushup
    }
}
long long query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum;
    push_down(u);//只要区间大就要pushdown
    int mid = tr[u].l+tr[u].r>>1;
    long long sum = 0 ;
    if(l<=mid)sum+=query(u<<1,l,r);
    if(r>mid)sum+=query(u<<1|1,l,r);
    return sum;
}
int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
    }
    build(1,1,n);
    while (m -- )
    {
        char op[2];
        scanf("%s", op);
        int l,r;
        scanf("%d%d", &l, &r);
        if(op[0]=='C')
        {
            int d;
            scanf("%d", &d);
            modify(1,l,r,d);
            for(int i = 1;i<=n;i++)
            {
                cout << query(1,i,i) << ' ';
            }
            puts("");
        }else 
        {
            cout << query(1,l,r) << endl;
        }
    }
}