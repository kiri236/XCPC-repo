//在指定位数下将比特进行翻转,如在3位2进制下将4(100)翻转为1(001)
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int bit_reverse(int x,int bits)
{
    int res = 0 ;
    for(int i = 0 ; i < bits ; i ++ )
    {
        res = (res<<1)|(x&1);
        x>>=1;
    }
    return res;
}
int main()
{
    int u;
    cin >> u ;
    cout << bit_reverse(u,4) << endl;
}