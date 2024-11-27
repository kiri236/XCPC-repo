#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6+100;
int a[N];
int ne[N];
int p[N];
struct Node
{
    int l,r,sum;//左儿子是hjt[l],右儿子是hjt[r]
}hjt[N*40];
int cnt ,root[N];//内存池计数器和根节点编号

void insert(int l ,int r,int pre,int &now ,int p)//[l,r]为当前节点维护的区间,pre表示上一个版本线段树的当前节点编号,Now表示当前线段树的当前节点编号,要插入的值用p表示
{
    hjt[++cnt]=hjt[pre];//从内存池中取一个节点让他等于上个版本的
    now = cnt;//更新当前节点
    hjt[now].sum++;//权值线段树维护的是值域值的个数
    if(l==r)return ;//到叶子节点了就返回
    int m = l+r>>1;
    //插入一个数等价于你想往线段树上哪个位置插入一个数
    if(p<=m)insert(l,m,hjt[pre].l,hjt[now].l,p);
    else insert(m+1,r,hjt[pre].r,hjt[now].r,p);
}
//查询L,R版本之间在[l,r]区间中大于num的数有多少
int query(int l ,int r,int L,int R,int &num)//L代表L-1版本的权值线段树遍历的当前节点,R代表R版本的权值线段树遍历的当前节点
{
    if(l==r)
    {
        return hjt[R].sum-hjt[L].sum;
    }
    int m = l+r>>1;
    if(num<=m)return query(l,m,hjt[L].l,hjt[R].l,num)+hjt[hjt[R].r].sum-hjt[hjt[L].r].sum;//如果在左子树就要加上右子树的值
    else return query(m+1,r,hjt[L].r,hjt[R].r,num);
}
int main()
{
    int n,m;
    scanf("%d", &n);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
        p[a[i]]=n+1;
    }
    for(int i = n;i>=1;i--)
    {
        ne[i]=p[a[i]];//ne记录在该数右边第一个相等的数的位置
        p[a[i]]=i;
    }
    for(int i = 1;i<=n;i++)
    {
        insert(1,n+1,root[i-1],root[i],ne[i]);
    }
    scanf("%d", &m);
    while (m -- )
    {
        int l,r;
        scanf("%d%d", &l, &r);
        int h = r+1;
        int ans = query(1,n+1,root[l-1],root[r],h);
        printf("%d\n",ans);
    }
}