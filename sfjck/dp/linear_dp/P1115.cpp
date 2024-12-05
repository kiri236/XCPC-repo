#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
int f[N];//以i结尾的最大连续子段和
int a[N];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        f[i]=max(f[i-1]+a[i],a[i]);//要么就将这个子段延续下去,要么另起炉灶
    }
    int maxn =-2e9-10;
    for (int i = 1; i <= n; i ++ )
    {
        maxn=max(f[i],maxn);//找最大值
    }
    cout << maxn;
    
}