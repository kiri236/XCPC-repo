#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
map<int,bool>st,lt;
const int N = 1e6;
int p[N];
int find(int x)
{
    if(p[x]!=x)p[x]=find(p[x]);
    return p[x];
}
vector<int>vers[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m ;

    for(int i = 0;i<n;i++)
    {
        p[i]=i;
    }
    for(int i =1 ; i<=m;i++)
    {
        int u,v;
        cin >> u >> v;
        vers[u].push_back(v);
        vers[v].push_back(u);
    }
    int k;
    cin >> k ;
    vector<int>del;
    for(int i = 0 ; i<k;i++)
    {
        int a;
        cin >> a;
        del.push_back(a);
        st[a]=true;
    }
    vector<int>ans;
    for(int i = 0 ; i<n;i++)
    {
        if(st[i])continue;
        for(int j = 0  ; j<vers[i].size();j++)
        {
            if(st[vers[i][j]])continue;
            int u = find(i) , v = find(vers[i][j]);
            if(u==v)continue;
            p[v]=u;
        }
    }
    int tmp = 0;
    for(int i = 0 ;i<n;i++)
    {
        if(st[i])continue;
        if(p[i]=i)
        {
            lt[i] = true;
            tmp++;
        }
    }
    ans.push_back(tmp);
    for(int i = del.size()-1;i>=0;i--)
    {
        tmp += 1;
        st[del[i]]=false;
        int x = del[i];
        for(int j = 0 ; j<vers[x].size();j++)
        {
            if(st[vers[x][j]])continue;
            int u = find(x) , v = find(vers[x][j]);
            if(u==v)continue;
            p[v]=u;
            if(vers[x][j]==p[vers[x][j]])tmp--;
        }
        ans.push_back(tmp);
    }
    for(int i = ans.size()-1;i>=0;i--)
    {
        cout << ans[i] << endl;
    }
    return 0;
}