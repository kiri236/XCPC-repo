#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int mod=1000000007;
int f[51][51][13][14];//f[i][j][k][c]表示从起点到i,j选了k个数且最后一个选的数是c的方案数
int g[51][51];
int main()
{
    int n,m,k;
    scanf("%d%d", &n, &m);
    scanf("%d", &k);
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= m; j ++ )
        {
            scanf("%d", &g[i][j]);
            g[i][j]++;//将每个价值加一个偏移量以便后续操作时数组下标合法
        }
    }
    f[1][1][1][g[1][1]]=1;//选起点
    f[1][1][0][0]=1;//不选起点,c初始化为0,后面的每个数都严格大于0以便选后面的数
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <=m; j ++ )
        {
            if(i==1&&j==1)continue;//起点已经处理过了
            for(int u =0;u<=k;u++)//枚举选的数量
            {
                for(int v = 0;v<=13;v++)//枚举这一个选的价值
                {
                    int &val=f[i][j][u][v];
                    //不选该点的情况
                    val=(val+f[i-1][j][u][v])%mod;
                    val=(val+f[i][j-1][u][v])%mod;
                    //选该点的情况
                    if(u!=0&&v==g[i][j])//当前选的要作为更新后的f中的c
                    {
                        for(int c=0;c<v;c++)//枚举上一个选的价值
                        {
                            val=(val+f[i-1][j][u-1][c])%mod;
                            val=(val+f[i][j-1][u-1][c])%mod;
                        }
                    }
                }
            }
        }
    }
    int res =0 ;
    for (int i = 0; i <= 13; i ++ )//将走到终点并取了k个的所有可能情况方案数相加
    {
        res=(res+f[n][m][k][i])%mod;
    }
    cout << res;
}