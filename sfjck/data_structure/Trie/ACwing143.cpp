#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 3e6+10,M=1e5;
int son[N][2];
int a[M];
int idx;
void insert(int x)
{
    int p=0;
    for (int i = 30; i >= 0; i -- )
    {
        int u =x>>i&1;
        if(!son[p][u])son[p][u]=++idx;
        p=son[p][u];
    }
}
//找与x异或起来最大的数
int query(int x)
{
    //从最高位开始找
    int p=0;
    int res=0;
    for (int i = 30; i >=0; i-- )
    {
        int u =x>>i&1;
        if(son[p][!u])//如果有与他相反的数
        {
            p=son[p][!u];
            res=res*2+!u;
        }else
        {
            p=son[p][u];
            res=res*2+u;
        }
    }
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        scanf("%d", &a[i]);
        insert(a[i]);
    }
    int res =0;
    for (int i = 0; i < n; i ++ )
    {
        int t=query(a[i]);
        res=max(res,t^a[i]);
    }
    printf("%d",res);
}