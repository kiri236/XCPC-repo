#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
int a[N];
int stk[N],tt;
int rt[N];
int big[N];
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1;i<=n;i++)
    {
        scanf("%d", &a[i]);
    }
    
    for(int i = n;i>=1;i --)
    {
        //单调栈找出每个数右边离他最近的比他大的数的下标
        while(tt&&a[stk[tt]]<=a[i])tt--;
        if(tt)rt[i]=stk[tt];
        else rt[i]=n+1;
        stk[++tt]=i;
    }
    for(int i = n;i>=1;i--)
    {
        big[i]+=big[rt[i]]+1;
    }
    for(int i = 1 ;i<=n;i++)cout << big[i+1] << ' ';
}