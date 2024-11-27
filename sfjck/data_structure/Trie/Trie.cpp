#include <bits/stdc++.h>

using namespace std ;

const int N = 4e6;
int son[N][62],cnt[N],idx;
char str[N];
int t ,n,q;
int getnum(char x){
    if(x>='A'&&x<='Z')
        return x-'A';
    else if(x>='a'&&x<='z')
        return x-'a'+26;
    else
        return x-'0'+52;
} 
void insert(char*str)
{
    int p =0 ,u;
    for(int i =0 ; str[i];i++)
    {
        u=getnum(str[i]);
        if(!son[p][u]) son[p][u]=++idx;
        p=son[p][u];
        cnt[p]++;
    }
    
}
int query(char*str)
{
    int p =0 ,u;
    for(int i =0 ; str[i];i++)
    {
        u=getnum(str[i]);
        if(!son[p][u]) return 0;
        p=son[p][u];
    }
    return cnt[p];
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        for(int i=0;i<=idx;i++)
            for(int j=0;j<=122;j++)
                son[i][j]=0;
        for(int i=0;i<=idx;i++)
            cnt[i]=0;
        idx=0;
        scanf("%d %d",&n,&q);
        while(n--)
        {
            scanf("%s",str);
            insert(str);
        }
        while(q--)
        {
            scanf("%s",str);
            printf("%d\n",query(str));
        }
    }
    return 0 ;
}