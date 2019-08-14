#include<bits/stdc++.h>

/*
 * Maximum flow of minimal cost
 * O(V*E + |f|*E*logV)
 * It is important to add edges in pairs one with positive and one with negative cost
 */

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
#define PB push_back
#define ST first
#define ND second
#define INF 1e9

const int maxn = 5010;
struct Edge 
{
	int b, c, f, r, a; //next vertex, capacity, flow, position in the neighbour's list, cost
	Edge() {}
	Edge(int x1, int x2, int x3, int x4, int x5) : b(x1), c(x2), f(x3), r(x4), a(x5) {}
};
vector<Edge> v[maxn];
int d[maxn], pot[maxn];
pii par[maxn];
bool vis[maxn];
int n;
int ile[maxn];

void BellmanFord(int a)
{
	d[a] = 0;
	//compute distances
	for(int q=0; q < n; q++)
	{
		for(int i=1; i <= n; i++)
		{
			for(Edge e : v[i])
			{
				if(e.c-e.f == 0)
					continue;
				if(d[a] + e.a < d[e.b])
				{
					d[e.b] = d[a] + e.a;
				}
			}
		}
	}
	//distance is a potential
	//compute new edges' weights
	for(int i=1; i <= n; i++)
	{
		pot[i] = d[i];
		for(Edge &e : v[i])
		{
			e.a = e.a + d[i] - d[e.b];
		}	
	}
}

pii Dijkstra(int s, int t)
{
	for(int i=1; i <= n; i++)
	{
		vis[i] = false;
		d[i] = -1;
	}
	d[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > kolejka;
	kolejka.push({0, s});
	//compute distances and shortest path to t
	while(kolejka.empty() == false)
	{
		pii x = kolejka.top();
		kolejka.pop();
		int a = x.ND;
		if(vis[a])
			continue;
		vis[a] = true;
		for(int i=0; i < v[a].size(); i++)
		{
			Edge e = v[a][i];
			if(e.c-e.f == 0)
				continue;
			if(d[e.b] == -1 || d[e.b] > d[a] + e.a)
			{
				d[e.b] = d[a] + e.a;
				par[e.b] = {a, i};
				kolejka.push({d[a] + e.a, e.b});
			}
		}
	}
	if(d[t] == -1)
	{
		return {0, 0};
	}
	//exact path
	int val = INF;
	int cost=0;
	int a = t;
	while(a!=s)
	{
		pii x = par[a];
		Edge e = v[x.ST][x.ND];
		val = min(val, e.c-e.f);
		a=x.ST;
	}
	a=t;
	while(a!=s)
	{
		pii x = par[a];
		Edge &e = v[x.ST][x.ND];
		e.f+=val;
		v[e.b][e.r].f-=val;
		cost+=val*e.a;
		a=x.ST;
	}
	//calculate new edges' weights and new potential
	cost=cost-(pot[s]-pot[t])*val;
	for(int i=1; i <= n; i++)
	{
		pot[i]+=d[i];
		for(Edge &e : v[i])
		{
			e.a = e.a + d[i] - d[e.b];
		}
	}
	return {val, cost};
}

pii minCostMaxFlow(int s, int t)
{
	BellmanFord(s);
	int f = 0;
	int cost=0;
	int df, dc;
	do
	{
		pii x = Dijkstra(s, t);
		df = x.ST;
		dc = x.ND;
		f+=df;
		cost+=dc;
	}while(df);
	return {f, cost};
}

int main()
{
	ios_base::sync_with_stdio(0);
	//example usage
	cin >> n;
	for(int a = 1; a <= n; a++)
	{
		for(int b = n+1; b <= n+n; b++)
		{
			int cost;
			cin >> cost;
			int x1 = v[a].size(), x2 = v[b].size();
			v[a].PB(Edge(b, 1, 0, x2, cost));
			v[b].PB(Edge(a, 0, 0, x1, -cost));
		}
	}
	int s = 2*n+1;
	int t = 2*n+2;
	for(int a = 1; a <= n; a++)
	{
		int x1 = v[s].size(), x2 = v[a].size();
		v[s].PB(Edge(a, 1, 0, x2, 0));
		v[a].PB(Edge(s, 0, 0, x1, 0));
	}
	for(int b = n+1; b <= n+n; b++)
	{
		int x1 = v[b].size(), x2 = v[t].size();
		v[b].PB(Edge(t, 1, 0, x2, 0));
		v[t].PB(Edge(b, 0, 0, x1, 0));
	}
	n = t;
	pii x = minCostMaxFlow(s, t);
	cout << x.ND << "\n";
	

	return 0;
}

