#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int N = 1e6;
const int mod = 1e9+7;

int a[N];
struct Node
{
    int l,r,x,sum,sum2;
}tr[N*4];
int qmi(int a,int k,int p)
{
    int res = 1;
    while(k)
    {
        if(k&1)res = res*a%p;
        a=a*a%p;
        k>>=1;
    }
    return res;
}
void push_up(int u)
{
    tr[u].sum = (tr[u<<1].sum%mod+tr[u<<1|1].sum%mod)%mod;
    tr[u].sum2 = (tr[u<<1].sum2%mod + tr[u<<1|1].sum2%mod)%mod;
}
void build(int u ,int l ,int r)
{
    tr[u]={l,r,a[l]%mod,a[l]%mod,a[l]*a[l]%mod};
    if(l==r)return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int x ,int y)
{
    if(tr[u].l == tr[u].r)
    {
        tr[u].x = y%mod;
        tr[u].sum = y%mod;
        tr[u].sum2 = y*y%mod;
        return ;
    }
    int mid = tr[u].l+tr[u].r>>1;
    if(x<=mid)modify(u<<1,x,y);
    else modify(u<<1|1,x,y);
    push_up(u);
}
int querysum(int u ,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sum%mod;
    }
    int mid = tr[u].l+tr[u].r>>1;
    int ans  = 0 ;
    if(l<=mid)ans = querysum(u<<1,l,r)%mod;
    if(r>mid)ans = (ans+querysum(u<<1|1,l,r))%mod;
    return ans;
}
int querysum2(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sum2%mod;
    }
    int mid = tr[u].l+tr[u].r>>1;
    int ans  = 0 ;
    if(l<=mid)ans = querysum2(u<<1,l,r)%mod;
    if(r>mid)ans = (ans+querysum2(u<<1|1,l,r))%mod;
    return ans;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m ;
    for(int i = 1;i<=n;i++)
    {
        cin >> a[i];
    }
    build(1,1,n);
    while (m -- )
    {
        int c,x,y;
        cin >> c >> x >> y;
        if(c==1)
        {
            modify(1,x,y);
        }else 
        {
            int l = x ,r = y;
            int sum = querysum(1,l,r)%mod;
            int sum2 = querysum2(1,l,r)%mod;
            int len = r-l+1;
            int avg = sum*qmi(len,mod-2,mod)%mod;
            int len1 = qmi(len,mod-2,mod);
            int ans = len1*(sum2-2*avg*sum%mod)+avg*avg%mod;
            cout << (ans%mod+mod)%mod << endl;
        }
    }
}