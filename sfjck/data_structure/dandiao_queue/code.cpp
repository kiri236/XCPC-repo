//滑动窗口求最大/最小值
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6+10;
int q[N],hh,tt=-1;//hh是队头,tt是队尾,单调队列里存的是下标
int a[N],n;
int main()
{
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    //求滑动窗口最小值
    for (int i = 1; i <= n; i ++ )
    {
        if(hh<=tt&&i-k+1>q[hh])hh++;//队头没跟上就让队头往前走一步
        while(hh<=tt&&a[q[tt]]>=a[i])tt--;
        q[++tt]=i;
        if(i>=k)printf("%d ",a[q[hh]]);
    }
    puts("");
    hh=0,tt=-1;
    //求滑动窗口最大值
    for (int i = 1; i <= n; i ++ )
    {
        if(hh<=tt&&i-k+1>q[hh])hh++;//队头没跟上就让队头往前走一步
        while(hh<=tt&&a[q[tt]]<=a[i])tt--;
        q[++tt]=i;
        if(i>=k)printf("%d ",a[q[hh]]);
    }
}