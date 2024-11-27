//区间修改为等差数列
//区间查询
//不开long long 见祖宗
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

const int N = 1e6+10;
using ll = long long ;
int a[N];
int n,q;
struct Node
{
    ll l,r,sum,k,d;
}tr[N*4];
void push_up(int u)
{
    tr[u].sum = tr[u<<1].sum+tr[u<<1|1].sum;
}
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    int l = tr[u].l,r = tr[u].r;
    if(root.d==0)return ;
    int mid = l+r>>1;
    left.d = right.d = root.d;
    left.k = root.k,right.k = root.k+(mid-l+1)*root.d;
    left.sum = (mid - l + 1) * root.k + (mid - l) * (mid - l + 1) / 2 * root.d;
    right.sum = (r - mid) * root.k + (r - mid - 1) * (r - mid) / 2 * root.d + (r - mid) * (mid - l + 1) * root.d;
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
void modify(int u ,int l,int r,int k,int d)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].sum = (tr[u].l+tr[u].r-2*l)*(tr[u].r-tr[u].l+1)/2*d+(tr[u].r-tr[u].l+1)*k;
        tr[u].d = d;
        tr[u].k = (tr[u].l - l) * d + k;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)modify(u<<1,l,r,k,d);
    if(r>mid)modify(u<<1|1,l,r,k,d);
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
    scanf("%lld", &n);
    for(int i = 1;i <= n ; i ++)
    {
        scanf("%lld", &a[i]);
    }
    build(1,1,n);
    ll ans = 0;
    scanf("%lld", &q);
    while(q--)
    {
        
        int id ,t;
        scanf("%lld%lld", &id, &t);
        int now = query(1,id,id);
        if(now<=t)
        {
            int l = id ,r = n;
            while(l<r)
            {
                int mid = l+r+1>>1;
                if(query(1,mid,mid)-(mid-id)<=t) l = mid;
                else r = mid-1;
            }
            ll sum = query(1,id,l);
            modify(1,id,l,t,1);
            ans += (2ll*t+l-id)*1ll*(l-id+1)/2-sum;
        }else 
        {
            int l = 1,r = id;
            while(l<r)
            {
                int mid  = l+r>>1;
                if(query(1,mid,mid)+(id-mid)>=t)r = mid;
                else l = mid+1;
            }
            ll sum = query(1,l,id);
            modify(1,l,id,t-(id-l),1);
            ans+=sum-(2ll*t-(id-l))*1ll*(id-l+1)/2;
        }
        // for(int i = 1;i<=n;i++)
        // {
        //     cout << query(1,i,i) << ' ';
        // }
        // puts("");
    }
    printf("%lld\n",ans);
}