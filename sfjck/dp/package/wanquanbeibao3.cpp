//一维优化版本
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e3+10;
int w[N],v[N];
int f[N];//f[i][j]表示从1到i总体积不超过j的情况下总价值的最大值
//状态计算:分为拿了第i个物品0,1,2,3....j/v[i]件
//f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+w[i],f[i-1][j-2*v[i]]+2*w[i]....)
//f[i][j-v[i]]=max(     f[i-1][j-v[i],f[i-1][j-2*v[i]]]+w[i]......)
//f[i][j] = max(f[i-1][j],f[i][j-v[i]]);
int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d%d", &v[i], &w[i]);
    }
    for(int i = 1; i<=n;i++)
    {
        for(int j = v[i];j<=m;j++)
        {
            //f[j]=f[j];
            f[j]=max(f[j],f[j-v[i]]+w[i]);//滚动数组优化
        }
    }
    cout << f[m] << endl;
}