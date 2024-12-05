//暴力写法
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e2+10;
int n,m;
int v[N],w[N],s[N];
int f[N][N];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d%d", &v[i], &w[i]);
        scanf("%d", &s[i]);
    }
    for (int i = 1; i <= n; i ++ )//枚举种数
    {
        for (int j = 0; j <=m; j ++ )//枚举容量
        {   
            f[i][j]=f[i-1][j];//不选当前的
            for (int k = 0; k <=s[i]; k ++ )//枚举选几个
            {
                if(j-k*v[i]>=0)f[i][j]=max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);
            }
        }
    }
    cout << f[n][m];
}