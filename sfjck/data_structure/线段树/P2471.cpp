//TODO
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
const int N = 1e6;
using namespace std;

int a[N];
int b[N];
vector<int>vec;
inline int get_id(int x)
{
    return lower_bound(vec.begin(),vec.end(),x)-vec.begin()+1;
}
struct Node
{
    int l,r;
    int maxn ,mini;
}tr[N*4];
void push_up_max(int u)
{
    tr[u].maxn = max(tr[u<<1].maxn,tr[u<<1|1].maxn);
}
void push_up_min(int u)
{
    tr[u].mini = min(tr[u<<1].mini,tr[u<<1|1].mini);
}
void build(int u ,int l,int r)
{
    int val = b[r];
    tr[u]={l,r,val,val};
    if(l==r)return ;
    int mid = l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up_max(u);
    push_up_min(u);
}
void modify(int u, int x,int v)
{
    if(tr[u].l==tr[u].r)
    {
        tr[u].maxn+=v;//找到了叶节点
        tr[u].mini+=v;
    }
    else
    {
        int mid = tr[u].l+tr[u].r>>1;
        if(x<=mid)modify(u<<1,x,v);//如果在左边就去左子树处理
        if(x>mid)modify(u<<1|1,x,v);//如果在右子树就去右子树处理
        push_up_max(u);//处理完了记得更新一下当前节点
        push_up_min(u);
    }
}
int query_max(int x ,int l,int r)
{
    if(tr[x].l>=l&&tr[x].r<=r)return tr[x].maxn;//如果完全包含这个区间就返回该区间的信息
    int mid =tr[x].l+tr[x].r>>1;
    int maxn =-1e9-10;
    //将区间分成两半处理
    if(l<=mid)maxn=max(maxn,query_max(x<<1,l,r));//如果这个区间左端点在mid左边,那么说明要获取的信息在左边有,查询左子树
    if(r>mid)maxn=max(query_max(x<<1|1,l,r),maxn);//如果这个区间右端点在mid+1右边,那么说明要获取的信息在右边有,查询右子树
    return maxn;
}
int query_min(int x ,int l,int r)
{
    if(tr[x].l>=l&&tr[x].r<=r)return tr[x].mini;//如果完全包含这个区间就返回该区间的信息
    int mid =tr[x].l+tr[x].r>>1;
    int mini =1e9+10;
    //将区间分成两半处理
    if(l<=mid)mini=min(mini,query_min(x<<1,l,r));//如果这个区间左端点在mid左边,那么说明要获取的信息在左边有,查询左子树
    if(r>mid)mini=min(query_min(x<<1|1,l,r),mini);//如果这个区间右端点在mid+1右边,那么说明要获取的信息在右边有,查询右子树
    return mini;
}
int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 1,pre=-1;
    for(int i =1 ;i<=n;i++)
    {
        int x,y;
        scanf("%d%d", &x, &y);
        if(pre!=-1&&x!=pre+1)
        {
            a[cnt]=pre+1;
            b[cnt++]=0;
        }
        pre=x;
        a[cnt]=x;
        b[cnt++]=y;
    }
    for(int i = 1;i<cnt;i++)
    {
        vec.push_back(a[i]);
    }
    //sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    build(1,1,cnt);
    //puts("");
    int m;
    scanf("%d", &m);
    while (m -- )
    {
        int x,y;
        scanf("%d%d", &x, &y);
        int u = x ,v = y ;
        x=get_id(x),y=get_id(y);
        int val = b[y];
        bool judge = false;
        int maxn = query_max(1,x+1,y-1);
        int mini = query_min(1,x+1,y-1);
        if((a[x]!=u||b[x]==0)&&(a[y]!=v||b[y]==0))
        {
            puts("maybe");
            continue;
        }else if((a[x]==u&&b[x]!=0)&&(a[y]!=v||b[y]==0))
        {
            if(maxn<b[x])puts("maybe");
            else puts("false");
            continue;
        }else if((a[x]!=u||b[x]==0)&&(a[y]==v&&b[y]!=0))
        {
            maxn = query_max(1,x,y-1);
            mini = query_min(1,x,y-1);
            if(maxn < val)puts("maybe");
            else puts("false");
            continue;
        }
        if(v==u+1)
        {
            int vx = b[x];
            int vy = b[y];
            if(vx>=vy)puts("true");
            else puts("false");
            continue;
        }
        if(b[y]<=b[x])
        {
            judge = true;
        }else 
        {
            puts("false");
            continue;
        }
        //cout << b[get_id(y)] << endl;
        
        // cout << maxn << ' ' << mini << endl;
        // cout << val << endl;
        
        if(maxn < val&&mini!=0)puts("true");
        else if(maxn < val&&mini==0)puts("maybe");
        else if(maxn >= val)puts("false");
    }
}