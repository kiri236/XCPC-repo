#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 5010;
int a[N];
int f[N];
int g[N];
int n ;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i ++ )
    {
        f[i]=1;//只有a[i]一个数
        g[i]=0;
        for (int j = 1; j <i; j ++ )
        {
            if(a[i]>a[j])
            {
                if(f[i]<f[j]+1)
                {
                    g[i]=j;
                    f[i]=f[j]+1;
                }//以第i个数结尾的序列的最大长度取决于以第j个数结尾的最大长度加1
            }
        }
    }
    int k =0;
    //看以谁结尾的上升子序列最长
    for (int i = 1; i <= n; i ++ )
    {
        if(f[i]>f[k])
        {
            k=i;
        }
    }
    cout << f[k] << endl ;
    //逆序输出最长上升子序列
    for(int i =0 ,len = f[k];i<len;i++)
    {
        cout << a[k] << " ";
        k=g[k];
    }
}