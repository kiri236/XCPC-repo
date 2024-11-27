#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+20;
const double alpha = 0.75;
struct Node
{
    int l,r,val;//左右子树编号及当前节点的值
    int sz,fact;//当前节点为根的树的大小与实际大小
    bool exist;//当前节点是否存在
}tzy[N];
int cnt;//计数变量
int root;//根节点编号
void newNode(int &now,int val)//用val新建节点
{
    now = ++cnt;
    tzy[now].val=val;
    tzy[now].fact = 1;
    tzy[now].sz = 1;
    tzy[now].exist = true;
}
bool imbalance(int now)//判断now这个节点不平衡
{
    if((max(tzy[tzy[now].l].sz,tzy[tzy[now].r].sz)>tzy[now].sz*alpha)
    ||(tzy[now].sz-tzy[now].fact)>tzy[now].sz*0.3)
    {
        return true;//若子树的大小大于根大小的alpha倍或者被删除的节点占了子树中节点的30%以上就不平衡
    }
    return false;
}
vector<int>v;
void ldr(int now)//中序遍历
{
    if(!now)return ;
    ldr(tzy[now].l);
    if(tzy[now].exist)v.push_back(now);//存在才能重构
    ldr(tzy[now].r);
}
void lift(int l,int r,int &now)
{
    if(l==r)
    {
        now=v[l];
        tzy[now].l=tzy[now].r=0;
        tzy[now].sz=tzy[now].fact=1;
        return;
    }
    int m = (l+r)>>1;
    while(l<m&&tzy[v[m]].val==tzy[v[m-1]].val)
        m--;
    now = v[m];
    if(l<m) lift(l,m-1,tzy[now].l);
    else tzy[now].l=0;
    lift(m+1,r,tzy[now].r);
    tzy[now].sz=tzy[tzy[now].l].sz+tzy[tzy[now].r].sz+1;
    tzy[now].fact=tzy[tzy[now].l].fact+tzy[tzy[now].r].fact+1;
}
void rebuild(int &now)//暴力重构
{
    v.clear();
    ldr(now);
    if(v.empty())//特判一下所有都被删除的情况
    {
        now = 0 ;
        return ;
    }
    //分治拎起来
    lift(0,v.size()-1,now);
}
//每个节点没有存父亲的编号,所以采用头递归
void update(int now , int ed)
{
    if(!now)return ;
    if(tzy[ed].val<tzy[now].val)update(tzy[now].l,ed);
    else update(tzy[now].r,ed);
    tzy[now].sz = tzy[tzy[now].l].sz + tzy[tzy[now].r].sz+1;
}
void check(int &now,int ed)//从根节点往刚刚操作的节点找
{
    if(now==ed)return ;
    if(imbalance(now))//当前节点不平衡
    {
        rebuild(now);//重构当前节点
        update(root,now);//重构完后要往上传
        return ; 
    }
    if(tzy[ed].val<tzy[now].val)
    {
        check(tzy[now].l,ed);
    }else check(tzy[now].r,ed);
}
void insert(int &now,int val)
{
    if(!now)//当前节点不存在
    {
        newNode(now,val);//新建一个节点
        //判断是否平衡
        check(root,now);
        return ;
    }
    //当前节点存在
    tzy[now].sz++,tzy[now].fact++;
    //看往哪边插入
    if(val<tzy[now].val)
    {
        insert(tzy[now].l,val);//比根节点小往左插
    }else insert(tzy[now].r,val);//比根节点大往右插
}
void del(int now,int val)
{
    if(tzy[now].exist&&tzy[now].val == val)//如果当前节点存在且当前节点是要删的点
    {
        tzy[now].exist = false;
        tzy[now].fact--;//实际大小要减掉
        check(root,now);//检查是否平衡
        return;
    }
    //当前节点不是要删的节点就查找
    tzy[now].fact--;//实际数量减一
    if(val<tzy[now].val)
    {
        del(tzy[now].l,val);
    }else del(tzy[now].r,val);
}
//查询某个数的排名:比他小的个数+1
int getrank(int val)
{
    int now = root,rk =  1;
    while(now)
    {
        if(val<=tzy[now].val)now = tzy[now].l;
        else 
        {
            rk += tzy[now].exist + tzy[tzy[now].l].fact;
            now = tzy[now].r;
        }
    }
    return rk;
}
//查询排名的值
int getnum(int rk)
{
    int now =  root;
    while(now)
    {
        if(tzy[now].exist&&tzy[tzy[now].l].fact+tzy[now].exist==rk)//比他小的数+他自身==rk那么我们就找到了
        {
            break;
        }else if(tzy[tzy[now].l].fact>=rk)//左边比rk多那么答案肯定在左子树
        {
            now = tzy[now].l;
        }else 
        {
            //在往右子树找时要把左子树及根节点的影响先去掉
            rk-=tzy[tzy[now].l].fact+tzy[now].exist;
            now = tzy[now].r;
        }
    }
    return tzy[now].val;
}
//获得前驱:getnum(getrank(x)-1) 求后继:getnum(getrank(x+1))

int main()
{
    int t ;
    scanf("%d", &t);
    while(t--)
    {
        int  opt,x;
        scanf("%d%d", &opt, &x);
        if(opt==1)
        {
            insert(root,x);
        }else if(opt==2)
        {
            del(root,x);
        }else if(opt==3)
        {
            printf("%d\n",getrank(x));
        }else if(opt==4)
        {
           printf("%d\n",getnum(x));
        }else if(opt==5)
        {
            printf("%d\n",getnum(getrank(x)-1));
        }else if(opt==6)
        {
            printf("%d\n",getnum(getrank(x+1))) ;
        }
    }
}