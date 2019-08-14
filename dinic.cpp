#include<bits/stdc++.h>

/*
 * Dinic's algorithm
 * O(V^2*E)
 */

using namespace std;
typedef long long ll;
#define PB push_back
#define INF 1e9
int n;
const int maxn = 5010;
struct Edge {
	int b, c, f, r;
	Edge(int x1, int x2, int x3, int x4) : b(x1), c(x2), f(x3), r(x4) {}
};

vector<Edge> v[maxn];
int d[maxn], st[maxn];

int dfs(int a, int t, int val)
{
	if(a==t)
	{
		return val;
	}
	for(; st[a] < v[a].size(); st[a]++)
	{
		Edge &e = v[a][st[a]];
		if(d[a]+1==d[e.b] && e.c-e.f > 0)
		{
			int res = dfs(e.b, t, min(e.c-e.f, val));
			if(res > 0)
			{
				e.f+=res;
				v[e.b][e.r].f-=res;
				return res;
			}
		}
	}
	
	return 0;
}

ll maxFlow(int s, int t)
{
	ll res=0;
	while(true)
	{
		for(int i=1; i<= n+1; i++)
		{
			st[i] = 0;
			d[i] = INF;
		}
		d[s] = 0;
		queue<int> kolejka;
		kolejka.push(s);
		while(kolejka.empty() == false)
		{
			int a = kolejka.front();
			kolejka.pop();
			for(Edge e : v[a])
			{
				if(d[e.b] == INF && e.c-e.f > 0)
				{
					d[e.b] = d[a]+1;
					kolejka.push(e.b);
				}
			}
		}
		if(d[t] == INF)
			break;
		int df=0;
		do
		{
			df = dfs(s, t, INF);
			res= res + (ll)df; 
		}while(df);
		
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(0);
	int m;
	cin >> n >> m;
	for(int i=0; i < m; i++)
	{
		int a, b, c, s1, s2;
		cin >> a >> b >> c;
		s1 = v[a].size();
		s2 = v[b].size();
		v[a].PB(Edge(b, c, 0, s2));
		v[b].PB(Edge(a, c, 0, s1));
	}
	cout << maxFlow(1, n) << "\n";
	
	/*for(int i=1; i <= n; i++)
	{
		for(Edge e : v[i])
		{
			cout << i << " " << e.b << " " << e.f << "\n";
		}
	}*/
	
	return 0;
}