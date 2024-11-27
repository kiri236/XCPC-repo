//P3402可持久化并查集
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2e5+12;
struct Node
{
    int l,r;
    int val;
}hjt[N*70];
int n,m;

int cnt,tot;//tot是为了初始化p[N]数组时让每个p[i]=i;
int rootp[N],rootdep[N];
void build(int l,int r,int &now)//初始化p[N]数组
{
    //先分配空间
    now = ++cnt;
    if(l==r)
    {
        hjt[now].val = ++tot;
        return ;
    }
    int mid = l + r>>1;
    build(l,mid,hjt[now].l);
    build(mid+1,r,hjt[now].r);
}
void modify(int l,int r,int ver,int &now,int pos,int num)
{
    hjt[now=++cnt] = hjt[ver];
    if(l==r)
    {
        hjt[now].val = num;
        return ;
    }
    int mid = l + r>>1;
    if(pos<=mid)
    {
        modify(l,mid,hjt[ver].l,hjt[now].l,pos,num);
    }else modify(mid+1,r,hjt[ver].r,hjt[now].r,pos,num);
}
int query(int l,int r,int now,int pos)
{
    if(l==r)return hjt[now].val;
    int mid = l+r>>1;
    if(pos<=mid)return query(l,mid,hjt[now].l,pos);
    else return query(mid+1,r,hjt[now].r,pos);
}
int find(int ver,int x)//找ver版本中x的父亲
{
    int px = query(1,n,rootp[ver],x);
    return px==x?px:find(ver,px);//不要路径压缩
}
void merge(int ver,int x,int y)//将ver版本中的x和y两个节点按秩合并
{
    x = find(ver-1,x),y = find(ver-1,y);//传进来的ver是新版本,里面是空,所以我们要找的是上一个版本的信息
    if(x==y)//在一个并查集内就不用合并将上个版本的信息拿过来就是了
    {
        rootp[ver]=rootp[ver-1];
        rootdep[ver]=rootdep[ver-1];
    }else //否则按秩合并
    {
        int depx = query(1,n,rootdep[ver-1],x);
        int depy = query(1,n,rootdep[ver-1],y);//ver-1!!!!!
        //小的往大的上并
        if(depx<depy)
        {
            modify(1,n,rootp[ver-1],rootp[ver],x,y);//把x的父亲修改为y
            rootdep[ver] = rootdep[ver-1];//合并后每个节点的秩不会改变
        }else if(depx>depy)
        {
            modify(1,n,rootp[ver-1],rootp[ver],y,x);
            rootdep[ver] = rootdep[ver-1];
        }else 
        {
            //两个树深度相等合并后深度加一
            modify(1,n,rootp[ver-1],rootp[ver],x,y);
            modify(1,n,rootdep[ver-1],rootdep[ver],y,depy+1);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    build(1,n,rootp[0]);
    for(int i = 1;i <= m;i ++)
    {
        int op;
        cin >> op;
        int x,y;
        if(op==1)
        {
            cin >> x >> y;
            merge(i,x,y);
        }else if(op==2)
        {
            cin >> x;
            //因为维护了两个可持久化数组,所以要同时回退,注意顺序
            rootp[i]=rootp[x];
            rootdep[i]=rootdep[x];
        }else 
        {
            cin >> x >> y;
            //询问算一次操作但是不做修改所以将其等于上一个版本即可
            rootp[i]=rootp[i-1];
            rootdep[i]=rootdep[i-1];
            int px = find(i,x),py = find(i,y);
            cout << (px==py?1:0) << endl;
        }
    }
}