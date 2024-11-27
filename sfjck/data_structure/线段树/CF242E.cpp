#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n , q;
const int N = 1e5+10;
using ll = long long ;
int a[N];
struct Node
{
    int l,r;
    ll sum ;
    int lazy;
    int s[32];//0~32从低到高
}tr[N*4];
void push_up(int u)
{
    tr[u].sum = tr[u<<1].sum+tr[u<<1|1].sum;
    for(int i = 0;i<32;i++)
    {
        tr[u].s[i]=tr[u<<1].s[i]+tr[u<<1|1].s[i];
    }
}
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    if(root.lazy)
    {
        int tmp = root.lazy;
        int dg = 0;
        while(tmp)
        {
            if(tmp&1)
            {
                right.s[dg]=(right.r-right.l+1)-right.s[dg];
                left.s[dg]=(left.r-left.l+1)-left.s[dg];
            }
            dg++;
            tmp>>=1;
        }
        ll sum1 = 0 ,sum2 = 0;
        for(int i = 0 ; i<32;i++)
        {
            sum1 += left.s[i]*(1ll<<i);
            sum2 += right.s[i]*(1ll<<i);
        }
        left.sum = sum1;
        right.sum = sum2;
        left.lazy ^= root.lazy,right.lazy ^= root.lazy;
        root.lazy = 0;
    }
}
void build(int u,int l,int r)
{
    tr[u]={l,r};
    if(l==r)
    {
        tr[u].sum = a[l];
        int tmp = a[l];
        int dg = 0;
        while(tmp)
        {
            tr[u].s[dg]+=tmp&1;
            dg++;
            tmp>>=1;
        }
        return ;
    }
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int l,int r,int x)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].lazy ^= x;
        int dg = 0;
        while(x)
        {
            if(x&1)
            {
                tr[u].s[dg]=(tr[u].r-tr[u].l+1)-tr[u].s[dg];
            }
            dg++;
            x>>=1;
        }
        ll sum = 0;
        for(int i = 0;i<32;i++)
        {
            //cout << tr[u].s[i] << ' ';
            sum += tr[u].s[i]*(1ll<<i);
        }
        tr[u].sum = sum;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)modify(u<<1,l,r,x);
    if(r>mid)modify(u<<1|1,l,r,x);
    push_up(u);
}
ll query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sum;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    ll ans = 0;
    if(l<=mid)ans+=query(u<<1,l,r);
    if(r>mid)ans+=query(u<<1|1,l,r);
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 1;i<=n;i++)cin >> a[i];
    cin >> q;
    build(1,1,n);
    while(q--)
    {
        int t;
        cin >> t;
        int l,r;
        cin >> l >> r;
        if(t==1)
        {
            cout << query(1,l,r) << endl;
        }else 
        {
            int x;
            cin >> x;
            modify(1,l,r,x);
            //cout << endl;
        }
    }
}