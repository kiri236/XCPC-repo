//维护到根节点距离的并查集
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const int N = 3e4+1;
int p[N];
int dist[N];
int sz[N];
int find(int x)
{
    if(p[x]!=x)
    {
        int tmp = p[x];
        p[x] = find(p[x]);
        dist[x]+=dist[tmp];
    }
    return p[x];
}
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i = 1;i<=30000;i++)
    {
        p[i]=i;
        dist[i]=0;
        sz[i]=1;
    }
    while(t--)
    {
        char op;
        cin >> op;
        int i,j;
        cin >> i >> j;
        //find(i),find(j);
        //cout << endl;
        if(op=='M')
        {
            int u,v;
            u = find(i),v = find(j);
            dist[u]+=sz[v];
            sz[v]+=sz[u];
            p[u]=v;
            
        }else
        {
            int u = find(i),v=find(j);
            if(u==v)
            {
                cout << abs(dist[i]-dist[j])-1 << endl;
            }else 
            {
                cout << -1 << endl;
            }
        }
    }
}