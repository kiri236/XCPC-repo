//最长上升子序列二分优化
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5+10;
int a[N];
int q[N];//存所有长度下上升子序列结尾的最小值

int n ;
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    int len = 0;//记录一下最长上升子序列长度
    q[0]=-2e9;//为了保证左边一定有比a[i]小的数,那么就将q[0]赋为-inf
    for (int i = 0; i < n; i ++ )
    {
        int l = 0 ,r=len;
        //要找的是从0到len中比a[i]小的最大一个q[j]
        while(l<r)
        {
            int mid = l+r+1>>1;//处理边界问题
            if(q[mid]<a[i])l=mid;
            else r=mid-1;
        }
        len=max(len,r+1);//更新一下现在的长度,接了a[i]后整体长度就加一
        q[r+1]=a[i];//因为r是小于a[i]的最后一个数,那么q[r+1]>=a[i]
    }
    cout << len;
}