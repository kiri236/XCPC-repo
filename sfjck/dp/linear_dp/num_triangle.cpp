//线性dp 洛谷P1216 [USACO1.5] [IOI1994]数字三角形 Number Triangles
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4,inf= 1e9;
int a[N][N];
int f[N][N];
int n ;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= i; j ++ )
        {
            scanf("%d", &a[i][j]);
        }
    }
    //初始化f数组
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 0; j <=i+1; j ++ )//要多初始化两位因为算边界时可能会用到左上方和右上方的
        {
            f[i][j]=-inf;
        }
    }
    f[1][1]=a[1][1];
    for (int i = 2; i <= n; i ++ )
    {
        for (int j = 1; j <=i; j ++ )
        {
            f[i][j]=max(f[i-1][j-1]+a[i][j],f[i-1][j]+a[i][j]);//有可能是从右上方来的也有可能是从左上方来的
        }
    }
    int res =-inf;
    for (int i = 1; i <= n; i ++ )
    {
        res = max(res,f[n][i]);//从最后一行找最大的
    }
    cout << res << endl;
}