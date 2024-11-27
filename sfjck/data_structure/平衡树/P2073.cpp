#include <bits/stdc++.h>
using namespace std;
map<int,int>mp;
inline int read()
{
    int s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+ch-'0',ch=getchar();
    return s*f;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    bool flag = false;
    int x,y,z;
    while(x=read())
    {
        if(x==-1)break;
        if(x==1)
        {
            y = read(),z = read();
            if(mp[z])continue;
            mp[z]=y;
        }else if(mp.empty())
        {
            continue;
        }
        else if(x==2)
        {
            auto it = mp.end();
            --it;
            mp.erase(it);
        }else if(x==3)
        {
            mp.erase(mp.begin());
        }
        //cout << endl;
    }
    long long ans = 0,sum = 0;
    for(auto it:mp)
    {
            //cout << it.first << ' ' << it.second << endl;
            ans += it.first;
            sum += it.second;
    }
    cout <<sum << " " << ans << endl;
}