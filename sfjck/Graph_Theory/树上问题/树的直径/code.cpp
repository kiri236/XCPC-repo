#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 1e4+10,M=1e5;
int h[N], e[M], ne[M], idx;
int dist[N];
void add(int a, int b)  // 添加一条边a->b
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs(int st)
{
    memset(dist, -1, sizeof dist);
    queue<int>q;
    q.push(st);
    dist[st]=0;
    while(!q.empty())
    {
        int t =q.front();
        q.pop();
        for(int i = h[t];i!=-1;i=ne[i])
        {
            if(dist[e[i]]==-1)
            {
                dist[e[i]]=dist[t]+1;
                q.push(e[i]);
            }
        }
    }
}
int main()
{
    int n;
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for (int i = 0; i < n-1; i ++ )
    {
        int a,b;
        scanf("%d%d", &a, &b);
        add(a,b);
        add(b,a);
    }
    bfs(1);
    int u =1 ;
    for (int i = 1; i <= n; i ++ )
    {
        if(dist[i]>dist[u])u=i;
    }
    bfs(u);
    for (int i = 1; i <= n; i ++ )
    {
        if(dist[i]>dist[u])u=i;
    }
    cout << dist[u];
}