//P3919
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6+10;
int a[N];
//同主席树
struct Node
{
    int l,r;
    int val;
}hjt[40*N];
int root[N],cnt;
//建树
void build(int l, int r,int &now)//当前版本now维护的[l,r]区间
{
    //先分配一个空间
    now = ++cnt;
    if(l==r)
    {
        hjt[now].val = a[r];
        return ;
    }
    int mid = l+r>>1;
    build(l,mid,hjt[now].l);
    build(mid+1,r,hjt[now].r);
}
void modify(int l,int r,int ver,int &now ,int pos ,int num)//历史版本(根节点)是ver当前版本(根节点)是now,因为新开节点要从内存池里面拿所以要传引用
{
    now = ++ cnt;
    hjt[now]=hjt[ver];//直接从历史版本新建当前版本
    if(l==r)
    {
        hjt[now].val = num;
        return ;
    }
    int mid = l+r>>1;
    if(pos<=mid)modify(l,mid,hjt[ver].l,hjt[now].l,pos,num);//要修改的在中点左边,那么就对应修改左子树
    else modify(mid+1,r,hjt[ver].r,hjt[now].r,pos,num);//修改的在右子树
}
int query(int l,int r,int now,int &pos)
{
    if(l==r)
    {
        return hjt[now].val;
    }
    int mid = l+r>>1;
    if(pos<=mid)return query(l,mid,hjt[now].l,pos);
    else return query(mid+1,r,hjt[now].r,pos);
}
int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
    }
    build(1,n,root[0]);//初始版本是0
    for(int i = 0 ;i < cnt;i++)
    {
        //cout << hjt[i].val << endl;
    }
    for(int i = 1;i<=m;i++)
    {
        int v ;
        int op;
        scanf("%d", &v);
        scanf("%d", &op);
        int loc ;
        scanf("%d", &loc);
        if(op==1)
        {
            int val;
            scanf("%d", &val);
            modify(1,n,root[v],root[i],loc,val);
        }else 
        {
            printf("%d\n",query(1,n,root[v],loc));
            root[i]=root[v];
        }
        //root[i]=root[v];
    }
}