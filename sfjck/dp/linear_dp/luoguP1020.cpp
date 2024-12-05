#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
int a[N];
int q[N];
int g[N];
int main()
{
    int d;
    int cnt =0 ;
    while(scanf("%d",&d)!=EOF)
    {
        a[cnt++]=d;
    }
    q[0]=2e9;
    int res  =0;
    for (int i = 0; i < cnt; i ++ )
    {
        int l = 0 ,r=res;
        while(l<r)
        {
            int mid = l+r+1>>1;
            if(q[mid]>=a[i])l=mid;
            else r=mid-1;
        }
        res=max(res,r+1);
        q[r+1]=a[i];
    }
    cout << res << endl;
    int num =0 ;
    //memset(g, 0x3f, sizeof g);
    for (int i = 0; i < cnt; i ++ )
    {
        int l =0,r=num;
        while(l<r)
        {
            int mid = l+r>>1;
            if(g[mid]>=a[i])r=mid;
            else l=mid+1;
        }
        //cout << i << " " << g[l] << " " << a[i] << endl;
        if(g[l]>=a[i])
        {
            g[l]=a[i];
        }else
        {
            num++;
            g[num]=a[i];
        }
    }
    cout << num;
}
