//最长公共子序列（lcs）线性dp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
const int N = 1e5;
typedef pair<int, int> PII;

int a[N],b[N];
map<PII,int> f;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= n; j ++ )
        {
            f[{i,j}]=max(f[{i-1,j}],f[{i,j-1}]);
            if(a[i]==b[j])f[{i,j}]=max(f[{i,j}],f[{i-1,j-1}]+1);
        }
    }
    cout << f[{n,n}];
}