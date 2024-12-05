//编辑距离 洛谷P2758
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e4;
char a[N],b[N];
int f[N][N];//表示将a[1~i]变成b[1~j]的最少操作次数
int main()
{
    scanf("%s", a+1);
    scanf("%s", b+1);
    int n = strlen(a+1),m=strlen(b+1);
    for (int i = 1; i <= n; i ++ )f[i][0]+=i;//将a的前i个字母变成b的前0个字母需要做i次删除
    for (int i = 1; i <= m; i ++ )f[0][i]+=i;//将a的前0个字母变成b的前i个字母需要做i次添加
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <=m; j ++ )
        {
            f[i][j]=min(f[i-1][j]+1,f[i][j-1]+1);//删除情况和添加情况可以直接算
            if(a[i]!=b[j])f[i][j]=min(f[i][j],f[i-1][j-1]+1);//若两个不同才加一
            else f[i][j]=min(f[i][j],f[i-1][j-1]);
        }
    }
    cout << f[n][m];
}