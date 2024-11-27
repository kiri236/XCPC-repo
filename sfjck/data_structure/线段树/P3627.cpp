//区间加 区间sin和
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define int long long
using namespace std;
const int N = 1e6;
int a[N];
int n;

struct Node
{
    int l,r;
    double sinsum,cossum;
    int lazy;
}tr[N<<2];
void push_up(int u)
{
    tr[u].sinsum = tr[u<<1].sinsum+tr[u<<1|1].sinsum;
    tr[u].cossum = tr[u<<1].cossum+tr[u<<1|1].cossum;
}
void push_down(int u)
{
    auto &root = tr[u],&left = tr[u<<1],&right = tr[u<<1|1];
    if(root.lazy)
    {
        double sinlazy = sin(root.lazy),coslazy = cos(root.lazy);
        double lsinsum = left.sinsum,lcossum = left.cossum;
        double rsinsum = right.sinsum,rcossum = right.cossum;
        left.sinsum = lsinsum*coslazy+lcossum*sinlazy;
        right.sinsum = rsinsum*coslazy+rcossum*sinlazy;
        left.cossum = lcossum*coslazy-lsinsum*sinlazy;
        right.cossum = rcossum*coslazy-rsinsum*sinlazy;
        left.lazy += root.lazy;
        right.lazy += root.lazy;
        root.lazy = 0 ;
    }
}
void build(int u,int l,int r)
{
    tr[u] = {l,r,sin(a[r]),cos(a[r]),0};
    if(l==r)return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
void modify(int u,int l,int r,int v)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        double sinsum = tr[u].sinsum;
        double cossum = tr[u].cossum;
        double sinv = sin(v);
        double cosv = cos(v);
        tr[u].sinsum = sinsum*cosv+sinv*cossum;
        tr[u].cossum = cossum*cosv-sinv*sinsum;
        tr[u].lazy += v;
        return ;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    if(l<=mid)modify(u<<1,l,r,v);
    if(r>mid)modify(u<<1|1,l,r,v);
    push_up(u);
}
double query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u].sinsum;
    }
    push_down(u);
    int mid = tr[u].l+tr[u].r>>1;
    double sum = 0 ;
    if(l<=mid)sum+=query(u<<1,l,r);
    if(r>mid)sum+=query(u<<1|1,l,r);
    return sum;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n ;
    for(int i = 1;  i <= n ; i  ++)
    {
        cin >> a[i];
    }
    build(1,1,n);
    int q;
    cin >> q;
    cout << fixed << setprecision(1);
    while(q--)
    {
        int op;
        cin >> op;
        int l,r;
        cin >> l >> r;
        if(op==1)
        {
            int v;
            cin >> v ;
            modify(1,l,r,v);
        }else 
        {
            cout << query(1,l,r) << '\n';
        }
    }
}