#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define int long long
using namespace std;
const int N = 1e6+10;

typedef pair<int, int> PII;
bool cmp(PII a, PII b)
{
    return a.first > b.first;
}
signed main()
{
    ios::sync_with_stdio(false);
    int t;
    cin.tie(0);
    cin >> t;
    while(t--)
    {
        int n;
        int k;
        cin >> n >> k;
        vector<PII>s(n+1);
        vector<int>pre(n+2,0ll);//预处理出选前i个不亏钱的利润
        for(int i = 1 ; i <= n ; i ++)
        {
            cin >> s[i].second;
        }
        for(int i = 1; i <= n ; i ++)
        {
            cin >> s[i].first ;
        }
        sort(s.begin()+1,s.end(),cmp);
        for(int i = n ; i >= 1; i --)
        {
            pre[i] = pre[i+1]+max(s[i].first - s[i].second,0ll);//从后面往前枚举,因为后面默认都能买到
            //cout << pre[i] <<" ";
        }
        if(!k)
        {
            cout << pre[1] << endl;
            continue;
        }
        priority_queue<int,vector<int>,less<int>>heap;//维护一个大根堆,维护本金,因为要把本金大的弹出来,所以用大根堆
        int sum = 0 ;
        int ans = 0 ;//维护一下堆内和
        //枚举最后一个亏损的i
        for(int i = 1 ; i <= n ; i ++)
        {
            heap.push(s[i].second);
            sum += s[i].second;
            while(heap.size()>k&&heap.size())
            {
                sum -= heap.top();
                heap.pop();
            }
            if(heap.size()==k)
            {
                ans = max(ans,pre[i+1]-sum);
            }
        }
        cout << max(ans,0ll) << endl;
        // for(int i = 1 ;  i <= n ; i ++)
        // {
        //     cout << s[i].second << ' ' << s[i].first << endl;
        // }
    }
}