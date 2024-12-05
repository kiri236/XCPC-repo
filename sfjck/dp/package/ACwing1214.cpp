#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4,mod=100000007;
int f[N][N];//f[i][j]表示前i个d的和mod n 等于j的方案数
int Mod(int a,int b)//防止余数出现负数
{
    return (a%b+b)%b;
}

int main()
{
    int n,s,a,b;
    cin >> n >> s >> a >> b ;
    f[0][0]=1;//选0个和的余数也是0是一种方案
    for (int i = 1; i < n; i ++ )
    {
        for (int j = 0; j < n; j ++ )
        {
            f[i][j]=(f[i-1][Mod(j-i*a,n)]+f[i-1][Mod(j+b*i,n)])%mod;//当前状态的方案数等于上一个状态的方案相加,当前状态的前i项d的和%n是j
        }
    }
    cout << f[n-1][Mod(s,n)];//因为首项是没有加di的所以加了di的就只有n-1项
}