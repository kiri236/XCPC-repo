//一个数是一段数的众数,那么它一定是这段数的中位数
//这个结论反之不一定成立
//那么我们只需要找到区间中位数然后看他的出现次数是否大于区间长度的一半即可
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 5e5+100;
int n,m;
int a[N];
//初始时树中的l,r,sum均为0,之后读一个插一个
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
int query(int l ,int r,int L,int R,int k)//L代表L-1版本的权值线段树遍历的当前节点,R代表R版本的权值线段树遍历的当前节点
{
    if(l==r)return l;
    int m = l+r>>1;
    //该往减出来的权值线段树的哪里找
    //先看减出来的权值线段树的左子树
    int nowls = hjt[hjt[R].l].sum-hjt[hjt[L].l].sum;
    if(k<=nowls)//要找的在左子树上
    {
        return query(l,m,hjt[L].l,hjt[R].l,k);//要走就都往左子树上走
    }else //要找的在右子树上
    {
        return query(m+1,r,hjt[L].r,hjt[R].r,k-nowls);
    }
}
//计算某个数出现的次数
int appear(int l,int r,int L,int R,int pos)
{
    if(l==r)return hjt[R].sum-hjt[L].sum;
    int mid = l+r>>1;
    if(pos<=mid)
    {
        return appear(l,mid,hjt[L].l,hjt[R].l,pos);
    }else return appear(mid+1,r,hjt[L].r,hjt[R].r,pos);
}
int main()
{
    scanf("%d", &n);
    scanf("%d", &m);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
    }
    //每插入一个数 就对他建权值线段树
    for(int i = 1;i<=n;i++)
    {
        insert(1,n,root[i-1],root[i],a[i]);//根节点维护的是[1,n]
    }
    //询问
    while(m--)
    {
        int l,r;
        scanf("%d%d", &l, &r);
        int len  = r-l+1;
        if(len%2)
        {
            int k = (r-l+2)/2;
            int ans =  query(1,n,root[l-1],root[r],k);
            //cout <<  ans  <<  " " <<appear(1,n,root[l-1],root[r],ans) << endl;
            if(appear(1,n,root[l-1],root[r],ans)>(r-l+1)/2)cout << ans;
            else cout << 0;
        }else //偶数的时候中位数是两个,如果一个数出现次数严格大于一半那么两个中位数都要是它
        {
            int k1 = (r-l+1)/2,k2 = (r-l+3)/2;
            int ans1 = query(1,n,root[l-1],root[r],k1),ans2 = query(1,n,root[l-1],root[r],k2);
            if(ans1==ans2&&appear(1,n,root[l-1],root[r],ans1)>(r-l+1)/2)
            {
                cout << ans1 ;
            }else cout << 0 ;
        }
        cout << endl;
    }
}