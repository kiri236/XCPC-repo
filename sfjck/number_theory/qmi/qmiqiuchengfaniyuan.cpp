//给定a和质数p求b在mod p意义下的逆元
#include<iostream>
using namespace std;
using ll = long long ;

int qmi(int a , int k , int p)//a^k%p
{
    int res = 1;
    while(k)//本质上是求k的二进制表示
    {
        if(k&1)res=(ll)res*a%p;//如果k的末位是1那么就乘上
        k>>=1;//k的末位算完了，删掉
        a=a*a%p;//到下一个a^2^i次方去
    }
    return res ;   
    
}
int main()
{
    int a, p;
    cin >> a >> p ;
    int res = qmi(a,p-2,p);
    if(a%p) cout << res;
    else cout << "impossible";//如果a是p的倍数那么一定无解 
}