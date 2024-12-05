//进行前后缀分解:预处理出1到n中和最大的连续子段(从前往后),再预处理出n到1中和最大的连续字段(从后往前),然后再枚举分界点即可
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int t;
const int inf= 1e9;
const int N = 5e4+10;
int a[N];
int f[N],g[N],h[N];//f是dp数组,g是前缀数组,h是后缀数组
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        f[0]=g[0]=-inf;//一个也不选是非法的
        for (int i = 1; i <= n; i ++ )
        {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i ++ )
        {
            f[i]=a[i]+max(0,f[i-1]);//分选a[i]和不选a[i]两种情况
            g[i]=max(g[i-1],f[i]);
        }
        f[n+1]=h[n+1]=-inf;
        for (int i = n; i ; i -- )
        {
            f[i]=a[i]+max(0,f[i+1]);
            h[i]=max(h[i+1],f[i]);
        }
        //枚举所有分界点
        int res =-inf ;
        for (int i = 1; i <= n; i ++ )
        {
            res=max(g[i]+h[i+1],res);
        }
        cout << res << endl;
        
    }
}