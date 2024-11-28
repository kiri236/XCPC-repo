#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e6;
int n,m;
int b[N];
int a[N];
int main()
{
    scanf("%d", &n);
    int len = sqrt(n);
    scanf("%d", &m);
    while (m -- )
    {
        int op;
        scanf("%d", &op);
        if(op==1)
        {
            int l,r;
            scanf("%d%d", &l, &r);
            l--,r--;
            if(l/len==r/len)
            {
                for(int i = l ;i <= r; i ++)
                {
                    a[i]^=1;
                }
            }else 
            {
                for(int j = l;j<l/len*len+len;j++)
                {
                   a[j] ^= 1; 
                }
                for(int j = l/len+1;j<=r/len-1;j++)
                {
                    b[j] ^= 1;
                }
                for(int j = r/len*len;j<=r;j++)
                {
                    a[j] ^= 1;
                }
            }
        }else 
        {
            int i;
            scanf("%d", &i);
            i--;
            cout << (a[i]^b[i/len]) << endl;
        }
    }
}