//洛谷P1962
//矩阵快速幂可加速递推
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int N = 3;

int n ,m=1e9+7;
void mul(int c[],int a[],int b[][N])//注意传进来的指针长度不是数组长度而是指针长度
{
    int tmp[N]={0};//用一个临时数组存一下
    for(int i =0;i<N;i++)
    {
        for (int j = 0; j < N; j ++ )
        {
            tmp[i]=(tmp[i]+a[j]*b[j][i])%m;
        }
    }
    memcpy(c,tmp,sizeof tmp);//不能用c的size
}
void mul(int c[][N],int a[][N],int b[][N])//二维矩阵相乘a*b=c
{
    int tmp[N][N]={0};
    for (int i = 0; i < N; i ++ )
    {
        for (int j = 0; j < N; j ++ )
        {
            for (int k = 0; k < N; k ++ )
            {
                tmp[i][j]=(tmp[i][j]+a[i][k]*b[k][j])%m;
            }
        }
    }
    memcpy(c,tmp,sizeof tmp);
}
signed main()
{
    cin>>n;
    //定义初始矩阵
    int f1[N]={1,1,1};//f1,f2,s1:斐波那契第一项,第二项,第一项的和
    //定义系数矩阵
    int a[N][N]={
      {0,1,0},
      {1,1,1},
      {0,0,1}
    };
    n--;
    //矩阵快速幂
    while(n)
    {
        if(n&1)mul(f1,f1,a);//f1=f1*a;
        mul(a,a,a);//a=a*a
        n>>=1;
    }
    cout << f1[0] << endl;
    return 0;
}