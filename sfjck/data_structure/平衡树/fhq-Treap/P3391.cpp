//Luogu P3391文艺平衡树
#include <iostream>
#include <random>
using namespace std;
const int N = 1e5+10;
mt19937 rnd(233);
struct Node
{
    int l,r;
    int val,key;
    int sz;
    bool lazy;
}fhq[N];
int cnt , root;
int newnode(int val)
{
    fhq[++cnt].val = val;
    fhq[cnt].key = rnd();
    fhq[cnt].sz = 1;
    return cnt;
}
inline void update(int now)
{
    fhq[now].sz = fhq[fhq[now].l].sz + fhq[fhq[now].r].sz + 1;
}
void push_down(int now)
{
    if(fhq[now].lazy)swap(fhq[now].l,fhq[now].r);
    fhq[fhq[now].l].lazy ^= 1;
    fhq[fhq[now].r].lazy ^= 1;
    fhq[now].lazy = false;
}
//按照大小分裂
void split(int now,int sz,int &x ,int &y)
{
    if(!now)x=y=0;
    else
    {
        if(fhq[now].lazy)push_down(now);//如果有lazytag那么就一定要往下传
        if(fhq[fhq[now].l].sz<sz)//左子树sz小于要分裂的sz那说明一定有部分在右子树中
        {
            x = now;
            split(fhq[now].r,sz-fhq[fhq[now].l].sz-1,fhq[now].r,y);
        }else 
        {
            y = now;
            split(fhq[now].l,sz,x,fhq[now].l);
        }
        update(now);
    }
}
int merge(int x,int y)
{
    if(!x||!y)return x+y;
    if(fhq[x].key<fhq[y].key)
    {
        //有更改就要push_down
        if(fhq[x].lazy)push_down(x);
        fhq[x].r = merge(fhq[x].r,y);
        update(x);
        return x;
    }else 
    {
        if(fhq[y].lazy)push_down(y);
        fhq[y].l = merge(x,fhq[y].l);
        update(y);
        return y;
    }
}
void reverse(int l ,int r)
{
    int x,y,z;
    //先按大小l-1拆成x,y
    split(root,l-1,x,y);
    //再将y按照大小r-l+1拆成y,z
    split(y,r-l+1,y,z);
    //y就是要操作的数
    fhq[y].lazy ^= 1;
    root = merge(merge(x,y),z);
}
void ldr(int now)
{
    if(!now)return ;
    if(fhq[now].lazy)push_down(now);
    ldr(fhq[now].l); 
    cout << fhq[now].val << ' ';
    ldr(fhq[now].r);
}
int main()
{
    int n,m;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n ; i ++)
    {
        root = merge(root,newnode(i));
    }
    while(m--)
    {
        int l,r;
        cin >> l >> r;
        reverse(l,r);
    }
    ldr(root);
}