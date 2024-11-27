#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e6;
int a[N];
long long b[N];
int main()
{
    int n;
    scanf("%d", &n);
    int len = sqrt(n);
    for(int i = 0; i < n ; i ++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n ; i ++)
    {
        int opt;
        int l,r,c;
        scanf("%d", &opt);
        scanf("%d%d", &l, &r);
        l--,r--;
        scanf("%d", &c);
        if(opt==0)
        {
            if(l/len==r/len)
            {
                for(int j = l ; j <= r; j ++)
                {
                    a[j] += c;
                }
            }else
            {
                for(int j = l;j<l/len*len+len;j++)
                {
                   a[j] += c; 
                }
                for(int j = l/len+1;j<=r/len-1;j++)
                {
                    b[j] += c;
                }
                for(int j = r/len*len;j<=r;j++)
                {
                    
                    a[j] += c;
                }
                ///cout << endl;
            }
        }else 
        {
            cout << a[r] + b[r/len] << endl;
        }
    }
}