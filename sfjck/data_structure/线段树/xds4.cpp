#include <iostream>
#include <cstring>
#include <algorithm>

#define int long long
const int N = 1e6+10;
using namespace std;

int a[N];
int n,q,m;
struct Node
{
    int l,r,sum;
    int add,mul ;
}tr[N*4];
void push_up(int u)
{
    tr[u].sum = (tr[u<<1].sum+tr[u<<1|1].sum)%m;
}
//在push_down时先传递加法和先传递乘法有区别 区别在于结果的精度
//先传递加法 会导致乘法时乘数变成小数
//先传递乘法 就没有精度问题
//注意在改变mul时add 也要改变
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    left.sum = (left.sum*root.mul+root.add*(left.r-left.l+1)%m)%m;
    right.sum = (right.sum*root.mul+root.add*(right.r-right.l+1)%m)%m;
    left.mul = (left.mul*root.mul)%m,right.mul = (right.mul*root.mul)%m;
    left.add = (left.add*root.mul+root.add)%m,right.add = (right.add*root.mul+root.add)%m;
    root.add = 0;
    root.mul = 1;
    
}
void build(int u,int l,int r)
{
    tr[u]={l,r,a[l],0,1};
    if(l==r)return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
    tr[u].sum%=m;
}
void add(int u ,int l,int r,int d)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].sum = (tr[u].sum+(tr[u].r-tr[u].l+1)*d%m)%m;
        tr[u].add = (tr[u].add+d)%m;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)add(u<<1,l,r,d);
    if(r>mid)add(u<<1|1,l,r,d);
    push_up(u);
}
void mul(int u,int l,int r,int x)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].sum = tr[u].sum*x%m;
        tr[u].mul = tr[u].mul*x%m;//注意是要乘
        tr[u].add = tr[u].add*x%m;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)mul(u<<1,l,r,x);
    if(r>mid)mul(u<<1|1,l,r,x);
    push_up(u);
}
int query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sum%m;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    int ans = 0;
    if(l<=mid)ans = (ans+query(u<<1,l,r))%m;
    if(r>mid)ans = (ans+query(u<<1|1,l,r))%m;
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q >> m;
    for(int i = 1;i<=n;i++)
    {
        cin >> a[i];
    }
    build(1,1,n);
    while(q--)
    {
        int op;
        cin >> op;
        int x,y,k;
        cin >> x >> y;
        if(op==1)
        {
            cin >> k ;
            mul(1,x,y,k);
        }else if(op==2)
        {
            cin >> k;
            add(1,x,y,k);
        }else cout << query(1,x,y) << endl;
    }
}