//可持久化数组
//插入的历史位置记录一下就行了
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5+10;
struct Node
{
    int l,r;
    char val;
}hjt[40*N];
int root[N];
int cnt;
int pos[N];
vector<int>pre;
void modify(int l,int r,int ver,int &now,int pos,char num)
{
    hjt[now=++cnt]=hjt[ver];
    if(l==r)
    {
        hjt[now].val = num;
        return ;
    }
    int mid = l+r>>1;
    if(pos<=mid)
    {
        modify(l,mid,hjt[ver].l,hjt[now].l,pos,num);
    }else modify(mid+1,r,hjt[ver].r,hjt[now].r,pos,num);
}
char query(int l,int r,int ver,int pos)
{
    if(l==r)
    {
        return hjt[ver].val;
    }
    int mid = l+r>>1;
    if(pos<=mid)
    {
        return query(l,mid,hjt[ver].l,pos);
    }else return query(mid+1,r,hjt[ver].r,pos);
}

int main()
{
    int n;
    ios::sync_with_stdio(false);
    cin >> n ;
    int ver = 0;
    pos[ver]=0;
    for(int i = 1;i<=n;i++)
    {
        //cout << i << ' ';
        char op;
        cin >> op;
        if(op=='T')
        {
            char x;
            cin >> x;
            ver++;
            pos[ver]=pos[ver-1]+1;
            modify(1,n,root[ver-1],root[ver],pos[ver],x) ;
            
        }else if(op=='U')
        {
            int x;
            cin >> x;
            ver++;
            root[ver]=root[ver-x-1];
            pos[ver]=pos[ver-x-1];
            
        }else 
        {
            int x;
            cin >> x;
            cout << query(1,n,root[ver],x) << endl;
        }
    }
}