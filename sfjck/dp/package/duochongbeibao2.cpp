//二进制优化
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 25000,M  =2020;

int w[N],v[N];
int f[N];
int main()
{
    int n ,m ;
    int cnt =0 ;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        int a , b ,s;
        scanf("%d%d", &a, &b);
        scanf("%d", &s);
        int k = 1;
        while(k<=s)
        {
            cnt++;
            v[cnt]=a*k;
            w[cnt]=b*k;
            s-=k;
            k*=2;
        }
        if(s>0)
        {
            cnt++;
            v[cnt]=a*s;
            w[cnt]=b*s;
        }
    }
    n= cnt;
    //对处理后的进行01背包
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = m; j >=v[i]; j -- )
        {
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }
    cout << f[m];
}