#include<bits/stdc++.h>
using namespace std;
const int N  = 1e6;
int n,m;
double a[N];
struct Node
{
        int l,r;
        double sum,sum2;
        double lazy;
}tr[N*4];
void push_up(int u)
{
        tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
        tr[u].sum2 =  tr[u<<1].sum2 + tr[u<<1|1].sum2;
}
void push_down(int u)
{
        auto &root = tr[u],&left =  tr[u<<1], &right = tr[u<<1|1];
        if(root.lazy)
        {
                right.lazy += root.lazy,left.lazy += root.lazy;
                left.sum2 += (left.r-left.l+1)*root.lazy*root.lazy + 2*root.lazy*left.sum;
                right.sum2 += (right.r-right.l +1)*root.lazy*root.lazy + 2*root.lazy*right.sum;
                left.sum += (left.r-left.l+1)*root.lazy,right.sum += (right.r - right.l+1)*root.lazy;
                root.lazy = 0;
        }
}
void build(int u,int l,int r)
{
        tr[u]={l,r,a[r],a[r]*a[r],0};
        if(l==r)return ;
        int mid = l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        push_up(u);
}
void modify(int u,int l,int r,double k)
{
        if(tr[u].l>=l&&tr[u].r<=r)
        {
                double sum = tr[u].sum;
                tr[u].sum += (tr[u].r-tr[u].l+1)*k;
                tr[u].sum2 += (tr[u].r-tr[u].l+1)*k*k + 2*sum*k;
                tr[u].lazy += k;
                return ;
        }
        push_down(u);
        int mid = tr[u].l+tr[u].r>>1;
        if(l<=mid)modify(u<<1,l,r,k);
        if(r>mid)modify(u<<1|1,l,r,k);
        push_up(u);
}
double querysum(int u,int l,int r)
{
        if(tr[u].l>=l&&tr[u].r<=r)
        {
                return tr[u].sum;
        }
        push_down(u);
        int mid = tr[u].l+tr[u].r>>1;
        double ans = 0;
        if(l<=mid)
        {
                ans += querysum(u<<1,l,r);
        }
        if(r>mid)
        {
                ans += querysum(u<<1|1,l,r);
        }
        return ans;
}

double querysum2(int u,int l,int r)
{
        if(tr[u].l>=l&&tr[u].r<=r)
        {
                return tr[u].sum2;
        }
        push_down(u);
        int mid = tr[u].l+tr[u].r>>1;
        double ans = 0;
         if(l<=mid)
        {
                ans += querysum2(u<<1,l,r);
        }
        if(r>mid)
        {
                ans += querysum2(u<<1|1,l,r);
        }
        return ans;
}
signed main()
{
        ios::sync_with_stdio(false);
        cin >> n >> m;
        for(int i = 1;i<=n;i++)
        {
                cin >> a[i];
        }
        cout << fixed << setprecision(4);
        build(1,1,n);
        while(m--)
        {
                int op;
                cin >> op;
                int x,y;
                cin >> x >> y;
                //cout << x << ' ' << y << endl;
                if(op==1)
                {
                        double k;
                        cin >> k;
                        //cout << x << ' ' << y << " " << k << endl;
                        modify(1,x,y,k);
                        // for(int i = 1;i<=n;i++)
                        // {
                        //     cout << querysum(1,i,i) << ' ';
                        // }
                        // cout << endl;
                        // for(int i = 1;i<=n;i++)
                        // {
                        //     cout << querysum2(1,i,i) << ' ';
                        // }
                        // cout << endl;
                        // cout << endl;
                }else if(op==2)
                {
                        int len = y-x+1;
                        cout << querysum(1,x,y)/len << endl;
                }else if(op==3)
                {
                        int len = y-x+1;
                        //cout << avg << ' ' << endl;
                        cout << (querysum2(1,x,y)/len-pow(querysum(1,x,y)/len,2)) << endl;
                }
        }
        return 0;
}