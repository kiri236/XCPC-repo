#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 200;
int n,m;
int h[N][N];
int f[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dp(int x , int y)
{
    if(f[x][y]!=-1)return f[x][y];//已经处理过了
    int &v=f[x][y];//用引用方便改变值
    v=1;//就算周围不能走了自己也算是一步
    for (int i = 0; i < 4; i ++ )
    {
        int a = x+dx[i],b=y+dy[i];
        if(a<=n&&a>=1&&b<=m&&b>=1&&h[a][b]<h[x][y])//如果能走
        {
            v=max(dp(a,b)+1,v);//向前走一步等于以新的点为起点算出的最大值再加一
        }
    }
    return v;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <=m; j ++ )
        {
            scanf("%d", &h[i][j]);
        }
    }
    memset(f, -1, sizeof f);
    int res = 0 ;
    for (int i = 1; i <= n; i ++ )//枚举每一个起点
    {
        for (int j = 1; j <=m; j ++ )
        {
            res = max(res,dp(i,j));
        }
    }
    cout << res << endl;
}