//单调栈 找每个数右边第一个大于他的数的下标
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5+20;
int a[N];
int stk[N],tt;
int res[N];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    for (int i = n; i>=1; i -- )
    {
        while(tt&&a[stk[tt]]<=a[i])tt--;
        if(tt)
        {
            res[i]=stk[tt];
        }else res[i]=0;
        stk[++tt]=i;
    }
    for (int i = 1; i <= n; i ++ )
    {
        cout << res[i]<< endl;
    }
}