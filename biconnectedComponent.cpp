#include<bits/stdc++.h>

/*
 * Finds subgraphs that are biconnected components or bridges. 
 * O(V+E)
 */

using namespace std;
typedef pair<int, int> pii;
#define PB push_back
#define ST first
#define ND second

const int maxn = 1e5+10;
vector<int> v[maxn];
bool vis[maxn];
int pre[maxn], low[maxn];

stack<int> stos;
stack<pii> stosE;
int nr;

void checkbc(vector<int> &v, vector<pii> &e) //this graph is a biconnected component or a bridge
{
	for(int b : v)
		cout << b << " ";
	cout << "\n";
	for(pii c : e)
		cout << c.ST << " " << c.ND << "\t";
	cout << "\n";
}

void dfs(int a, int p)
{
	vis[a] = true;
	pre[a] = nr++;
	int res=pre[a];
	bool czy=true;
	for(int b : v[a])
	{
		if(b == p)
			continue;
		
		if(vis[b] == false)
		{
			stos.push(a);
			stosE.push({a, b});
			dfs(b, a);
			if(low[b] >= pre[a])
			{
				vector<int> v;
				vector<pii> e;
				while(true)
				{
					int c = stos.top();
					stos.pop();
					v.PB(c);
					if(c == a)
						break;
				}
				while(true)
				{
					pii  c = stosE.top();
					stosE.pop();
					e.PB(c);
					if(c.ST == a && c.ND == b)
						break;
				}
				checkbc(v, e);
			}
			else
				czy = false;
			res = min(res, low[b]);
		}
		else
			res = min(res, pre[b]);
		if(pre[b] < pre[a])
			stosE.push({a, b});
	}
	low[a] = res;
	if(czy)
		stos.push(a);
}

int main()
{
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].PB(b);
		v[b].PB(a);
	}
	dfs(1, 0);
	
	return 0;
}

