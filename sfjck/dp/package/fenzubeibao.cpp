#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int s[N];
int v[N][N],w[N][N];
int n,m;
int f[N];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &s[i]);
        for (int j = 0; j < s[i]; j ++ )
        {
            scanf("%d%d", &v[i][j], &w[i][j]);
        }
    }
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = m; j >=0; j -- )
        {
            for (int k = 0; k < s[i]; k ++ )
            {
                if(v[i][k]<=j)f[j]=max(f[j],f[j-v[i][k]]+w[i][k]);
            }
        }
    }
    cout << f[m];
}