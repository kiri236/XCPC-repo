//石子合并 区间dp ACwing282
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e4;
int s[N];
int f[N][N];
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &s[i]);
        s[i]+=s[i-1];
    }
    for(int len = 2;len<=n;len++)//首先枚举区间长度len
    {
        for (int i = 1; i+len-1<=n; i ++ )//枚举起点
        {
            int mini =1e9;
            int l = i , r =i+len-1;
            for (int k = l; k < r; k ++ )//枚举分界点
            {
                mini=min(mini,f[l][k]+f[k+1][r]+s[r]-s[l-1]);//dp方程:找代价最小值:此次代价最小值等于上次合并石子的最小值之和加上这一段的价值之和
            }
            f[l][r]=mini;
        }
    }
    cout << f[1][n];
}