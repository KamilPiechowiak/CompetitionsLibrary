#include<bits/stdc++.h>

/*
 * KMP algorithm
 * O(n+m)
 */

using namespace std;

const int maxn=100;

int main()
{
	ios_base::sync_with_stdio(0);
	string t, s;
	cin >> t;
	int n = t.size();
	int pi[maxn];
	pi[0] = -1;
	int b=-1;
	for(int i=1; i <= n; i++)
	{
		while(b!=-1 && t[b] != t[i-1])
			b = pi[b];
		b++;
		pi[i] = b;
		cout << i << " " << pi[i] << endl;
	}
	
	cin >> s;
	int m = s.size();
	b=0;
	for(int i=0; i < m; i++)
	{
		while(b!=-1 && t[b]!=s[i])
			b=pi[b];
		b++;
		if(b==n)
		{
			cout << i << endl;
			b = pi[b];
		}
	}
	
	return 0;
}
