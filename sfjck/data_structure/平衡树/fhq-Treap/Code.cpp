//LuoguP3369
#include <iostream>
#include <algorithm>
#include <cstring>
#include <random>

using namespace std;

const int N = 2e5+10;
mt19937 rnd(233);
struct Node
{
    int l, r;//左右子树编号
    int val,key;//值和索引
    int sz;//子树大小
}fhq[N];
int cnt,root;
//创建节点
inline int newnode(int val)
{
    fhq[++cnt].val = val;
    fhq[cnt].key = rnd();//索引要随机
    fhq[cnt].sz = 1;
    return cnt;
}
//更新子树大小
inline void update(int now)
{
    fhq[now].sz = fhq[fhq[now].l].sz + fhq[fhq[now].r].sz+1;
}
//按照值val分裂
void split(int now ,int val , int &x , int &y)
{
    if(!now)x=y=0;//特判一下当前节点不存在
    else 
    {
        if(fhq[now].val<=val)
        {
            x = now;//当前节点的左子树一定是小于val的
            //当前节点右子树不一定小于val,那么要单独对右子树进行分裂
            split(fhq[now].r,val,fhq[now].r,y);//注意在当前节点的右子树中仍然有可能有小于等于val的,但是这些比当前节点的值大,所以要并到当前节点的右子树中
        }else 
        {
            //上下对偶
            y = now;
            split(fhq[now].l,val,x,fhq[now].l);
        }
        update(now);
    }
}
//合并,返回的是合并完后的树的编号
int merge(int x,int y)
{
    if(!x||!y)return x+y;
    //合并后要维护Treap性质——值满足二叉搜索树,idx满足二叉堆
    //先维护二叉堆的性质(此处按照大根堆来写)
    if(fhq[x].key>fhq[y].key)
    {
        fhq[x].r = merge(fhq[x].r,y);
        update(x);
        return x;
    }else 
    {
        //对偶
        fhq[y].l = merge(x,fhq[y].l);
        update(y);
        return y;
    }
}
int x,y,z;
//插入val:把Treap按照val分裂成x和y,然后再合并新节点,x,y
void insert(int val)
{
    split(root,val,x,y);
    root = merge(merge(x,newnode(val)),y);
}
//删除val,先将树按值val分裂成x,z再将x按值val-1分裂成x,y,那么y树上所有的节点的值都是val,那么可以直接删y树上的根节点(即将根节点的左右子树合并),最后合并x,y,z即可
void del(int val)
{
    split(root,val,x,z);
    split(x,val-1,x,y);
    y = merge(fhq[y].l,fhq[y].r);
    root = merge(merge(x,y),z);
}
//查询排名:要查询val,只用将treap按val-1分裂成x,y即可,x的大小+1就是排名,最后再合并起来即可
inline void get_rank(int val)
{
    split(root,val-1,x,y);
    cout << fhq[x].sz+1 ;
    root=merge(x,y);
}
void get_num(int rank)
{
    int now = root;
    while (now)
    {
        if(fhq[fhq[now].l].sz+1==rank)break;
        else if(fhq[fhq[now].l].sz>=rank)
        {
            now = fhq[now].l;
        }else 
        {
            rank -= fhq[fhq[now].l].sz+1;
            now = fhq[now].r;
        }
    }
    cout << fhq[now].val;
}
//找前驱:把treap按val-1分裂成x,y;x的最右边的数就是val的前驱
void find_pre(int val)
{
    split(root,val-1,x,y);
    int now = x;
    while(fhq[now].r)
    {
        now = fhq[now].r;
    }
    cout << fhq[now].val;
    root=merge(x,y);
}
void find_ne(int val)
{
    split(root,val,x,y);
    int now = y;
    while(fhq[now].l)
    {
        now = fhq[now].l;
    }
    cout << fhq[now].val ;
    root=merge(x,y);
}

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
            insert(x);
            //cout << 'c' << ' ';
            //get_num(1);
            //cout << endl;
        }else if(opt==2)
        {
            del(x);
        }else if(opt==3)
        {
            get_rank(x);
            cout << endl;
        }else if(opt==4)
        {
           get_num(x);
           cout << endl;
        }else if(opt==5)
        {
            find_pre(x);
            cout << endl;
        }else if(opt==6)
        {
            find_ne(x);
            cout << endl;
        }
    }
}