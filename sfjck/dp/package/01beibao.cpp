#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e3+10;

int w[N],v[N];
int f[N][N];
int n,m;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1 ;i<=n;i++)
    {
        scanf("%d%d", &v[i], &w[i]);
    }
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 0; j <=m; j ++ )
        {
            f[i][j]=f[i-1][j];
            if(j>=v[i])f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+w[i]);
        }
    }
    cout << f[n][m];
}