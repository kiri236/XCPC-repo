//枚举中间点即可
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5+10;
int a[N];
struct Node
{
    int l,r,sum;
}hjt[N*36];
int root[N],cnt;
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
//查询L,R版本之间在[l,r]区间中小于等于num的数有多少
int queryless(int l ,int r,int L,int R,int num)//L代表L-1版本的权值线段树遍历的当前节点,R代表R版本的权值线段树遍历的当前节点
{
    if(l==r)
    {
        return hjt[R].sum-hjt[L].sum;
    }
    int m = l+r>>1;
    if(num<=m)return queryless(l,m,hjt[L].l,hjt[R].l,num);//如果在左子树就要加上右子树的值
    else return queryless(m+1,r,hjt[L].r,hjt[R].r,num)+hjt[hjt[R].l].sum-hjt[hjt[L].l].sum;
}
int querymore(int l ,int r,int L,int R,int num)//L代表L-1版本的权值线段树遍历的当前节点,R代表R版本的权值线段树遍历的当前节点
{
    if(l==r)
    {
        return hjt[R].sum-hjt[L].sum;
    }
    int m = l+r>>1;
    if(num<=m)return querymore(l,m,hjt[L].l,hjt[R].l,num)+hjt[hjt[R].r].sum-hjt[hjt[L].r].sum;//如果在左子树就要加上右子树的值
    else return querymore(m+1,r,hjt[L].r,hjt[R].r,num);
}
int main()
{
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
        insert(0,N-5,root[i-1],root[i],a[i]);
    }
    for(int i = 1;i<=n;i++)
    {
        //if(i==1||i==n)continue;
        ans+= (long long)queryless(0,N-5,root[0],root[i],a[i]-1)*querymore(0,N-5,root[i-1],root[n],a[i]+1);
    }
    printf("%lld\n",ans);
}