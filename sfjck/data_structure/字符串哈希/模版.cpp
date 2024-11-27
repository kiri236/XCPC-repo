#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using ull=unsigned long long ;
const int N = 1e6,P=131;
ull h[N],p[N];//h数组存字符串前缀的哈希值，p数组用来存p的多少次方
char str[N];
ull gethash(int l ,int r)//算出区间的哈希值
{
    return h[r]-h[l-1]*p[r-l+1];
}
int main()
{
    int n ,m ;
    scanf("%d%d", &n, &m);
    scanf("%s", str);
    p[0]=1;
    for (int i = 1; i <= n; i ++ )
    {
        p[i]=p[i-1]*P;//预处理p的几次方
        h[i]=h[i-1]*P+str[i];//计算前缀的哈希值
    }
}